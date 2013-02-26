#include "camera_info.h"
#include "stdlib.h"
#include "conf.h"
#include "keyboard.h"
#include "font.h"
#include "lang.h"
#include "gui.h"
#include "gui_lang.h"
#include "gui_draw.h"
#include "gui_menu.h"
#include "gui_mbox.h"
#include "modules.h"


//-------------------------------------------------------------------
static void rinit()
{
	// Erase screen if switching from user menu to main menu
	// in case the user menu is larger than the main menu
	// otherwise it leaves remnants of the user menu above and below
	// the main menu.
    gui_set_need_restore();
	gui_menu_init(&root_menu);
}

//-------------------------------------------------------------------
/*
 * 1 extra entry for the "Main menu" and 1 for null when the menu is full with user selections
 * Compiler will zero init remaining portion of array so no there is no hidden relationship between
 * this structure and the value of USER_MENU_ITEMS. The value of USER_MENU_ITEMS can be anything you
 * wish and everything automagically works.
*/

static CMenuItem user_submenu_items[USER_MENU_ITEMS + 2] = {
	MENU_ITEM(0x20,LANG_MENU_MAIN_TITLE,     MENUITEM_PROC,  rinit, 0 )
};

CMenu user_submenu = {0x2e,LANG_MENU_USER_MENU, NULL, user_submenu_items };

//-------------------------------------------------------------------
void add_user_menu_item(CMenuItem curr_menu_item, int* cur_menu_item_indx)
{
    int i;

    /*
     * Insert new Item at end of existing entries
     */
    for (i = 1; i < USER_MENU_ITEMS + 1; i++)
    {
        if (!user_submenu_items[i].text)
        {
            user_submenu_items[i] = curr_menu_item;
            char buf[200];
            sprintf(buf,lang_str(LANG_USER_MENU_ITEM_ADDED), lang_str(curr_menu_item.text));
            gui_mbox_init(LANG_MENU_USER_MENU, (int)buf, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
            camera_info.state.user_menu_has_changed = 1;
            return;
        }
    }
    gui_mbox_init(LANG_MENU_USER_MENU, LANG_USER_MENU_FULL, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
}


void gui_load_user_menu_script(const char *fn) 
{
    if (fn)
    {
		script_load(fn);

        // exit menu system on the assumption the user will want to run the script just loaded

        gui_set_mode(&altGuiHandler);
        rinit();
    }
}


void add_script_to_user_menu( char * fname ,  char * title )
{
    int i ;
    /*
     * Insert script info at end of existing entries
     */
    for(i = 1; i < USER_MENU_ITEMS + 1; i++)
    {
        if (!user_submenu_items[i].text)   // insert script title & full filename in next available spot 
        {
            if (conf.user_menu_vars.items[i-1].script_file == 0)
                conf.user_menu_vars.items[i-1].script_file = malloc(CONF_STR_LEN);
            strcpy(conf.user_menu_vars.items[i-1].script_file, fname);
            if (conf.user_menu_vars.items[i-1].script_title == 0)
                conf.user_menu_vars.items[i-1].script_title = malloc(CONF_STR_LEN);
            strcpy(conf.user_menu_vars.items[i-1].script_title, title);

            user_submenu_items[i].symbol = 0x35;
            user_submenu_items[i].opt_len = 0 ;
            user_submenu_items[i].type = MENUITEM_PROC;
            user_submenu_items[i].text = (int) conf.user_menu_vars.items[i-1].script_title;
            user_submenu_items[i].value = (int *) gui_load_user_menu_script ;
            user_submenu_items[i].arg = (int) conf.user_menu_vars.items[i-1].script_file;
            
            char buf[200];
            sprintf(buf,lang_str(LANG_USER_MENU_ITEM_ADDED), lang_str(user_submenu_items[i].text));
            gui_mbox_init(LANG_MENU_USER_MENU, (int)buf, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
            camera_info.state.user_menu_has_changed = 1;
            return;
        }
    }
    gui_mbox_init(LANG_MENU_USER_MENU, LANG_USER_MENU_FULL, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
}

void del_user_menu_item(int* cur_menu_item_indx)
{
    int i;

    // don't allow deleting link to main menu
    if (*cur_menu_item_indx == 0)
        return;

    /*
     * Delete user menu entry by sliding all the lower valid/existing entries up.
     */
    for (i = *cur_menu_item_indx; user_submenu_items[i].text; i++)
    {
        user_submenu_items[i] = user_submenu_items[i+1];

        if (conf.user_menu_vars.items[i-1].script_file)
            free(conf.user_menu_vars.items[i-1].script_file);
        conf.user_menu_vars.items[i-1].script_file = conf.user_menu_vars.items[i].script_file;
        conf.user_menu_vars.items[i].script_file = 0;

        if (conf.user_menu_vars.items[i-1].script_title)
            free(conf.user_menu_vars.items[i-1].script_title);
        conf.user_menu_vars.items[i-1].script_title = conf.user_menu_vars.items[i].script_title;
        conf.user_menu_vars.items[i].script_title = 0;
    }

    /*
     * there were no valid entries below this one, so
     * the index pointer must be decremented.
     */
    if(!user_submenu_items[*cur_menu_item_indx].text)
        *cur_menu_item_indx -= 1;

    camera_info.state.user_menu_has_changed = 1;
}

static void move_user_menu_item(int* cur_menu_item_indx, int dir)
{
    int src_index, dst_index ;
    char *tbuff;
        
    src_index = *cur_menu_item_indx ;
    dst_index = *cur_menu_item_indx + dir;    
        
    // Move current user menu item up (dir = -1) or down (dir = 1)
        
    CMenuItem tmp_menu_item = user_submenu_items[dst_index];
    user_submenu_items[dst_index] = user_submenu_items[src_index];
    user_submenu_items[src_index] = tmp_menu_item;
    
    src_index--; dst_index--;
   
    tbuff = conf.user_menu_vars.items[dst_index].script_file;
    conf.user_menu_vars.items[dst_index].script_file = conf.user_menu_vars.items[src_index].script_file;    
    conf.user_menu_vars.items[src_index].script_file = tbuff;
            
    tbuff = conf.user_menu_vars.items[dst_index].script_title;
    conf.user_menu_vars.items[dst_index].script_title = conf.user_menu_vars.items[src_index].script_title;    
    conf.user_menu_vars.items[src_index].script_title = tbuff;
        
    *cur_menu_item_indx += dir;

    camera_info.state.user_menu_has_changed = 1;
}

void move_user_menu_item_up(int* cur_menu_item_indx)
{
    /*
     * Move entry up
     */
    if (*cur_menu_item_indx > 1)
        move_user_menu_item(cur_menu_item_indx, -1);
}

void move_user_menu_item_down(int* cur_menu_item_indx)
{
    // don't allow moving link to main menu
    if (*cur_menu_item_indx == 0)
        return;

    /*
     * Move entry down below next entry if next entry is not empty
     */
    if((*cur_menu_item_indx < (USER_MENU_ITEMS)) && (user_submenu_items[*cur_menu_item_indx +1].text))
        move_user_menu_item(cur_menu_item_indx, 1);
}

//-------------------------------------------------------------------
CMenuItem* find_mnu_adv(CMenu *curr_menu, int flags, int itemid )
{
	int gui_menu_curr_item;
	CMenuItem* rv=0;

	if ( itemid==0 )
		return 0;		

	gui_menu_curr_item = 0;
	while(curr_menu->menu[gui_menu_curr_item].text) {
		if ( lang_strhash31(curr_menu->menu[gui_menu_curr_item].text) == itemid){
			return (CMenuItem*) &(curr_menu->menu[gui_menu_curr_item]);
		}
		if ((flags & FLAG_FIND_RECURSIVE) &&
		  (curr_menu->menu[gui_menu_curr_item].type & MENUITEM_MASK) == MENUITEM_SUBMENU) {

				if (curr_menu->menu[gui_menu_curr_item].text != LANG_MENU_USER_MENU) {
					rv = find_mnu((CMenu*)(curr_menu->menu[gui_menu_curr_item].value), itemid);
					if ( rv )
						return rv;
				}
		}
		gui_menu_curr_item++;
	}
	return 0;
}

CMenuItem* find_mnu(CMenu *curr_menu, int itemid )
{
	return find_mnu_adv(curr_menu, FLAG_FIND_RECURSIVE, itemid );
}

void user_menu_save() {
    int x;
    for (x=0; x<USER_MENU_ITEMS; x++) {
		/*
		 * First entry in user_submenu_items is reserved for the "Main Menu"
 		 * conf.user_menu_vars only tracks/saves the real user entries.
 		 */
	
        if ( user_submenu_items[x+1].text )
        {
            if ( user_submenu_items[x+1].value == (int *)gui_load_user_menu_script )
            {
                conf.user_menu_vars.items[x].var = -1 ;                                             // flag script entries specially 
            }
            else
            {
                conf.user_menu_vars.items[x].var = lang_strhash31(user_submenu_items[x+1].text);    // otherwise save a hash
            }
        }
        else
        {
            conf.user_menu_vars.items[x].var = 0;
            if (conf.user_menu_vars.items[x].script_file != 0)
            {
                free(conf.user_menu_vars.items[x].script_file);
                conf.user_menu_vars.items[x].script_file = 0;
            }
            if (conf.user_menu_vars.items[x].script_title != 0)
            {
                free(conf.user_menu_vars.items[x].script_title);
                conf.user_menu_vars.items[x].script_title = 0;
            }
        }
    } 
}

void user_menu_restore() {
    int x,y ;
    CMenuItem* item=0;
    /*
     * First entry in user_submenu_items is reserved for the "Main Menu"
     * conf.user_menu_vars only tracks/saves the real user entries.
     */
       
    for (x=0, y=1; x<USER_MENU_ITEMS; x++, y++)
    {
        if( conf.user_menu_vars.items[x].var == -1 )    // special flag- there is no hash for script entries
        {   
            user_submenu_items[y].symbol = 0x35;        // restore the script entry
            user_submenu_items[y].opt_len = 0 ;
            user_submenu_items[y].type = MENUITEM_PROC;
            user_submenu_items[y].text = (int) conf.user_menu_vars.items[x].script_title;
            user_submenu_items[y].value = (int *) gui_load_user_menu_script ;
            user_submenu_items[y].arg = (int) conf.user_menu_vars.items[x].script_file;  
        }
        else
        { 
            if (conf.user_menu_vars.items[x].var > 0 )  // look up the menu text
                 item = find_mnu(&root_menu, conf.user_menu_vars.items[x].var);
            else item = NULL ;
            
            if ( item )                                 // add back in if found
            {
                user_submenu_items[y] = *item;
            }
            else                                        // otherwise clear the menu entry
            {
                user_submenu_items[y].text = 0;            
                break ;                                 // and exit - all done !
            }
        }
    }  
}

