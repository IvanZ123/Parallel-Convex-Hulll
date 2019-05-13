wrap: wrapping.cpp
	g++ -g -o wrap wrapping.cpp ch_helper.cpp
brute: brute_force.cpp
	g++ -g -o  brute brute_force.cpp ch_helper.cpp
graham: graham_scan.cpp
	g++ -g -o  graham graham_scan.cpp 
para_wrap: para_wrap.cpp
	g++ -g -o para_wrap -fopenmp para_wrap.cpp para_helper.cpp
clean:
	rm -f *.o wrap graham brute
