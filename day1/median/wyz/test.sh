make gen
SEED=$((RANDOM*32768+RANDOM))
echo $SEED >seed.txt
echo $SEED
./gen $SEED 3000 3000 >input.in

echo std:
time ./std <input.in >std.out
echo =========
echo log:
time ./log <input.in >log.out
if diff std.out log.out >diff.log.txt; then
	echo AC
else
	echo WA
fi

