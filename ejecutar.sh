#!/bin/bash

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    ./linux/biblioteca
elif [[ "$OSTYPE" == "darwin"* ]]; then
    ./macos/biblioteca
elif [[ "$OSTYPE" == "msys" ]]; then
    ./windows/biblioteca.exe
else
    echo "Sistema operativo no compatible."
    exit 1
fi
