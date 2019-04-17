m=(2 100 400 1000 1000 2333 2666 2666 3000 3000)
n=(100 100 400 1000 1000 2333 2666 2666 3000 3000)
type=(0 0 0 0 2 2 1 0 1 2)

seedList=$(cat seed.txt)

i=0
make gen

for seed in $seedList
do
	echo \.\/gen $seed ${m[i]} ${n[i]} ${type[i]} \>$((i+1)).in
	./gen $seed ${m[i]} ${n[i]} ${type[i]} >$((i+1)).in
	((++i))
done
