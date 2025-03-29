# PA02 — Checksum Calculation

This program calculates an 8, 16, or 32-bit checksum for the contents of a given input file using ASCII text. The program follows the specification provided in the CIS3360 "Security in Computing" course.

---

# Description

The program:
- Accepts an input file and checksum size (8, 16, or 32) via command-line arguments
- Reads the file contents as ASCII characters
- Pads the input if necessary
- Prints the formatted input (80 characters per line)
- Computes the checksum
- Outputs the checksum in the specified format

---
# Checksum Padding Rules

- 8-bit: No padding required
- 16-bit: Pads with 'X' if the character count is odd
- 32-bit: Pads with 'X' up to a multiple of 4

# Input assumptions

- All files use standard 8-bit ASCII
- Max input size of 10,000 characters
- Checksum size is 8, 16, or 32 bits

# Author
Peter Petro
PE310601@ucf.edu
UCF CIS3360 – Spring 2025
Instructor: Professor Michael McAlpin

# Note
- Test input files and accompanying bash scripts from test files folder used for validation were provided by Professor McAlpin as part of the CIS3360 course materials. These were used solely for testing and evaluation purposes in accordance with the course guidelines.

# Example output:

(i) amount of checksum is (hexadecimal_value) for all (n) chars "\n"
Processing: filename.txt "\n"
(content of text file) "\n"


// (format modifiers: i = 2 digits  hex: 8 digits chars: 4 digits)

## Compile & Run
# To Compile: 
```bash    gcc -o pa02 pa02.c
# To Execute:
    ./pa02 inputFilename.txt checksumSize
#   where inputFilename.txt is the input file and checksumSize is either 8, 16, or 32

#To run baseTest.sh:
in cmd:
chmod +x basetest.sh # This command adds execute permission to the script file.
./basetest.sh pa02.c # To run script file with pa02c that will take input files from /testfiles/ folder
