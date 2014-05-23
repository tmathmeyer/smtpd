#include "parse.h"
#include <stdio.h>

int using_sed();
int using_parse();

int main() {
	//return using_sed();	// 0.004s
	return using_parse();	// 0.002s
}


int using_sed() {
	FILE* rf = popen(
		"cat synclient.in | grep RightEdge | sed s/[a-z\\ =]//gi", "r");
	FILE* lf = popen(
		"cat synclient.in | grep LeftEdge | sed s/[a-z\\ =]//gi", "r");
	FILE* tf = popen(
		"cat synclient.in | grep TopEdge | sed s/[a-z\\ =]//gi", "r");
	FILE* bf = popen(
		"cat synclient.in | grep BottomEdge | sed s/[a-z\\ =]//gi", "r");

	FILE* conf = fopen("gen/sizes.h", "w");

	if (rf==NULL || lf==NULL || tf==NULL || bf==NULL || conf==NULL) {
		return 1;
	}

	int re = 0;
	int le = 0;
	int te = 0;
	int be = 0;

	char c;
	while( (c=fgetc(rf)) != -1) re = build_int(re, c);
	while( (c=fgetc(lf)) != -1) le = build_int(le, c);
	while( (c=fgetc(tf)) != -1) te = build_int(te, c);
	while( (c=fgetc(bf)) != -1) be = build_int(be, c);

	int trackpad_width = ((re-le) + 99) / 100;
	int trackpad_height = ((be-te) + 99) / 100;

	fprintf(conf, "#define trackpad_width %i\n", trackpad_width);
	fprintf(conf, "#define trackpad_height %i\n", trackpad_height);

	fclose(rf);
	fclose(lf);
	fclose(tf);
	fclose(bf);
	fclose(conf);

	return 0;
}

int using_parse() {
	FILE* conf = fopen("gen/sizes.h", "w");
	if (conf == NULL) return 1;
    
    //FILE* op = popen("synclient", "r");
	FILE* op = popen("cat synclient.in", "r");
	if (op == NULL) return 1;

	int re = 0;
	int le = 0;
	int te = 0;
	int be = 0;
	config_read(op, "LeftEdge", &le);
	config_read(op, "RightEdge", &re);
	config_read(op, "TopEdge", &te);
	config_read(op, "BottomEdge", &be);

	int trackpad_width = ((re-le) + 99) / 100;
	int trackpad_height = ((be-te) + 99) / 100;


	fprintf(conf, "#define trackpad_width %i\n", trackpad_width);
	fprintf(conf, "#define trackpad_height %i\n", trackpad_height);

	fclose(op);
	fclose(conf);

	return 0;
}