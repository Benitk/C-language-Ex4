CC = gcc
AR = ar
FLAGS = -Wall -g

# $@ - the file on the left side of the :
# $< - the first name in the dependencies list
# $^ - the right side of :

all: frequency
frequency: main.o frequency.o
	$(CC) $(FLAGS) -o $@ $^
frequency.o: frequency.c frequency.h
	$(CC) $(FLAGS) -fPIC -c $<
main.o: main.c frequency.h
	$(CC) $(FLAGS) -c $<

.PHONY: clean all

clean:
	rm -f *.o frequency
