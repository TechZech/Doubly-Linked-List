all: mydriver.x driver.x

mydriver.x: mydriver.o
	g++ -o mydriver.x mydriver.o

driver.x: driver.o
	g++ -o driver.x driver.o

mydriver.o: mydriver.cpp tlist.h tlist.hpp tnode.h
	g++ -c mydriver.cpp -std=c++11

driver.o: driver.cpp tlist.h tlist.hpp tnode.h
	g++ -c driver.cpp -std=c++11

clean:
	rm -f *.o mydriver.x driver.x
