CC = gcc
INC = -I
FLAGS = --std=c99 -W -Wall -g -D_GNU_SOURCE
LINKOPTS = -lpthread

all: msort check differr
	./check

msort: msort.c
	$(CC) $(INC) $(FLAGS) msort.c -o msort  $(LINKOPTS)
	
check: check.c
	$(CC) $(INC) $(FLAGS) check.c -o check $(LINKOPTS) 
	
differr: differr.c
	$(CC) $(INC) $(FLAGS) differr.c -o differr $(LINKOPTS)

clean:
	rm -rf msort || true
	rm -rf check || true
	rm -rf differr || true
