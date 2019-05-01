all: std force

D_FLAGS="-D__TUACK__ -std=c++11 -O2"

std: std.cpp
	g++ std.cpp -o std ${D_FLAGS}

force: force.cpp
	g++ force.cpp -o force ${D_FLAGS}

clean:
	rm std force
