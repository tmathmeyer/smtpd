#include "parse.h"
#include "circular_buffer.h"
#include "config.h"
#include "action_identify.h"

#include <stdio.h>
#include <stdlib.h>


#define MAX(A,B) (A>B?A:B)
#define ABS(A) (A>0?A:-A)

/*
 * for converting string to int:
 * removes decimals and treats floats as ints
 */
int build_int(int old, char n) {
    if (n == ' ') {
        n = '0';
    }
    if (n == '.') {
        return old;
    }
    if (n < '0' || n > '9') {
        return -1;
    }
    return (old*10) + (n-'0');
}


status* read_std_line() {


    char lineID = getchar();
    while( (lineID=getchar()) == ' ' );

    if (lineID == 't') {
        // this is a title line, ignore it
        while( (lineID=getchar()) != '\n' );
        return NULL;
    }

    status* cur = malloc(sizeof(status));

    cur -> reading_time = build_int(0, lineID);
    while( (lineID=getchar()) != ' ' ) {
        cur -> reading_time
            = build_int(cur -> reading_time, lineID);
    }
    while( (lineID=getchar()) == ' ' );

    cur -> contact_xpos = build_int(0, lineID);
    while( (lineID=getchar()) != ' ' ) {
        cur -> contact_xpos
            = build_int(cur -> contact_xpos, lineID);
    }
    while( (lineID=getchar()) == ' ' );

    cur -> contact_ypos = build_int(0, lineID);
    while( (lineID=getchar()) != ' ' ) {
        cur -> contact_ypos
            = build_int(cur -> contact_ypos, lineID);
    }
    while( (lineID=getchar()) == ' ' );

    cur -> contact_preassure = build_int(0, lineID);
    while( (lineID=getchar()) != ' ' ) {
        cur -> contact_preassure
            = build_int(cur -> contact_preassure, lineID);
    }
    while( (lineID=getchar()) == ' ' );

    cur -> contact_points = build_int(0, lineID);
    while( (lineID=getchar()) != ' ' ) {
        cur -> contact_points
            = build_int(cur -> contact_points, lineID);
    }
    while( (lineID=getchar()) == ' ' );

    cur -> contact_size = build_int(0, lineID);
    while( (lineID=getchar()) != ' ' ) {
        cur -> contact_size
            = build_int(cur -> contact_size, lineID);
    }
    while( (lineID=getchar()) != '\n' );

    return cur;
}


void print_status(status* s)
{
    printf("contact_xpos: %i\n", s -> contact_xpos);
    printf("contact_ypos: %i\n", s -> contact_ypos);
    printf("contact_preassure: %i\n", s -> contact_preassure);
    printf("contact_points: %i\n", s -> contact_points);
    printf("contact_size: %i\n", s -> contact_size);
    printf("reading_time: %i\n", s -> reading_time);
}

void execute_command(status* beginning, status* end, int max_preassure) {
    if (beginning == end) {
        puts("error type 0");
        return;
    }

    if (beginning -> contact_points != end -> contact_points) {
        // something changed mid swipe... maybe do something about this later
        puts("error type 1");
       // return;
    }

    if (max_preassure < 20) {
        // they probably brushed the pad... ignore this
        puts("error type 2");
        return;
    }

    int distance_x = end -> contact_xpos - beginning -> contact_xpos;
    int distance_y = end -> contact_ypos - beginning -> contact_ypos;

    // this may seem backwards, but it is an attempt to normalize them in order to pick a decision
    int normal_x = ABS(distance_x) * TOUCHPAD_HEIGHT;
    int normal_y = ABS(distance_y) * TOUCHPAD_WIDTH;

    if (normal_x < normal_y) {
        //swipe up/down
        system("bspc desktop -f prev");
    } else {
        //swipe left/right
        system("bspc desktop -f next");
    }

}


//char* identify_action(int duration, int dx, int dy, int fingers)
int main(int argc, char** argv) {

    //c_buf* buffer = makebuffer(4);



    status* next = NULL;
    status* initial = NULL;
    char max_preassure = 0;


    while ( 1 ) {
        next=read_std_line();
        if (next != NULL) {

            if (initial == NULL) {
                initial = next;
                puts("setting initial");
            }



            if (next -> contact_points == 0) {
                identify_action(next->reading_time-initial->reading_time,
                	            next->contact_xpos-initial->contact_xpos,
                	            next->contact_ypos-initial->contact_ypos,
                	            initial -> contact_points);
                max_preassure = 0;
                free(initial);
                initial = NULL;
            } else {
                max_preassure = MAX(max_preassure, next -> contact_preassure);
            }
        }
    }


    //free(buffer);
    return 0;

}
