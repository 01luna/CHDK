#include "platform.h"

void *hook_raw_fptr()
{
    return (void*)0x3F960;
}

void *hook_raw_ret_addr()
{
    return (void*)0xFFCC6640;
}

char *hook_raw_image_addr()
{
    return (char*)(0x10400000+0x164000+0xBF0);
}

long hook_raw_size()
{
    return 0x8CAE10;
}