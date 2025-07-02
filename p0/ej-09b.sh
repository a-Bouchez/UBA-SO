#!/bin/bash

echo -n "Número 1? "
read n1
echo -n "Número 2? "
read n2

s=$(( n1 + n2 ))
p=$(( n1 * n2 ))

echo "La suma es $s y el producto es $p"
