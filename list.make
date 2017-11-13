a.out : struct.c test.c
	gcc struct.c test.c

test : test.c struct.h
	gcc test.c struct.c

struct : struct.c struct.h
	gcc struct.c struct.h

