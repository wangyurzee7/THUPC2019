cd ..; make std; cd dmk;
for ((i=1;;++i))
do
	if [ ! -e $i.in ]; then
		break
	fi
	time ./../std <$i.in >$i.ans
done
