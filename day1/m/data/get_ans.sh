g++ ../wyz/std.cpp -o std
for ((i=1;i<=107;++i)); do
	./std <$i.in >$i.ans
done
rm std
