/*

example output:
  27.219  1398 1052   0 0  2  0 0 0 0 0  00000000
  27.419  1356 1079   8 1  2  0 0 0 0 0  00000000
  27.620  1356 1079   0 0  2  0 0 0 0 0  00000000



parts:
  time
  xcoord
  ycoord
  preasure
  fingers
  touch width (palming?)


*/

#include <stdio.h>

typedef struct input {
	short contact_xpos;
	short contact_ypos;
	char  contact_preassure;
	char  contact_points;
	char  contact_size;
	int   reading_time;
} status;


int build_int(int old, char n);
status* read_std_line();
int config_read(FILE* descriptor, char* matching, int* saveto);
