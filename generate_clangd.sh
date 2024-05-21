#!/bin/bash

# Get the current working directory
CURRENT_PWD=$(pwd)

# Create or overwrite the .clangd file
cat <<EOL > .clangd
If:
  PathMatch: .*\\.cpp|.*\\.h

CompileFlags:
  Add: 
    - -std=c++20
    - -Wall
    - -Wextra
    - -I$CURRENT_PWD/SDL2.framework/Headers
    - -F$CURRENT_PWD
    - -framework
    - SDL2
EOL

echo ".clangd file generated with PWD: $CURRENT_PWD"
