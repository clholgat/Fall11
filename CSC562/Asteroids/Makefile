all: asteroids


asteroids: asteroids.o tardis.o
	gcc -lGL -lglut -lGLU -std=c++0x asteroids.o tardis.o -o client

asteroids.o: asteroids.cpp asteroids.h tardish.h
	gcc -lGL -lglut -lGLU -std=c++0x asteroids.cpp -c
	
tardis.o: tardis.cpp tardis.h tardish.h
	gcc -lGL -lglut -lGLU -std=c++0x tardis.cpp -c
    
clean: 
	rm *.o

