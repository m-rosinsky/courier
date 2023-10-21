################################################################################
#								Vars										   #
################################################################################

# Compiler selection.
CC=g++

# CPP Standard.
CSTD=11

# Compiler flags.
CFLAGS_RELEASE=-Wall -Wextra -pedantic -std=c++$(CSTD)
CFLAGS=$(CFLAGS_RELEASE) -g

# Source directory.
SRCS=src

# Test directory.
TEST=test

# Static object directory.
OBJS=objs

# Binary directory.
BINS=bins

################################################################################
#								Rules										   #
################################################################################

# Debug Rules.
all: setup compile link

# Release build.
release: setup compile-release link-release

################################################################################
#								Debug										   #
################################################################################

setup:
	@echo "Creating subdirectories..."

	@mkdir -p $(OBJS)
	@echo "  [+] Created ./$(OBJS)"

	@mkdir -p $(BINS)
	@echo "  [+] Created ./$(BINS)"

	@echo "Done!"

compile: setup
	@echo "Compiling sources (debug)..."

# Compile error.
	@$(CC) $(CFLAGS) -o $(OBJS)/error.o -c $(SRCS)/error/error.cpp
	@echo "  [+] Compiled ./$(SRCS)/error/error.cpp"

# Compile lexer.
	@$(CC) $(CFLAGS) -o $(OBJS)/lexer.o -c $(SRCS)/lexer/lexer.cpp
	@echo "  [+] Compiled ./$(SRCS)/lexer/lexer.cpp"

# Compile objects.
	@$(CC) $(CFLAGS) -o $(OBJS)/object_signed_int.o -c $(SRCS)/object/object_signed_int.cpp
	@echo "  [+] Compiled ./$(SRCS)/object/object_signed_int.cpp"

	@$(CC) $(CFLAGS) -o $(OBJS)/object_unsigned_int.o -c $(SRCS)/object/object_unsigned_int.cpp
	@echo "  [+] Compiled ./$(SRCS)/object/object_unsigned_int.cpp"

# Compile parser.
	@$(CC) $(CFLAGS) -o $(OBJS)/var_handler.o -c $(SRCS)/parser/var_handler/var_handler.cpp
	@echo "  [+] Compiled $(SRCS)/parser/var_handler/var_handler.cpp"

	@echo "Done!"

link: setup compile
	@echo "Linking binaries (debug)..."

# Link main.
	@$(CC) $(CFLAGS) -o $(BINS)/courier $(SRCS)/main.cpp $(OBJS)/*.o
	@echo "  [+] Created binary ./$(BINS)/courier"

	@echo "Done!"

################################################################################
#								Release										   #
################################################################################

compile-release: setup
	@echo "Compiling sources..."

# Compile error.
	@$(CC) $(CFLAGS_RELEASE) -o $(OBJS)/error.o -c $(SRCS)/error/error.cpp
	@echo "  [+] Compiled ./src/error/error.cpp"

# Compile lexer.
	@$(CC) $(CFLAGS_RELEASE) -o $(OBJS)/lexer.o -c $(SRCS)/lexer/lexer.cpp
	@echo "  [+] Compiled ./src/lexer/lexer.cpp"

# Compile objects.
	@$(CC) $(CFLAGS_RELEASE) -o $(OBJS)/object_signed_int.o -c $(SRCS)/object/object_signed_int.cpp
	@echo "  [+] Compiled ./$(SRCS)/object/object_signed_int.cpp"

	@$(CC) $(CFLAGS_RELEASE) -o $(OBJS)/object_unsigned_int.o -c $(SRCS)/object/object_unsigned_int.cpp
	@echo "  [+] Compiled ./$(SRCS)/object/object_unsigned_int.cpp"

# Compile parser.
	@$(CC) $(CFLAGS_RELEASE) -o $(OBJS)/var_handler.o -c $(SRCS)/parser/var_handler/var_handler.cpp
	@echo "  [+] Compiled $(SRCS)/parser/var_handler/var_handler.cpp"

	@echo "Done!"

link-release: setup compile-release
	@echo "Linking binaries..."

# Link main.
	@$(CC) $(CFLAGS_RELEASE) -o $(BINS)/courier $(SRCS)/main.cpp $(OBJS)/*.o
	@echo "  [+] Created binary ./$(BINS)/courier"

	@echo "Done!"

################################################################################
#								Test 										   #
################################################################################

test: setup compile
	@echo "Compiling test libraries..."

# Compile lexer test functions.
	@$(CC) $(CFLAGS) -o $(OBJS)/test_lexer.o -c $(TEST)/test_lexer.cpp
	@echo "  [+] Compiled $(OBJS)/test_lexer.o"

# Compile lexer test functions.
	@$(CC) $(CFLAGS) -o $(OBJS)/test_object.o -c $(TEST)/test_object.cpp
	@echo "  [+] Compiled $(OBJS)/test_object.o"

# Compile var test functions.
	@$(CC) $(CFLAGS) -o $(OBJS)/test_var.o -c $(TEST)/test_var.cpp
	@echo "  [+] Compiled $(OBJS)/test_var.o"

# Compile unit test library.
	@$(CC) $(CFLAGS) -o $(OBJS)/courier_test.o -c $(TEST)/courier_test/courier_test.cpp
	@echo "  [+] Compiled $(OBJS)/courier_test.o"

	@echo "Done!"

	@echo "Linking test binaries..."

# Link test main.
	@$(CC) $(CFLAGS) -o $(BINS)/test_main $(TEST)/test_main.cpp $(OBJS)/*.o
	@echo "  [+] Created binary ./$(BINS)/test_main"

	@echo "Done!"

################################################################################
#								Clean										   #
################################################################################

clean:
	@echo "Cleaning..."

	@$(RM) -rf $(OBJS)
	@echo "  [-] Removed ./$(OBJS)"

	@$(RM) -rf $(BINS)
	@echo "  [-] Removed ./$(BINS)"

	@echo "Done!"
