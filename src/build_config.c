#include "parse.h"
#include <stdio.h>

int main() {
    FILE* conf = fopen("gen/sizes.h", "w");
    if (conf == NULL) {
        return 1;
    }

    //FILE* op = popen("synclient", "r");
    FILE* op = popen("cat synclient.in", "r");
    if (op == NULL) {
        return 1;
    }

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
