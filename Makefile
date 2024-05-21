# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -std=c++20 -I./SDL2.framework/Headers

# Linker flags to include the SDL2 framework
LDFLAGS = -F. -framework SDL2

# Source files
SRC := $(shell find . -type f -name '*.cpp')

# Executable name
EXE = output

all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) $^ -o $(EXE) $(LDFLAGS)
	install_name_tool -add_rpath @loader_path/ $(EXE)

clean:
	rm -f $(EXE)

run: $(EXE)
	./$(EXE)

.PHONY: all clean run

restart: clean all run
