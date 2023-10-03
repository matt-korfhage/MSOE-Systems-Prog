# Makefile for compiling source files in the "src" directory

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinc

# Directories
SRCDIR = src
INCDIR = inc
BUILDDIR = build

# Source files and object files
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRCS))

# Target executable
TARGET = minimat

# Default target
all: $(TARGET)

# Linking the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compiling source files to object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the build directory if it doesn't exist
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Clean rule
clean:
	rm -rf $(BUILDDIR) $(TARGET)

.PHONY: all clean
