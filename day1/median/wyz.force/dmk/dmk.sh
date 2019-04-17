CASE_CNT=10

DST=../../data/

if [[ ! -e seed.txt ]]; then
	./genSeed.sh ${CASE_CNT}
fi
./genIn.sh
./getAns.sh 1 ${CASE_CNT}
for ((i=1;i<=${CASE_CNT};++i)); do
	mv $i.in ${DST}/
	mv $i.ans ${DST}/
done