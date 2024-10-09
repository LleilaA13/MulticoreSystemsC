# Variables
CC = mpicc                      # Use mpicc for MPI programs
CFLAGS = -Wall -g        # Compiler flags
LDFLAGS =                        # Add any additional libraries here (if needed)
SRC = mpilect4helloworld.c     # Source files
OBJ = $(SRC:.c=.o)               # Object files
TARGET = esempioMPI          # Name of the final executable

# Number of processes (for running the MPI program, not for compiling)
NP = 4                           # Default number of processes

# Default target: this is the first target and will be run by default when you run 'make'
all: $(TARGET)

# Rule to build the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build object files from .c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove compiled files
.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)

# Rule to run the MPI program with the specified number of processes
.PHONY: run
run: $(TARGET)
	mpirun -np $(NP) ./$(TARGET)
