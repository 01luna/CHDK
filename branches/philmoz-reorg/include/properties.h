#ifndef PROPERTIES_H
#define PROPERTIES_H

/* propcase ID constants. These are in their own header files for easier sed processing */
#if CAM_PROPSET == 5
    #include "propset5.h"   // DryOS R50
#elif CAM_PROPSET == 4
    #include "propset4.h"
#elif CAM_PROPSET == 3
    #include "propset3.h"
#elif CAM_PROPSET == 2      // most digic3 cameras
    #include "propset2.h"
#elif CAM_PROPSET == 1      // most digic2 cameras
    #include "propset1.h"
#elif CAM_PROPSET == 0      // dummy for module build
    // Don't load a propset when building modules
    // If any module tries to use a propset value it will generate an error
#else
    #error unknown camera processor
#endif

extern long get_property_case(long id, void *buf, long bufsize);
extern long set_property_case(long id, void *buf, long bufsize);

extern void shooting_set_prop(int id, int v);
extern int shooting_get_prop(int id);

extern long get_parameter_data(long id, void *buf, long bufsize);
extern long set_parameter_data(long id, void *buf, long bufsize);

#endif
