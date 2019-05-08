#!/bin/sh

echo "== Compiling =="
g++ val.cpp -O2 -o val

echo "== This should fail because n > 1 =="
./val 1 < ../down/1.in

echo "== This should fail because k != 30 =="
./val 7 < ../down/1.in

echo "== This should fail beacause there are duplicate schools =="
./val < ./dup-school.in

echo "== Should not fail from now on =="

for i in {1..3}; do
    echo "-- Sample #$i --"
    ./val < ../down/$i.in
done

for i in {1..10}; do
    echo "-- Test #$i --"
    ./val $i < ../data/$i.in
done

echo "== Cleaning up =="
rm val
