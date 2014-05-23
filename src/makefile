

smtpd: parse.o c_buf.o config.h
	gcc parse.o c_buf.o -o smtpd

parse.o: parse.h parse.c
	gcc -c parse.c

c_buf.o: circular_buffer.c circular_buffer.h
	gcc -c circular_buffer.c -o c_buf.o







clean:
	rm *.o smtpd
