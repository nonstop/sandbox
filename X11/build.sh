#!/bin/sh

set -e
for d in ex1 ex2 ex3 ex4 ex5; do
    cd $d
    tcc *.c -o $d -lX11
    cd ..
done
