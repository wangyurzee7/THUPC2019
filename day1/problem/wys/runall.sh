#!/bin/bash

for ((i=1;i<=7;i++)) do
	echo "Run $i" &&
	python3 vali.py < ../data/$i.in &&
	echo "Vali ok" &&
	time ./std.exe < ../data/$i.in > tmp.out &&
	diff -s -b ../data/$i.ans tmp.out | head -n 1 &&
	rm tmp.out
done
