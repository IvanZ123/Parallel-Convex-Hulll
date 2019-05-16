wrap: wrapping.cpp
	g++ -g -o wrap wrapping.cpp ch_helper.cpp
brute: brute_force.cpp
	g++ -g -o  brute brute_force.cpp para_helper.cpp
graham: graham_scan.cpp
	g++ -g -o  graham graham_scan.cpp 
g_scan: g_scan.cpp
	g++ -g -o  g_scan g_scan.cpp para_helper.cpp
para_wrap: para_wrap.cpp
	g++ -g -o para_wrap -fopenmp para_wrap.cpp para_helper.cpp
para_scan: para_scan.cpp
	g++ -g -o para_scan -fopenmp para_scan.cpp
para_wrap2: para_wrap.cpp
	icc  -o para_wrap2 -qopenmp para_wrap.cpp para_helper.cpp
clean:
	rm -f *.o wrap graham brute
