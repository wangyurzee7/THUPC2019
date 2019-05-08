make validate
buffer=''
for ((i=1;;++i))
do
	if [ ! -e "../data/$i.in" ]
	then
		echo Testcase#$i Nout Found.All the datas are checked!
		break
	fi
	./validate ../data/$i.in
	if (($?))
	then
		echo Boooooooooooooom!!!!
		read -n1 -s -p "Press Any Key To Continue..."
		buffer+=${i}', '
	fi
done
echo [ Invalid Testcase Id ]: ${buffer}
