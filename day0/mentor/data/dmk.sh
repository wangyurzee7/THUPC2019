if [ ! -e seed.txt ]
then
    ./gen_seed.sh
fi
./gen_in.sh
./get_ans.sh
