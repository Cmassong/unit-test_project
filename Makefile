# Compiler
CC = gcc

# Common Include Paths
INCLUDES = -I./src -I./tests -I./fff -I./Unity/src

# Compiler flags
CFLAGS = -Wall $(INCLUDES)

# Additional CI/Unity-specific flags
ifdef CI
	CFLAGS += -DUNITY_OUTPUT_CHAR=ci_putchar -DUNITY_EXCLUDE_FLOAT
endif

# Production Source Files
SRC = src/state_machine.c

# Unity core
UNITY_SRC = Unity/src/unity.c

# CI-only putchar redirect (only added in CI builds)
CI_PUTCHAR_SRC = tests/ci_output.c

# Source files for tests
TEST_SRC = tests/test_state_machine.c $(SRC) $(UNITY_SRC)

# Add CI putchar file in CI builds
ifdef CI
	TEST_SRC += $(CI_PUTCHAR_SRC)
endif

# Object file conversion
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

# Clean up build artifacts
clean:
	rm -f src/*.o tests/*.o $(PROD_TARGET).exe $(TARGET).exe test_results.txt program_output.txt

.PHONY: all test clean run
