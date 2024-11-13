#!/bin/bash

echo "Enter the string to search:"
read searchString

echo "Enter the file name to search in:"
read fileName

if [ ! -f "$fileName" ]; then
    echo "File not found!"
    exit 1
fi

grep "$searchString" "$fileName"

if [ $? -eq 0 ]; then
    echo "String '$searchString' found in the file '$fileName'."
else
    echo "String '$searchString' not found in the file '$fileName'."
fi
