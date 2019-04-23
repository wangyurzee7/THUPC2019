./gen 6 7 23333 > data/1.in
./gen 8 6 66666 > data/2.in
./gen 12 4 55555 > data/3.in
./gen 233 2 233333 > data/4.in

./gen 2 19 500000 > data/5.in
./gen 3 12 499999 > data/6.in
./gen 4 9 499998 > data/7.in
./gen 5 8 499997 > data/8.in
./gen 7 7 499995 > data/9.in
./gen 10 6 499992 > data/10.in
./gen 15 5 500000 > data/11.in
./gen 31 4 500000 > data/12.in
./gen 100 3 500000 > data/13.in
./gen 1000 2 500000 > data/14.in
./gen 1000000 1 500000 > data/15.in

for((i=1;i<=15;i++))
do
	time saffah/std < data/$i.in > data/$i.ans
done
