#!/bin/sh

echo "== Compiling =="

g++ val.cpp -O2 -o val

echo
echo "== The following should fail =="

for i in {1..4}; do
    echo Case $i
    ./val < ./$i.in
done

echo
echo "== The following system tests should pass =="

for i in {1..8}; do
    echo Case $i
    ./val < ../data/$i.in
done
