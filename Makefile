# Compiler
CC = gcc

# Common Include Paths
INCLUDES = -I./src -I./tests -I./fff -I./Unity/src

# Compiler flags
CFLAGS = -Wall $(INCLUDES)

# Unity and FFF flags for CI
ifdef CI
	CFLAGS += -DUNITY_OUTPUT_CHAR=ci_putchar -DUNITY_EXCLUDE_FLOAT
endif

# Source files
SRC = src/state_machine.c
UNITY_SRC = Unity/src/unity.c
FFF_SRC = fff/fff.c  # Add this if you use fff.c (not just fakes via headers)

# CI-only putchar redirect
CI_PUTCHAR_SRC = tests/ci_output.c

# Test source files
TEST_SRC = tests/test_state_machine.c $(SRC) $(UNITY_SRC) $(FFF_SRC)

# Add ci_output.c for CI environments only
ifdef CI
	TEST_SRC += $(CI_PUTCHAR_SRC)
endif

# Object conversions
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
