
#include "parse.h"
#include "action_identify.h"
#include <stdio.h>
#include <stdlib.h>


#define MAX(A,B) (A>B?A:B)
#define ABS(A) (A>0?A:-A)


//char* identify_action(int duration, int dx, int dy, int fingers)
int main(int argc, char** argv) {

    status* next = NULL;
    status* initial = NULL;
    char max_preassure = 0;
    char max_fingers = 0;

    FILE* desc = popen("synclient -m 10", "r");


    while ( 1 ) {
        next=read_mouse_std(desc);
        if (next != NULL) {

            if (initial == NULL) {
                initial = next;
            }



            if (next -> contact_points == 0) {
                system(
                	identify_action(next->reading_time-initial->reading_time,
                	                next->contact_xpos-initial->contact_xpos,
                	                next->contact_ypos-initial->contact_ypos,
                	                max_fingers));
                max_preassure = 0;
                max_fingers = 0;
                free(initial);
                initial = NULL;
            } else {
                max_preassure = MAX(max_preassure, next -> contact_preassure);
                max_fingers = MAX(max_fingers, next -> contact_points);
            }
        }
    }

    return 0;

}