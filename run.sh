#!/bin/bash

# Check if the first parameter is "build"
if [ "$1" = "build" ]; then
    # Run build script
    ./build.sh
fi

# Check if executable exists
if [ -f ./build/main ]; then
    # Run the executable
    ./build/main
else
    echo "Executable 'main' not found. Make sure your build was successful."
fi