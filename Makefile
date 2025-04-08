# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -I./src -I./tests -I./fff -I./Unity/src

# Source files for your main project (not the tests)
SRC = src/helloW.c

# Source files for tests (test file + Unity + Fake Functions)
TEST_SRC = tests/test_helloW.c Unity/src/unity.c

# Object files for normal compilation
OBJ = $(SRC:.c=.o)

# Object files for test compilation
TEST_OBJ = $(TEST_SRC:.c=.o)

# Combine all object files for linking
ALL_OBJ = $(OBJ) $(TEST_OBJ)

TARGET = run_tests

# Default target: build and run tests
all: $(TARGET)

# Build the test executable
$(TARGET): $(ALL_OBJ)
	$(CC) $(CFLAGS) -o $(TARGET).exe $(ALL_OBJ)

# Compile C files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET).exe --txt > test_results.txt

# Clean up generated files
clean:
	rm -f src/*.o tests/*.o $(TARGET).exe
