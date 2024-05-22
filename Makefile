# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -std=c++20 -I./SDL2.framework/Headers

# Debug compiler flags
DEBUG_CFLAGS = -g  # Add debugging information

# Linker flags to include the SDL2 framework
LDFLAGS = -F. -framework SDL2

# Source files
SRC := $(shell find . -type f -name '*.cpp')

# Executable names
RELEASE_EXE = release
DEBUG_EXE = debug

# Phony targets
.PHONY: all clean run restart all_debug rebuild

all: release

release: $(RELEASE_EXE)

debug: $(DEBUG_EXE)

$(RELEASE_EXE): $(SRC)
	$(CC) $(CFLAGS) $^ -o $(RELEASE_EXE) $(LDFLAGS)
	install_name_tool -add_rpath @loader_path/ $(RELEASE_EXE)

$(DEBUG_EXE): $(SRC)
	$(CC) $(DEBUG_CFLAGS) $(CFLAGS) $^ -o $(DEBUG_EXE) $(LDFLAGS)
	install_name_tool -add_rpath @loader_path/ $(DEBUG_EXE)

clean:
	rm -f $(RELEASE_EXE) $(DEBUG_EXE)

run: release
	./$(RELEASE_EXE)

run_debug: debug
	./$(DEBUG_EXE)

restart: clean all run

# New target for debug build
rebuild: clean debug
