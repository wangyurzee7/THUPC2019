CXX_FLAGS = -Wall -D__TEST__ -O2

std.exe: std/airport.cpp
	g++ $< -o $@ $(CXX_FLAGS)

val.exe: val/val.cpp
	g++ $< -o $@ $(CXX_FLAGS)

val: val.exe std.exe
	python val/main.py

clean:
	rm *.exe