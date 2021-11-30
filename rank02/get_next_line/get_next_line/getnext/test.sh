#!/bin/bash
echo BUFFER_SIZE = 1
gcc -D BUFFER_SIZE=1 *.c
#  valgrind --leak-check=full --show-leak-kinds=all ./a.out
./a.out

echo BUFFER_SIZE = 42
gcc -D BUFFER_SIZE=42 *.c
#  valgrind --leak-check=full --show-leak-kinds=all ./a.out
./a.out

echo BUFFER_SIZE = 1000
gcc -D BUFFER_SIZE=1000 *.c
#  valgrind --leak-check=full --show-leak-kinds=all ./a.out
./a.out

echo BUFFER_SIZE = 1000000
gcc -D BUFFER_SIZE=1000000 *.c
#  valgrind --leak-check=full --show-leak-kinds=all ./a.out
./a.out
