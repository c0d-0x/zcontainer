# Compiler and flags
CC = g++
CFLAGS = -g -Wall -Wextra -Wformat-security -pedantic
# Debugging params 
# CFLAGS += -fsanitize=address
# CFLAGS += -fno-omit-frame-pointer
# CFLAGS += -fsanitize-recover=address

LIBS = 
MAIN = main.cpp

# Source and object files
CFILES = ./src/*.cpp
OBJFILES = *.o  

# Target binaries
BINARY = zcontainer
BIN = bin

# Main target
all: $(BIN)/$(BINARY)
	@echo "Build Complete..."


# Build executable
$(BIN)/$(BINARY): $(OBJFILES)
	@$(CC) $(CFLAGS) $(LIBS) $(MAIN) -o $@ $^

# Compile source files
$(OBJFILES): $(CFILES)
	@$(CC) $(CFLAGS) -c $^ 


# Phony target (no actual command)
.PHONY: run clean uninstall all test

run:all
	@sudo $(BIN)/$(BINARY)
# Clean target
clean:
	@rm *.o $(BIN)/* 

