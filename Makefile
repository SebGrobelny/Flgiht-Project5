simulator.out: airport.o main.o plane.o city.o
	g++ -Wall -ansi -g -lm -o simulator.out airport.o main.o  plane.o city.o

city.o: city.cpp city.h
	g++ -Wall -ansi -g -c city.cpp 

airport.o: airport.cpp airport.h city.h list.h list.cpp
	g++ -Wall -ansi -g -c airport.cpp

main.o: main.cpp plane.h airport.h city.h list.h list.cpp
	g++ -Wall -ansi -g -c main.cpp

plane.o: plane.cpp plane.h
	g++ -Wall -ansi -g -c plane.cpp

clean:
	rm -f simulator.out airport.o main.o plane.o city.o
