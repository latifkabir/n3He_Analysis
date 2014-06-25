all:
	g++ -g -o sync llsq_prb_v2.cpp llsq.cpp ReadBinary.cpp `root-config --cflags --glibs` && ./sync

clear:
	rm -f *.o
clean:
	rm -f *.o sync                                                      
