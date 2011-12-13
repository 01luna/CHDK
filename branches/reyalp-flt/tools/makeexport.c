#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

char* load_from_file(const char* filename);

int num_lines=0;


////////////////////////////////////////////////////////////////////////////////////////////////
//
// @tsv - Utility to convert export list to different required format
//
// USAGE:   makeexport module_exportlist.c module_exportlist.h exportlist.txt
//
///////////////////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv )
{
	if ( argc < 4 )
	{
		printf("#error Not enough arguments for export list maker.\n");
		exit(-1);
	}


	char* file1 = load_from_file( argv[1]);

	FILE* out_h = fopen(argv[2],"wb");
	FILE* out_txt = fopen(argv[3],"wb");

	if (!out_h)
	{
		printf("#error Error creation exportlist.h.\n");
		exit(-1);
	}
	if (!out_txt)
	{
		printf("#error Error creation exportlist.txt.\n");
		exit(-1);
	}

	fprintf(out_h,"//Auto generated file. Do not edit the contents of this file.\n");
	fprintf(out_h,"//Update the core/module_exportlist.c\n\n");
	fprintf(out_h,"#ifndef MODULE_EXPORTLIST_H\n");
	fprintf(out_h,"#define MODULE_EXPORTLIST_H\n\n");


	// Separate CHDK build num
	char* build = BUILD_NUMBER;
    int build_num=0;
    for ( ; *build; build++) {
        build_num = strtol(build, NULL, 0/*autodetect base oct-dec-hex*/);	
		if ( build_num>100 )
			 break;
	}
	if ( *build )
		fprintf(out_h,"#define CHDK_BUILD_NUM %d\n",build_num);

	num_lines=0;

    char* cur, *cursym;

    cur = file1;

    const char* exp_def_tag="/* EXPORTED_DEFINES_";
	int flag_section_defines = 0;

    for(; *cur && *cur!='{'; cur++) {

		if ( !strncmp(cur,exp_def_tag,strlen(exp_def_tag)) )
		{
			cur+=strlen(exp_def_tag);
			if (*cur=='B' ) { 
				fprintf(out_h,"\n//Section: exported defines\n");
				flag_section_defines=1; 
			}
			else if (*cur=='E' ) { flag_section_defines=0;}
    		for(; *cur && *cur!=10; cur++);
		}

		if (flag_section_defines) {
			cursym=cur;
    		for(; *cur && *cur!=10 && *cur!='='; cur++);
			if ( *cur=='=' ) {
				*cur=0;
				cur++;
				fprintf(out_h,"extern %s;\n",cursym);
    			for(; *cur && *cur!=10; cur++);		//goto eol
			}
		}
    }

	fprintf(out_h,"\n\n");
	fprintf(out_h,"\n//Section: ids of exported symbols\n");

    for(; *cur && *cur!=10; cur++); 	//get eol
    
    // Main cycle
    for(;*cur; )
    {
		for(; *cur==9 || *cur==' '; cur++);
	    if (*cur=='(') {
			for(cur++; *cur && *cur!=')'; cur++);
			for(; *cur==9 || *cur==' ' || *cur==')'; cur++);
		}
		//printf("%x [%c]\n",cur-file1,*cur);
		if ( *cur=='}') {break;}

	    if (*cur=='&')
			for(cur++; *cur==9 || *cur==' '; cur++);


		cursym=cur;
		for(; (*cur>='A' && *cur<='Z') || 
			  (*cur>='a' && *cur<='z') || 
			  (*cur>='0' && *cur<='9') || 
			  *cur=='_'; 
			cur++);

		if (cursym!=cur) {
			char symbol[33];
			int size=cur-cursym;

			if ( size>32) {size=32;}
			memcpy(symbol,cursym,size);
			symbol[size]=0;

			if (num_lines>=2) {
				fprintf(out_txt,"%s\x0a",symbol);
				for(; size>=0; size--)
				{
					if ( symbol[size]>='a' && symbol[size]<='z')
						symbol[size]-=0x20;
				}
				fprintf(out_h,"#define MODULESYM_%s %d\n",symbol,num_lines);
			}
			num_lines++;
		}

		for(; *cur && *cur!=10; cur++);
		for(; *cur==10; cur++);
	
    }

	if (num_lines>=1)
		fprintf(out_h,"\n#define EXPORTLIST_LAST_IDX %d\n\n",num_lines-1);
	else {
		fprintf(out_h,"#error Malformed export list. Only %d valid records\n\n",num_lines+2);
		exit(-2);
	}
	fprintf(out_h,"#endif\n");

	fclose(out_h);
	fclose(out_txt);
	
    return 0;
}

//-------------------------------------------------------------------

char* load_from_file(const char *filename) 
{
    int f, size;
    static struct stat st;
    char *buf = 0;

    f = open(filename, O_RDONLY, 0777);
    if (f>=0) {
        size = (stat((char*)filename, &st)==0)?st.st_size:0;
        if (size) {
            buf = (char*)malloc(size+1);
            if (buf) {
                size = read(f, buf, size);
                buf[size]=0;
            }
        }
        close(f);
    }
    return buf;
}
