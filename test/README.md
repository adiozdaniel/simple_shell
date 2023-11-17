# THE GATES OF HELL

This **SIMPLE SHELL** program was written entirely in C as a milestone project for ALX Africa Software Engineering. It replicates functionalities of UNIX shell (sh).

## Usage

### On normal use

* Compile it using ```gcc -Wall -Werror -Wextra -pedantic -std=gnu89 ../*.c -o hsh```
* run ```./hsh```

### If you add a feature or improvement and want to test

## memory testing

* You can copy the original .C function in the [compare](./compare.md) before modifying it.
* Make sure you link it with all the dependencies.
* Also make sure that it doesn't run with any memory leaks, as is.

```C
sudo apt-get install valgrind
gcc -g -o hsh ../ *.c
valgrind --leak-check=full -v ./hsh

```

### Usage of this Simple shell program

After compilation, the resulting program can run stand-alone, either in interactive or non-interactive mode.
