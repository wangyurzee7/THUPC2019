#!/bin/bash

g++ sol.cpp -std=c++11 -O2 -o sol
g++ ../wyz/std.cpp -std=c++11 -O2 -o std
g++ gen.cpp -std=c++11 -O2 -o gen

for i in {1..100}; do
    echo linear $i
    ./gen linear 100 240 Seed=$i > x.in
    diff <(./std < x.in) <(./sol < x.in) || exit
done

for i in {1..100}; do
    echo majime $i
    ./gen majime 180 240 90 150 30 45 Seed=$i > x.in
    diff <(./std < x.in) <(./sol < x.in) || exit
done
