#include "parse.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * utility for building a number from a character stream
 */
int build_int(int old, char n) {
    if (n == ' ') {
        return old;
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
    float temp_time_store;

    fscanf(desc, "%f %i %i %s %s %s",
           &(temp_time_store),
           &(cur -> contact_xpos),
           &(cur -> contact_ypos),
           &(cur -> contact_preassure),
           &(cur -> contact_points),
           &(cur -> contact_size));
    cur -> reading_time = (int) (temp_time_store * 1000);

    //scan to eol
    while( (lineID=fgetc(desc)) != '\n' );

    return cur;
}


/*
 * reads in form:
 *      \[ *][matching]\[ *]=[ *][0-9]^\n
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