# File name :- makefile
# Licence:- GNU GPL v3
# Project Name:- RainGL

raingl : main.o
	g++ -Wall -g -o raingl main.o -lglut -lGL -lGLU -lm

main.o : main.cpp
	g++ -Wall -g -c main.cpp

clean : 
	rm *.o *.h.gch raingl a.out

rmback : 
	rm *~
