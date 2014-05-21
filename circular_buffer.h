



typedef struct be {
	void* element;
	struct be* next;
} b_elem;


typedef struct cb {
	int bufsize;
	b_elem* head;
	b_elem* tail;
} c_buf;


c_buf* makebuffer(int size);
void*  readbuffer(c_buf* buf);
void*  peekbuffer(c_buf* buf, int rewind);
void   writebuffer(void* elem, c_buf* buf);
void   cleanbuffer(c_buf* buf);
