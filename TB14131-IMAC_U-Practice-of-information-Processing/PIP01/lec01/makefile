CC      = gcc
CFLAGS  = -g -Wall
RM      = rm -rf
FILE    = 

default: build

all: build

build: $(FILE).c
	$(CC) $(CFLAGS) -o $(FILE) $(FILE).c -lm

execute: $(FILE)
	./$(FILE)

run: $(FILE)
	$(RM) $(FILE)
	$(CC) $(CFLAGS) -o $(FILE) $(FILE).c -lm
	./$(FILE)
	$(RM) $(FILE)

debug: $(FILE)
	$(RM) $(FILE)
	$(CC) $(CFLAGS) -o $(FILE) $(FILE).c -lm
	./$(FILE)
	$(RM) $(FILE)

clean:
	$(RM) $(FILE)
