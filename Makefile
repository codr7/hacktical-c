export CC=ccache gcc
export CFLAGS=-g -O0 -Wall -I.
CHAPTERS=build/error.o build/fix.o build/list.o build/task.o build/time.o build/vector.o

build/test: clean tests.c $(CHAPTERS) 
	$(CC) $(CFLAGS) tests.c $(CHAPTERS) -o build/test
	valgrind build/test

build/benchmark: clean benchmarks.c $(CHAPTERS) 
	$(CC) $(CFLAGS) benchmarks.c $(CHAPTERS) -o build/benchmark
	build/benchmark

build/error.o:
	$(MAKE) -C error

build/fix.o:
	$(MAKE) -C fix

build/list.o:
	$(MAKE) -C list

build/task.o:
	$(MAKE) -C task

build/time.o:
	$(MAKE) -C time

build/vector.o:
	$(MAKE) -C vector

clean:
	rm -f build/*
