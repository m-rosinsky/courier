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
	@echo "  [+] Compiled ./src/error/error.o"

# Compile lexer.
	@$(CC) $(CFLAGS) -o $(OBJS)/lexer.o -c $(SRCS)/lexer/lexer.cpp
	@echo "  [+] Compiled ./src/lexer/lexer.o"

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
	@echo "  [+] Compiled ./src/error/error.o"

# Compile lexer.
	@$(CC) $(CFLAGS_RELEASE) -o $(OBJS)/lexer.o -c $(SRCS)/lexer/lexer.cpp
	@echo "  [+] Compiled ./src/lexer/lexer.o"

	@echo "Done!"

link-release: setup compile-release
	@echo "Linking binaries..."

# Link main.
	@$(CC) $(CFLAGS_RELEASE) -o $(BINS)/courier $(SRCS)/main.cpp $(OBJS)/*.o
	@echo "  [+] Created binary ./$(BINS)/courier"

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
