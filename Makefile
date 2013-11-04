# File name :- makefile
# Licence:- GNU GPL v3
# Project Name:- RainGL

raingl : temp.o
	g++ -Wall -g -o raingl temp.o -lglut -lGL -lGLU -lm -lSDL -lSDL_image

temp.o : temp.cpp
	g++ -Wall -g -c temp.cpp

clean : 
	rm *.o *.h.gch raingl a.out

rmback : 
	rm *~
