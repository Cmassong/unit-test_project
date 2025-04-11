# Compiler
CC = gcc

# Common Include Paths
INCLUDES = -I./src -I./tests -I./fff -I./Unity/src

# Compiler flags
CFLAGS = -Wall $(INCLUDES)

# Unity and FFF flags for CI
ifdef CI
	CFLAGS += -DUNITY_OUTPUT_CHAR=ci_putchar -DUNITY_EXCLUDE_FLOAT
	TEST_SRC += tests/ci_output.c  # Add ci_output.c for CI
endif

# Source files
SRC = src/state_machine.c
UNITY_SRC = Unity/src/unity.c
FFF_SRC =  # If you use FFF library (add fff/fff.c if you have it)

# Test source files (including Unity and any other dependencies)
TEST_SRC = tests/test_state_machine.c $(SRC) $(UNITY_SRC) $(FFF_SRC)

ifdef CI
	TEST_SRC += tests/ci_output.c  # Ensure ci_output.c is included only in CI
endif

# Object files
OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

# Targets
TARGET = run_tests
PROD_TARGET = program

# Default target
all: $(TARGET)

# Production binary
$(PROD_TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(PROD_TARGET).exe $(OBJ)

# Test binary
$(TARGET): $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $(TARGET).exe $(TEST_OBJ)

# Compilation rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run tests
test: $(TARGET)
	./$(TARGET).exe --txt | tee test_results.txt

# Run production binary
run: $(PROD_TARGET)
	./$(PROD_TARGET).exe > program_output.txt

# Full cleanup
clean:
	rm -f src/*.o \
	      tests/*.o \
	      Unity/src/*.o \
	      fff/*.o \
	      $(PROD_TARGET).exe \
	      $(TARGET).exe \
	      test_results.txt \
	      program_output.txt

.PHONY: all test clean run
