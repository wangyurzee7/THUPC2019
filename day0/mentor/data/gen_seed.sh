if [ -e seed.txt ]
then
    mv seed.txt seed.bak
fi
touch seed.txt
for ((i=1;i<=10;++i))
do
    echo $((RANDOM*32768+RANDOM)) >> seed.txt
done