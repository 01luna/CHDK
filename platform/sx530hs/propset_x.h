#error "verify propcase IDs and assign a number"
// this file came from includes/propset7.h in http://chdk.setepontos.com/index.php?topic=12418.10
// the lines with "jeronymo" in the comment are probably correct for sx530hs
// The status of others is unknown. Most are copied from propset6. It is likely that values have shifted
#ifndef PROPSET_X_H
#define PROPSET_X_H

/*
constants for propset ???
WARNING:
The build uses tools/gen_propset_lua.sed to generate propset6.lua from this file
DO NOT USE MULTILINE COMMENTS AROUND DEFINES
*/

#define PROPCASE_AE_LOCK                         3          // 0 = AE not locked, 1 = AE locked-----blackhole
#define PROPCASE_AF_ASSIST_BEAM                  5          // 0=disabled,  1=enabled-----blackhole
#define PROPCASE_REAL_FOCUS_MODE                 6          //??? WIKI|Propcase focus_mode
#define PROPCASE_AF_FRAME                        8          // 1 = Center, 2 = Face AiAF / Tracking AF----blackhole
#define PROPCASE_AF_LOCK                         11         // 0 = AF not locked, 1 = AF locked
#define PROPCASE_CONTINUOUS_AF                   12         // 0 = Continuous AF off, 1 = Continuous AF on-----blackhole
#define PROPCASE_FOCUS_STATE                     18         //???
#define PROPCASE_AV2                             22         // (philmoz, May 2011) - this value causes overrides to be saved in JPEG and shown on Canon OSD
#define PROPCASE_AV                              26         // This values causes the actual aperture value to be overriden jeronymo
#define PROPCASE_MIN_AV                          25
#define PROPCASE_USER_AV                         26
#define PROPCASE_BRACKET_MODE                    29
#define PROPCASE_BV                              34
#define PROPCASE_SHOOTING_MODE                   50         // jeronymo 
#define PROPCASE_CUSTOM_SATURATION               55         // Canon Menu slide bar values: 255, 254, 0, 1, 2
#define PROPCASE_QUALITY                         57
#define PROPCASE_CUSTOM_CONTRAST                 59         // Canon Menu slide bar values: 255, 254, 0, 1, 2
#define PROPCASE_FLASH_SYNC_CURTAIN              64
#define PROPCASE_SUBJECT_DIST2                   65
#define PROPCASE_DATE_STAMP                      66         // 0 = Off, 1 = Date, 2 = Date & Time
#define PROPCASE_DELTA_SV                        79
#define PROPCASE_DIGITAL_ZOOM_MODE               91         // Digital Zoom Mode/State 0 = off/standard, 2 = 1.5x, 3 = 2.0x
#define PROPCASE_DIGITAL_ZOOM_STATE              94         // Digital Zoom Mode/State 0 = Digital Zoom off, 1 = Digital Zoom on
#define PROPCASE_DIGITAL_ZOOM_POSITION           95
#define PROPCASE_DRIVE_MODE                      102
#define PROPCASE_OVEREXPOSURE                    103
#define PROPCASE_DISPLAY_MODE                    105
#define PROPCASE_EV_CORRECTION_1                 107
#define PROPCASE_FLASH_ADJUST_MODE               121
#define PROPCASE_FLASH_FIRE                      122
#define PROPCASE_FLASH_EXP_COMP                  127    // APEX96 units
#define PROPCASE_FOCUS_MODE                      133
#define PROPCASE_FLASH_MANUAL_OUTPUT             141        // !not sure, but required for compile; from propset4
#define PROPCASE_FLASH_MODE                      146        // 0 = Auto, 1 = ON, 2 = OFF
#define PROPCASE_IS_MODE                         145        // 0 = Continuous, 2 = only Shoot, 4 = OFF
#define PROPCASE_ISO_MODE                        152        // jeronymo
#define PROPCASE_METERING_MODE                   160        // 0 = Evaluative, 1 = Spot, 2 = Center weighted avg----blackhole

#define PROPCASE_CUSTOM_BLUE                     176        // Canon Menu slide bar values: 255, 254, 0, 1, 2
#define PROPCASE_CUSTOM_GREEN                    177        // Canon Menu slide bar values: 255, 254, 0, 1, 2
#define PROPCASE_CUSTOM_RED                      178        // Canon Menu slide bar values: 255, 254, 0, 1, 2
#define PROPCASE_CUSTOM_SKIN_TONE                179        // Canon Menu slide bar values: 255, 254, 0, 1, 2
#define PROPCASE_MY_COLORS                       187        // 0 = Off, 1 = Vivid, 2 = Neutral, 3 = B/W, 4 = Sepia, 5 = Positive Film, 6 = Lighter Skin Tone, 7 = Darker Skin Tone, 8 = Vivid Red, 9 = Vivid Green, 10 = Vivid Blue, 11 = Custom Color
#define PROPCASE_ND_FILTER_STATE                 195        // 0 = out, 1 = in
#define PROPCASE_OPTICAL_ZOOM_POSITION           198 
#define PROPCASE_EXPOSURE_LOCK                   209     // Old PROPCASE_SHOOTING value - gets set when set_aelock called or AEL button pressed
#define PROPCASE_SHOOTING                        304     // This value appears to work better - gets set to 1 when camera has focused and set exposure, returns to 0 after shot
#define PROPCASE_EV_CORRECTION_2                 210
#define PROPCASE_IS_FLASH_READY                  211
#define PROPCASE_RESOLUTION                      222        // 0 = L, 1 = M1, 2 = M2, 4 = S, 7 = Low Light jeronymo
#define PROPCASE_ORIENTATION_SENSOR              222
#define PROPCASE_TIMER_MODE                      229        // 0 = OFF, 1 = 2 sec, 2 = 10 sec, 3 = Custom-----blackhole
#define PROPCASE_TIMER_DELAY                     227        // timer delay in msec
#define PROPCASE_CUSTOM_SHARPNESS                228        // Canon Menu slide bar values: 255, 254, 0, 1, 2
#define PROPCASE_STITCH_DIRECTION                236        // 0=left>right, 1=right>left. Some cams have more
#define PROPCASE_STITCH_SEQUENCE                 241        // counts shots in stitch sequence, positive=left>right, negative=right>left
#define PROPCASE_SUBJECT_DIST1                   248
#define PROPCASE_SV_MARKET                       249
#define PROPCASE_TV2                             264        // (philmoz, May 2011) - this value causes overrides to be saved in JPEG and shown on Canon OSD
#define PROPCASE_TV                              265        // Need to set this value for overrides to work correctly
#define PROPCASE_USER_TV                         267
#define PROPCASE_WB_MODE                         276        // 0 = Auto, 1 = Daylight, 3 = Cloudy, 4 = Tungsten, 5 = Fluorescent, 6 = Fluorescent H, 8 = Custom-----blackhole
#define PROPCASE_WB_ADJ                          272
#define PROPCASE_SERVO_AF                        303        // 0 = Servo AF off, 1 = Servo AF on-----blackhole
#define PROPCASE_ASPECT_RATIO                    304        // 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1------blackhole
#define PROPCASE_SV                              346        // (philmoz, May 2011) - this value causes overrides to be saved in JPEG and shown on Canon OSD
#define PROPCASE_GPS                             357        // (CHDKLover, August 2011) - contains a 272 bytes long structure
#define PROPCASE_TIMER_SHOTS                     376        // Number of shots for TIMER_MODE=Custom

// !not sure
//#define PROPCASE_DIGITAL_ZOOM_MODE               91         // Digital Zoom Mode/State 0 = off/standard, 2 = 1.7x, 3 = 2.1x

#endif
