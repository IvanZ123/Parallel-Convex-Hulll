wrap: wrapping.cpp
	g++ -g -o wrap wrapping.cpp ch_helper.cpp
brute: brute_force.cpp
	g++ -g -o  brute brute_force.cpp ch_helper.cpp
stam: MST.cpp
	icc -o mst -qopenmp MST.cpp
clean:
	rm -f *.o wrap
