for ((i=1;i<=8;++i)); do
	time ./log <dmk/$i.in >output.out
	if diff output.out dmk/$i.ans >$i.difflog.txt; then
		echo $i:AC
	else
		echo $i:WA
	fi
done
