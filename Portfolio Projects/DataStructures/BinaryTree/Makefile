make:
	make proj4.o
	make proj4.x

proj4.o: bet.h bet.cpp
	g++ -std=c++11 -c -o proj4.o bet.cpp

proj4.x: proj4.o proj4_driver.cpp
	g++ -std=c++11 -o proj4.x proj4.o proj4_driver.cpp

clean:
	rm proj4.o proj4.x
