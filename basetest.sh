#!/bin/bash

TESTDIR="./testfiles"
EXE="./a.out"

case $1 in
    pa02.c)
        rm -f -- $EXE
        gcc pa02.c
        if [ $? -ne 0 ]; then 
            echo "Compile of pa02.c failed"
            echo "Good bye!"
            exit 1 
        fi
        ;;
    *)
        echo "Invalid source file name"
        echo "-> Only pa02.c is supported in this test script."
        exit 1
        ;;
esac

for file in "$TESTDIR"/in*.txt; do
    name=$(basename "$file")
    echo "Processing: $name"
    for bit in 8 16 32; do
        eval $EXE "$file" "$bit"
    done
done