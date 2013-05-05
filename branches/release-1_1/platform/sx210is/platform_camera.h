// Camera - SX210IS - platform_camera.h

// This file contains the various settings values specific to the SX210IS camera.
// This file is referenced via the 'include/camera.h' file and should not be loaded directly.

// If adding a new settings value put a suitable default in 'include/camera.h',
// along with documentation on what the setting does and how to determine the correct value.
// If the setting should not have a default value then add it in 'include/camera.h'
// using the '#undef' directive along with appropriate documentation.

// Override any default values with your camera specific values in this file. Try and avoid
// having override values that are the same as the default value.

// When overriding a setting value there are two cases:
// 1. If removing the value, because it does not apply to your camera, use the '#undef' directive.
// 2. If changing the value it is best to use an '#undef' directive to remove the default value
//    followed by a '#define' to set the new value.

// When porting CHDK to a new camera, check the documentation in 'include/camera.h'
// for information on each setting. If the default values are correct for your camera then
// don't override them again in here.

    //********
    //SX210   ASM1989 08.20.2010
    //********
    #define CAM_DRYOS_2_3_R39			1

    #define CAM_PROPSET			3

    #define	CAM_DATE_FOLDER_NAMING	1

    #define CAM_DRYOS                   1
    #define CAM_RAW_ROWPIX              4416 // from calcs see 100C lib.c   //ASM1989 08.20.2010  4416
    #define CAM_RAW_ROWS                3296 //  "     "    "    "    "  //ASM1989 08.20.2010   3296

    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO

    #define CAM_HAS_VIDEO_BUTTON		1
    #define CAM_VIDEO_QUALITY_ONLY          1
    #undef  CAM_VIDEO_CONTROL
    #define CAM_MULTIPART               1
    #define CAM_HAS_JOGDIAL             1
    #undef  CAM_USE_ZOOM_FOR_MF

    #define CAM_BRACKETING				1

    #undef  CAM_UNCACHED_BIT  // shut up compiler
    #define CAM_UNCACHED_BIT    0x40000000
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    // seem good asm1989

    #define	CAM_DNG_LENS_INFO               { 50,10, 700,10, 31,10, 59,10 }	// See comments in camera.h

    #define CAM_COLORMATRIX1                          \
        1026340, 1000000, -412992, 1000000, -158934, 1000000, \
        -59169, 1000000, 421214, 1000000, 23459, 1000000,     \
        28948, 1000000, 10693, 1000000, 127339,  1000000

    #define cam_CalibrationIlluminant1 17 // Standard Light A

    // cropping  //ASM1989 08.20.2010
    #define CAM_JPEG_WIDTH  4320
    #define CAM_JPEG_HEIGHT 3240

    // This works
    #define CAM_ACTIVE_AREA_X1			48
    #define CAM_ACTIVE_AREA_Y1			28
    #define CAM_ACTIVE_AREA_X2			4416-48
    #define CAM_ACTIVE_AREA_Y2			3296-28

    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #undef  CAM_WHITE_LEVEL
    #undef  CAM_BLACK_LEVEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #define CAM_BLACK_LEVEL             127

    #define CAM_EXT_TV_RANGE            1

    #undef CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE    5
    #undef CAM_HAS_ERASE_BUTTON
    #define  CAM_SHOW_OSD_IN_SHOOT_MENU  1

    #define CAM_HAS_VARIABLE_ASPECT 1

    #undef CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION  1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized

    #undef CAM_BITMAP_WIDTH
    #define CAM_BITMAP_WIDTH 960
    #undef CAM_BITMAP_HEIGHT
    #define CAM_BITMAP_HEIGHT 270
    #undef CAM_SCREEN_WIDTH
    #define CAM_SCREEN_WIDTH 480

    #undef EDGE_HMARGIN
    #define EDGE_HMARGIN 10			//10 fits video mode of sx210

   //zebra letterbox for saving memory
   #undef ZEBRA_HMARGIN0
   #define ZEBRA_HMARGIN0  30 //this 30 rows are not used by the display buffer is 720x240 effective, no 960x270, i.e. (270-240) reduction in widht possible but not done (more difficult to manage it and slower).

    //Testing Zebra stuff asmp1989 Dec2010
    #define CAM_ZEBRA_ASPECT_ADJUST 1
    #define CAM_ZEBRA_NOBUF 1

   #define CAM_QUALITY_OVERRIDE 1

    #define CAM_DRIVE_MODE_FROM_TIMER_MODE  1   // use PROPCASE_TIMER_MODE to check for multiple shot custom timer.
                                                // Used to enabled bracketing in custom timer, required on many recent cameras
                                                // see http://chdk.setepontos.com/index.php/topic,3994.405.html
                                              
    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX 1
    #define CAM_MIN_ISO_OVERRIDE                60  // see http://chdk.setepontos.com/index.php?topic=5045.msg99863#msg99863
//----------------------------------------------------------
