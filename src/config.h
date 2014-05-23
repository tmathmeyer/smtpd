

/*
 * Touchpad dimensions
 *    as long as the ratio lines up this is fine, ie:
 *			1599:901 -> 16:9 will be suficient
 */

 #define TOUCHPAD_HEIGHT 9
 #define TOUCHPAD_WIDTH  16


/*
 * System commands for each swipe. leave a blank command as an empty string
 */

#define FINGERS_3 ["", "", "bspc desktop -f prev", "bspc desktop -f next", ""]
#define FINGERS_4 ["up_cmd", "down_cmd", "left_cmd", "right_cmd", "tap_cmd"]
#define FINGERS_5 ["up_cmd", "down_cmd", "left_cmd", "right_cmd", "tap_cmd"]

#define trackpad_width 