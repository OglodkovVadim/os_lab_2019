CC=gcc
CFLAGS=-I.

all : min_max

min_max : sequential_min_max parallel_min_max

task4 : proc_mem parallel_min_max 

parallel_sum : 
	$(CC) -o parallel_sum -c parallel_sum.c $(CFLAGS)

myExec : utils.o find_min_max.o sequential_min_max utils.h find_min_max.h
	$(CC) -o exec_out find_min_max.o utils.o myExec.c $(CFLAGS)

sequential_min_max : utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -o sequential_min_max find_min_max.o utils.o sequential_min_max.c $(CFLAGS)

parallel_min_max : utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -o parallel_min_max utils.o find_min_max.o parallel_min_max.c $(CFLAGS)

utils.o : utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)

find_min_max.o : utils.h find_min_max.h
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)

proc_mem : 
	$(CC) -o proc_mem -c process_memory.c $(CFLAGS)

clean :
	rm utils.o find_min_max.o parallel_min_max
