
#include "parse.h"
#include "smtpd.h"
#include "action_identify.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>





//char* identify_action(int duration, int dx, int dy, int fingers)
int main(int argc, char** argv) {

    return daemon_function();

}

float dist(status* a, status* b) {
    int x = a -> contact_xpos - b -> contact_xpos;
    int y = a -> contact_ypos - b -> contact_ypos;
    return sqrt(x*x + y*y);
}

float calc_angle(status* a, status* b, status* c) {
    float A = dist(a, b);
    float B = dist(a, c);
    float C = dist(b, c);
    float arg = (C*C - A*A - B*B) / (-2*A*B);
    return acos(arg);
}

float circle_analyzer(sample* motionlist) {
    float angle = 0.0;
    status *a = NULL, *b = NULL, *c = NULL;
    while(motionlist -> next != NULL) {
        a = b; b = c;
        c = motionlist -> data;
        if (a != NULL  &&  b != NULL  &&  c != NULL) {
            angle += calc_angle(a, b, c);
        }
        motionlist = motionlist -> next;
    }
    return angle;
}




// do this neively for now (dont even bother freeing the list)
int analyze(sample* motionlist) {
    if (motionlist == NULL) {
        return -1;
    }

    //status* initial = motionlist -> data;
    //int max_fingers = 0;
    //while(motionlist -> next != NULL) {
    //    max_fingers = MAX(max_fingers, motionlist -> data -> contact_points);
    //    motionlist = motionlist -> next;
    //}
    //status* final = motionlist -> data;

    //puts(identify_action(final->reading_time-initial->reading_time,
    //                       final->contact_xpos-initial->contact_xpos,
    //                       final->contact_ypos-initial->contact_ypos,
    //                       max_fingers));

    printf("%f\n", circle_analyzer(motionlist));
    return 0;
}






// run the application as a daemon
// return 0 for success
int daemon_function() {
    sample* head = NULL;
    sample* tail = NULL;
    status* next = NULL;
    FILE* desc = popen("cat synclient.test", "r");
    if (desc == NULL) {
        perror("cannot open that file");
        return 2;
    }
    puts("opened file");

    while( 1 ) {

        next = read_mouse_std(desc);
        if (next != NULL) {
            if (next -> contact_points == 0) {
                analyze(head); // analyze is responsible for freeing the memory in head
                head = NULL;
            } else {
                sample* cur = malloc(sizeof(sample));
                cur -> data = next;
                cur -> next = NULL;
                if (head == NULL) {
                    head = cur;
                } else {
                    tail -> next = cur;
                }
                tail = cur;
            }
        } else {
            // line was T line
        }
    }
    pclose(desc);
    return 0;
}