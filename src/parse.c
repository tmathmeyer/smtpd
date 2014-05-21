#include "parse.h"
#include "circular_buffer.h"

#include <stdio.h>
#include <stdlib.h>


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
		
	if (lineID == ' ') {
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


int main(int argc, char** argv) {

	c_buf* buffer = makebuffer(4);

	

	status* next = NULL;
	status* prev = NULL;

	char* action = NULL;

	while ( 1 ) {
		next=read_std_line();
		if (next != NULL) {
			if (prev != NULL) {
				if (next -> contact_points == 3 &&
					prev -> contact_points == 3 &&
					next -> reading_time - prev -> reading_time < 30) {
					action = "bspc desktop -f prev";
				}
			} else {
				action == NULL;
			}

			if (next -> contact_points == 0) {
				if (action != NULL) {
					system(action);
					action = NULL;
				}
			}


			free(prev);
			prev = next;
		}
	}


	free(buffer);

}