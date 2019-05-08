make validate
for ((i=1;i<=10;++i)); do
	./validate ../data/$i.in $i
done
