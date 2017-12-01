#!/bin/bash


./fibonacci 0
./fibonacci 1
./fibonacci 2
./fibonacci 3
./fibonacci 4
./fibonacci 5
./fibonacci 6
./fibonacci 7
./fibonacci 8
./fibonacci 9
./fibonacci 10

echo
echo "testing fib(47):"
./fibonacci 47
echo

echo "testing fib(92):"
./fibonacci 92
echo

echo "testing fib(93):"
./fibonacci 93
echo

echo "testing fib(94):"
./fibonacci 94
echo

echo "testing fib(95):"
./fibonacci 95
echo

echo "testing fib(100):"
./fibonacci 100
echo

echo "testing fib(186):"
./fibonacci 186
echo

echo "testing negative number fib(-1):"
./fibonacci -1
echo

echo "testing out of range fib(187):"
./fibonacci 187
echo

echo "testing 3 command line args provided:"
./fibonacci 47 47
echo

echo "testing no command line args provided:"
./fibonacci
echo
