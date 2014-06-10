
#include "parse.h"
#include "action_identify.h"
#include "smtpd.h"
#include <stdio.h>
#include <stdlib.h>

//#include <math.h>





//char* identify_action(int duration, int dx, int dy, int fingers)
int main(int argc, char** argv) {

    return daemon_function();

}







// do this neively for now
int analyze(sample* motionlist) {
    if (motionlist == NULL) {
        return -1;
    }

    status* initial = motionlist -> data;
    int max_fingers = 0;
    while(motionlist -> next != NULL) {
        max_fingers = MAX(max_fingers, motionlist -> data -> contact_points);
        motionlist = motionlist -> next;
    }
    status* final = motionlist -> data;

    system(identify_action(final->reading_time-initial->reading_time,
                           final->contact_xpos-initial->contact_xpos,
                           final->contact_ypos-initial->contact_ypos,
                           max_fingers));
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
        printf("is next null? %i\n", next == NULL);
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
            pclose(desc);
            return 1;
        }
    }
    pclose(desc);
    return 0;
}