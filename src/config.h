

/*
 * Touchpad dimensions
 *    take the output of `synclient`
 *    height = (bottomedge-topedge)/10
 *    width =  (right-left)/10;
 */

 #define TOUCHPAD_HEIGHT 189
 #define TOUCHPAD_WIDTH  300


/*
 * System commands for each swipe. leave a blank command as an empty string
 */

#define FINGERS_3 ["", "", "bspc desktop -f prev", "bspc desktop -f next", ""]
#define FINGERS_4 ["up_cmd", "down_cmd", "left_cmd", "right_cmd", "tap_cmd"]
#define FINGERS_5 ["up_cmd", "down_cmd", "left_cmd", "right_cmd", "tap_cmd"]