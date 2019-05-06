cd ../wyz
make std
cd ../data
cp ../wyz/std ./
for ((i=1;i<=10;++i))
do
    echo [case$i]:
    time ./std <$i.in >$i.ans
done
