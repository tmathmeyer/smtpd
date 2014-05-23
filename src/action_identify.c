#include "parse.h"
#include "config.h"
#include "action_identify.h"

#define ABS(A) ((A)>0?(A):-(A))

char* identify_action(int duration, int dx, int dy, int fingers) {
    int nx = dx/trackpad_width;
    int ny = dy/trackpad_height;
    int mx = ABS(nx);
    int my = ABS(ny);

    if (Math.sqrt(nx*nx + ny*ny) <= trackpad_scale_factor ||
    	duration <= trackpad_min_duration) {
    	return tap(fingers);
    }

    if (mx > my) {
    	if (nx < 0) {
    		return swipeleft(fingers);
    	} else {
    		return swiperight(fingers);
    	}
    } else {
    	if (ny < 0) {
    		return swipedown(fingers);
    	} else {
    		return swipeup(fingers);
    	}
    }
    return "";
}


char* swipeleft (int fingers) {
	return "bspc desktop -f next";
}
char* swiperight(int fingers) {
	return "bspc desktop -f prev";
}
char* swipeup   (int fingers) {
	return "";
}
char* swipedown (int fingers) {
	return "";
}
char* tap(int fingers) {
	return "";
}