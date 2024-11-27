CC      = gcc
CFLAGS  = -g -Wall
RM      = rm -f  # Use `-f` to avoid errors if the file doesn't exist
FILE    =    # Set to your desired file name without extension

default: build

all: build execute clean

# Build the binary from the C source
build: $(FILE).c
	$(CC) $(CFLAGS) -o $(FILE) $(FILE).c -lm

# Execute the binary if it exists
execute: $(FILE)
	./$(FILE)

# Clean the binary only if it exists
clean:
	-@$(RM) $(FILE)

# Debug: Clean (if needed), compile with debugging symbols, and launch GDB
debug: clean
	$(CC) $(CFLAGS) -o $(FILE) $(FILE).c -lm
	gdb ./$(FILE)
