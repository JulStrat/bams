CC = gcc
# CFLAGS = -m32 -g -w -Wall -Wextra -Wconversion -ansi -pedantic --coverage
CFLAGS = -g -w -Wall -Wextra -Wconversion -ansi -pedantic --coverage -fsanitize=address -static-libasan
all: test_merge test_bisect bams_app bams_ptr_app test_bams_ptr

test_merge: test_merge.o merge.o
	$(CC) $(CFLAGS) -o test_merge test_merge.o merge.o

test_bisect: test_bisect.o bisect.o
	$(CC) $(CFLAGS) -o test_bisect test_bisect.o bisect.o

bams_app: bams_app.o bams.o bisect.o merge.o
	$(CC) $(CFLAGS) -o bams_app bams_app.o bams.o bisect.o merge.o

bams_ptr_app: bams_ptr_app.o bams.o bisect.o merge.o
	$(CC) $(CFLAGS) -o bams_ptr_app bams_ptr_app.o bams.o bisect.o merge.o

test_bams_ptr: test_bams_ptr.o bams.o bisect.o merge.o
	$(CC) $(CFLAGS) -o test_bams_ptr test_bams_ptr.o bams.o bisect.o merge.o

test_merge.o: tests/test_merge.c tests/greatest.h merge.h
	$(CC) -c $(CFLAGS) -o test_merge.o -I. tests/test_merge.c

test_bisect.o: tests/test_bisect.c tests/greatest.h bisect.h
	$(CC) -c $(CFLAGS) -o test_bisect.o -I. tests/test_bisect.c

bams_app.o: bams_app.c bams.h
	$(CC) -c $(CFLAGS) -o bams_app.o bams_app.c

bams_ptr_app.o: bams_ptr_app.c bams.h
	$(CC) -c $(CFLAGS) -o bams_ptr_app.o bams_ptr_app.c

test_bams_ptr.o: test_bams_ptr.c bams.h
	$(CC) -c $(CFLAGS) -o test_bams_ptr.o test_bams_ptr.c

bams.o: bams.c bams.h
	$(CC) -c $(CFLAGS) -o bams.o bams.c

merge.o: merge.c
	$(CC) -c $(CFLAGS) -o merge.o merge.c

bisect.o: bisect.c
	$(CC) -c $(CFLAGS) -o bisect.o bisect.c
