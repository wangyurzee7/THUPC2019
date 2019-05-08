n=(1 10 20 30 30 500 500 500 1000 1000)
c=(1 10 20 30 30 500 30 500 1000 1000)
k=(1 10 0 0 30 0 30 30 0 30)
m=(1 100 100 100 500 1000 1000 1000 2500 2500)

seedList=$(cat seed.txt)
make gen
i=0
for seed in $seedList; do
    echo "./gen $seed ${n[i]} ${c[i]} ${k[i]} ${m[i]} 5 >$((i+1)).in"
    ./gen $seed ${n[i]} ${c[i]} ${k[i]} ${m[i]} 5 >$((i+1)).in
    ((++i))
done
