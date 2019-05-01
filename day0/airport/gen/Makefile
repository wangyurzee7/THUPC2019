
CXX_FLAGS = -Wall -O3

run: ../cy/std.exe random.exe
	python run.py

../cy/std.exe: ../cy/std/airport.cpp
	make -C ../cy

random.exe: random.cpp
	g++ $< -o $@ $(CXX_FLAGS)

clean:
	make -C ../cy clean
	-rm *.exe