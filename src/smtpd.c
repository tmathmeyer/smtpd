
//#include "parse.h"
#include <stdio.h>



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



get_touchpad_stats() {
	FILE* op = popen("cat synclient.in", "r");
	int re = 0;
	int le = 0;
	int to = 0;
	int bt = 0;
	config_read(op, "LeftEdge", &le);
	config_read(op, "RightEdge", &re);
	config_read(op, "TopEdge", &to);
	config_read(op, "BottomEdge", &bt);

	printf("LeftEdge %i\n", le);
	printf("RightEdge %i\n", re);
	printf("TopEdge %i\n", to);
	printf("BottomEdge %i\n", bt);
}



int main() {

	get_touchpad_stats();

/*
	int re = 0;
	int le = 0;
	config_read(op, "LeftEdge", &le);
	config_read(op, "RightEdge", &re);
	printf("LeftEdge:\t%i\n", le);
	printf("RightEdge:\t%i\n", re);

	fclose(op);
*/

}