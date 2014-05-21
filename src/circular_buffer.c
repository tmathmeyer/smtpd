#include "circular_buffer.h"
#include <stdlib.h>

c_buf* makebuffer(int size) {
	c_buf* elem = malloc(sizeof(c_buf));
	elem -> bufsize = 0;
	elem -> head = elem -> tail
	             = malloc(sizeof(b_elem));

	for(;size>0;size--) {
		elem -> tail = malloc(sizeof(b_elem));
		elem -> head -> next = elem -> tail;
	}

	elem -> tail -> next = elem -> head;
	elem -> tail = elem -> head;

}

void* readbuffer(c_buf* buf) {
	if (buf -> bufsize == 0) {
		return NULL;
	} else {
		void* res = buf -> tail -> element;
		buf -> tail -> element = NULL;
		buf -> tail = buf -> tail -> next;
		buf -> bufsize = buf -> bufsize - 1;
		return res;
	}
}

void writebuffer(void* elem, c_buf* buf) {
	buf -> head = buf -> head -> next;
	if (buf -> head == buf -> tail) {
		buf -> tail = buf -> tail -> next;
	}
	if (buf -> head -> element != NULL) {
		free(buf -> head -> element);
	}
	buf -> head -> element = elem;
	buf -> bufsize = buf -> bufsize + 1;
}

void cleanbuffer(c_buf* buf) {
	while (buf -> head != NULL) {
		b_elem* be = buf -> head;
		buf -> head = be -> next;
		if (be -> element != NULL) {
			free(be -> element);
		}
		free(be);
	}
	free(buf);
}

void*  peekbuffer(c_buf* buf, int rewind) {
	return buf -> tail -> element;
}