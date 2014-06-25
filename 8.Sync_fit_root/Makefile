all:
	g++ -g -o sync sync_fit.C ReadBinary.cpp `root-config --cflags --glibs` && ./sync

clear:
	rm -f *.o
clean:
	rm -f *.o sync                                                      
