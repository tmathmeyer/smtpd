

smtpd: parse.o c_buf.o action.o
	gcc -Wall -lm parse.o c_buf.o action.o -o smtpd

parse.o: parse.h parse.c
	gcc -Wall -c parse.c

c_buf.o: circular_buffer.c circular_buffer.h
	gcc -Wall -c circular_buffer.c -o c_buf.o

action.o: action_identify.c action_identify.h config.h
	gcc -Wall -c -lm action_identify.c -o action.o







clean:
	rm *.o smtpd
