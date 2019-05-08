make gen
cd ../wyz; make std; cd ../data; cp ../wyz/std ./
./gen 19260817 30 20 10 500 1 >../down/2.in
./gen 19260817 500 250 0 800 1 >../down/3.in
./std <../down/2.in >../down/2.ans
./std <../down/3.in >../down/3.ans
