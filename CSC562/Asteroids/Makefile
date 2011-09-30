all: asteroids


asteroids: asteroids.o tardis.o asteroid.o dalek.o draw.o
	gcc -lGL -lglut -lGLU -std=c++0x asteroids.o tardis.o asteroid.o dalek.o draw.o -o asteroid

asteroids.o: asteroids.cpp asteroids.h tardis.h asteroid.h
	gcc -lGL -lglut -lGLU -std=c++0x asteroids.cpp -c
	
asteroid.o: asteroid.cpp asteroid.h
	gcc -lGL -lglut -lGLU -std=c++0x asteroid.cpp -c	
	
tardis.o: tardis.cpp tardis.h
	gcc -lGL -lglut -lGLU -std=c++0x tardis.cpp -c

dalek.o: dalek.cpp dalek.h
	gcc -lGL -lglut -lGLU -std=c++0x dalek.cpp -c
	
draw.o: draw.cpp draw.h
	gcc -lGL -lglut -lGLU -std=c++0x draw.cpp -c
    
clean: 
	rm *.o

