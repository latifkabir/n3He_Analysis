all:
	g++ -g -o compare_ch src/compare_ch.cpp src/ReadBinary.cpp `root-config --cflags --glibs` && ./compare_ch

clear:
	rm -f src/*.o
clean:
	rm -f src/*.o compare_ch                                                      
