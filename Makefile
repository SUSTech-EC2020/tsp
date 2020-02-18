objects = main.o Utils.o 
compiler= g++
cflags  = -c -g -std=c++11 -stdlib=libc++

libs=

TSP : $(objects)
	$(compiler) -o TSP $(objects) $(libs) -L.
mainPro.o: main.cpp
	$(compiler) $(cflags) main.cpp
Utils.o : Utils.cpp
	$(compiler) $(cflags) Utils.cpp
clean :
	-rm -f TSP
	-rm -f *.o
