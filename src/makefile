

smtpd: parse.o c_buf.o action.o
	gcc -lm parse.o c_buf.o action.o -o smtpd

parse.o: parse.h parse.c
	gcc -c parse.c

c_buf.o: circular_buffer.c circular_buffer.h
	gcc -c circular_buffer.c -o c_buf.o

action.o: action_identify.c action_identify.h config.h
	gcc -c -lm action_identify.c -o action.o







clean:
	rm *.o smtpd
