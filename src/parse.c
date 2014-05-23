#include "parse.h"
#include "circular_buffer.h"
#include "config.h"
#include "action_identify.h"

#include <stdio.h>
#include <stdlib.h>


#define MAX(A,B) (A>B?A:B)
#define ABS(A) (A>0?A:-A)

/*
 * utility for building a number from a character stream
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


status* read_mouse_std(FILE* desc) {
    char lineID = fgetc(desc);
    while( (lineID=fgetc(desc)) == ' ' );

    if (lineID == 't') {
        // this is a title line, ignore it
        while( (lineID=fgetc(desc)) != '\n' );
        return NULL;
    }

    status* cur = malloc(sizeof(status));

    cur -> reading_time = build_int(0, lineID);
    while( (lineID=fgetc(desc)) != ' ' ) {
        cur -> reading_time
            = build_int(cur -> reading_time, lineID);
    }
    while( (lineID=fgetc(desc)) == ' ' );

    cur -> contact_xpos = build_int(0, lineID);
    while( (lineID=fgetc(desc)) != ' ' ) {
        cur -> contact_xpos
            = build_int(cur -> contact_xpos, lineID);
    }
    while( (lineID=fgetc(desc)) == ' ' );

    cur -> contact_ypos = build_int(0, lineID);
    while( (lineID=fgetc(desc)) != ' ' ) {
        cur -> contact_ypos
            = build_int(cur -> contact_ypos, lineID);
    }
    while( (lineID=fgetc(desc)) == ' ' );

    cur -> contact_preassure = build_int(0, lineID);
    while( (lineID=fgetc(desc)) != ' ' ) {
        cur -> contact_preassure
            = build_int(cur -> contact_preassure, lineID);
    }
    while( (lineID=fgetc(desc)) == ' ' );

    cur -> contact_points = build_int(0, lineID);
    while( (lineID=fgetc(desc)) != ' ' ) {
        cur -> contact_points
            = build_int(cur -> contact_points, lineID);
    }
    while( (lineID=fgetc(desc)) == ' ' );

    cur -> contact_size = build_int(0, lineID);
    while( (lineID=fgetc(desc)) != ' ' ) {
        cur -> contact_size
            = build_int(cur -> contact_size, lineID);
    }
    while( (lineID=fgetc(desc)) != '\n' );

    return cur;
}


/* 
 * reads in form:
 *      \ *[matching]\ *=[0-9]^\n
 *   
 * MUST be queried in order, or given a new filedescriptor for each call
 */
int config_read(FILE* descriptor, char* matching, int* saveto) {
    char c, s=0, *old = matching;
    // clear the leading spaces
    while( (c=fgetc(descriptor)) == ' ');

    while(*matching == c) {
        c = fgetc(descriptor);
        s = *(++matching)==0;
    }

    if (!s) {
        //read to end of line
        while( (c=fgetc(descriptor)) != '\n');
        return config_read(descriptor, old, saveto);
    }

    //read up to the = sign
    while( (c=fgetc(descriptor)) == ' ');
    while( (c=fgetc(descriptor)) == ' ');

    int r = build_int(0, c);
    while( (c = fgetc(descriptor)) != ' ' && c != '\n' && c != 0) {
        r = build_int(r, c);
    }
    while( (c=fgetc(descriptor)) != '\n');

    *saveto = r;
    return 1;
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


//char* identify_action(int duration, int dx, int dy, int fingers)
int main(int argc, char** argv) {

    status* next = NULL;
    status* initial = NULL;
    char max_preassure = 0;
    char max_fingers = 0;

    //FILE* desc = fopen("synclient-m.in", "r");
    FILE* desc = popen("synclient -m 10", "r");

    while ( 1 ) {
        next=read_mouse_std(desc);
        if (next != NULL) {

            if (initial == NULL) {
                initial = next;
                puts("setting initial");
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
