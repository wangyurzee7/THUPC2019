echo 1 >1.in
echo 10 >2.in
echo 10000 >3.in
echo 10000000 >4.in
echo 20190106 >5.in
echo 20190107 >6.in
echo 20190108 >7.in
echo 20190109 >8.in
echo 23333333 >9.in
echo 2148473647 >10.in

for ((i=1;i<=6;++i)); do
	echo "yes" >$i.ans
done
for ((i=7;i<=10;++i)); do
	echo "no" >$i.ans
done
