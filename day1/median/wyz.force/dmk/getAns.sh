STD=../std
make ${STD}
for ((i=$1;i<=$2;++i))
do
	time ./${STD} <$i.in >$i.ans
done
