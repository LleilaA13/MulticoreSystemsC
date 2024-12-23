# Variables
CC = gcc                      # Use mpicc for MPI programs
CFLAGS = -Wall -g 			     # Compiler flags
LDFLAGS = -lpthread                   # Add any additional libraries here (if needed)
SRC = EserciziPthreads/histogram.c   # Source files
OBJ = $(SRC:.c=.o)               # Object files
TARGET = histogram   # Name of the final executable
#TOSSES = 1000000     # Number of tosses for the Monte Carlo simulation
# Number of processes (for running the MPI program, not for compiling)
#NP = 6                          # Default number of processes

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

run: $(TARGET)
	mpirun -np $(NP) ./$(TARGET) 