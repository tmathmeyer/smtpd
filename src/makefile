

smtpd: parse.o c_buf.o action.o
	gcc parse.o c_buf.o action.o -o smtpd -lm

parse.o: parse.h parse.c
	gcc -c parse.c

c_buf.o: circular_buffer.c circular_buffer.h
	gcc -c circular_buffer.c -o c_buf.o

action.o: action_identify.c action_identify.h config.h
	gcc -c action_identify.c -o action.o -lm







clean:
	rm *.o smtpd
