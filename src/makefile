

smtpd: build_config action.o
	gcc -Wall smtpd.c parse.o action.o -o ../smtpd -lm \
	&& make purge





parse.o: parse.h parse.c
	gcc -c -Wall parse.c

action.o: action_identify.c action_identify.h config.h gen/sizes.h
	gcc -c -Wall action_identify.c -o action.o -lm





build_config: build_config.c parse.o
	gcc -Wall build_config.c parse.o -o confgen && \
	rm -rf gen && mkdir gen && ./confgen && rm confgen

purge:
	rm -rf gen *.o



clean: purge
	rm smtpd
