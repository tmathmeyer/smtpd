#include "parse.h"
#include "config.h"
#include "action_identify.h"
#include <math.h>
#include <stdio.h>

#define ABS(A) ((A)>0?(A):-(A))

char* identify_action(int duration, int dx, int dy, int fingers) {
    int nx = dx/trackpad_width;
    int ny = dy/trackpad_height;
    int mx = ABS(nx);
    int my = ABS(ny);

    float dist = sqrt(nx*nx + ny*ny);
    if (dist <= trackpad_scale_factor || duration <= trackpad_min_duration) {
    	printf("\tdist: %f\n\tdur: %i\n", dist, duration);
    	return tap(fingers);
    }

    if (mx*2.7 > my) {
    	if (nx < 0) {
    		return swipeleft(fingers);
    	} else {
    		return swiperight(fingers);
    	}
    } else {
    	if (ny > 0) {
    		return swipedown(fingers);
    	} else {
    		return swipeup(fingers);
    	}
    }
    return "";
}


char* swipeleft (int fingers) {
	printf("swipeleft: %i fingers\n", fingers);
	switch(fingers) {
		case 2: return LEFT_2;
		case 3: return LEFT_3;
		case 4: return LEFT_4;
		case 5: return LEFT_5;
		default: return "";
	}
}
char* swiperight(int fingers) {
	printf("swiperight: %i fingers\n", fingers);
	switch(fingers) {
		case 2: return RIGHT_2;
		case 3: return RIGHT_3;
		case 4: return RIGHT_4;
		case 5: return RIGHT_5;
		default: return "";
	}
}
char* swipeup   (int fingers) {
	printf("swipeup: %i fingers\n", fingers);
	switch(fingers) {
		case 2: return UP_2;
		case 3: return UP_3;
		case 4: return UP_4;
		case 5: return UP_5;
		default: return "";
	}
}
char* swipedown (int fingers) {
	printf("swipedown: %i fingers\n", fingers);
	switch(fingers) {
		case 2: return DOWN_2;
		case 3: return DOWN_3;
		case 4: return DOWN_4;
		case 5: return DOWN_5;
		default: return "";
	}
}
char* tap(int fingers) {
	printf("tap: %i fingers\n", fingers);
	switch(fingers) {
		case 2: return TAP_2;
		case 3: return TAP_3;
		case 4: return TAP_4;
		case 5: return TAP_5;
		default: return "";
	}
}
