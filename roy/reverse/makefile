CC=gcc
CFLAGS=-O0 -I. -L.

TARGETS=lab1 lab2 lab3 lab4

all: $(TARGETS)

lab1: lab1.c
lab2: lab2.c

lab3: lab3.c lab3_lib.c lab3_lib.h
	$(CC) $(CFLAGS) -c lab3.c -o lab3.o

	# Static library
	# $(CC) $(CFLAGS) -c lab3_lib.c -o lab3_lib.o
	# $(AR) rvs liblab3_lib.a lab3_lib.o

	# Create shared library
	$(CC) $(CFLAGS) -fPIC -c lab3_lib.c
	$(CC) $(CFLAGS) -shared -o liblab3_lib.so lab3_lib.o

	$(CC) $(CFLAGS) lab3.o -llab3_lib -o $@
	strip --strip-all liblab3_lib.so
	# $(CC) $(CFLAGS) lab3.o liblab3_lib.a -o $@

lab4: lab4.c md5.c
	$(CC) $(CFLAGS) -c lab4.c -o lab4.o
	$(CC) $(CFLAGS) -c md5.c -o md5.o
	$(CC) $(CFLAGS) lab4.o md5.o -o $@

.PHONY: clean

clean:
	rm -f $(TARGETS) *.o *.a *.so *.txt
	rm -f .gdb_history

# pattern
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
