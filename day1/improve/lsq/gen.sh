#!/bin/bash

compile() {
    echo "Compiling $1.cpp -> $2"
    g++ "$1.cpp" -std=c++11 -O2 -o "$2"
}

compile sol sol
compile wa-1 wa-1
compile wa-2 wa-2
compile wa-flow wa-flow
compile gen gen
compile ../wyz/std std

cp ../down/1.in .
cat > 2.in <<EOF
2 1
2 1
1 1
1 2
EOF
cat > 3.in <<EOF
2 1
2 1
1 1
2 1
EOF
./gen linear 5 7 Seed=3 > 4.in
./gen linear 5 8 > 5.in
./gen linear 10 6 > 6.in
./gen linear 10 15 > 7.in
./gen linear 10 40 > 8.in
./gen majime 15 30 9 15 3 5 > 9.in
./gen broom 15 36 > 10.in

./gen linear 700 200 > 11.in
./gen linear 700 2000 > 12.in       # Same answers for 11, 12, 13?
./gen linear 700 60000 OuO > 13.in  # So to me seems line a notorious coincidence
./gen linear 700 60000 OvO > 14.in
./gen linear 700 60000 OwO > 15.in
./gen majime 200 400 125 250 25 40 > 16.in
./gen majime 300 800 250 450 25 60 > 17.in
./gen majime 400 2000 320 1000 30 80 > 18.in
./gen majime 500 2000 250 750 50 250 > 19.in
./gen majime 600 10000 551 1551 15 51 > 20.in

./gen majime 700 700 300 300 200 400 > 21.in
./gen majime 700 3000 400 1200 100 400 > 22.in
./gen majime 700 10000 450 1350 100 500 > 23.in
./gen majime 700 30000 550 2550 52 252 > 24.in
./gen majime 700 45000 650 10000 25 255 > 25.in

./gen majime 700 60000 40 80 200 500 > 26.in
./gen majime 700 60000 120 400 120 8000 > 27.in
./gen majime 700 60000 200 5000 150 10000 > 28.in
./gen majime 700 60000 350 5000 20 40 > 29.in
./gen majime 700 60000 650 12000 20 40 > 30.in

./gen majime 700 60000 300 15000 50 1500 > 31.in
./gen majime 700 60000 350 15000 150 1500 > 32.in
./gen majime 700 60000 350 25000 50 1500 > 33.in
./gen majime 700 60000 350 35000 50 150 > 34.in
./gen majime 700 60000 350 45000 5 15 > 35.in

./gen majime 700 60000 700 60000 0 0 > 36.in
./gen majime 700 60000 1 0 50 50 > 37.in
./gen broom 700 702 > 38.in
./gen broom 700 60000 > 39.in
./gen maxans 700 0 > 40.in

for i in {1..40}; do
    echo "Validating case $i"
    python3 ../wyz.validate/vali.py < $i.in
    echo "Testing case $i"
    ./std < $i.in > $i.ans
    cat $i.ans
    diff <(./sol < $i.in) $i.ans || exit
    #diff <(./wa-1
done

assert_incorrect() {
    echo "Incorrect solution $1"
    for i in {1..40}; do
        echo "Testing case $i"
        diff <("./$1" < $i.in) $i.ans || break
    done
}

assert_incorrect wa-1
assert_incorrect wa-2
assert_incorrect wa-flow
