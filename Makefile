CFLAGS=-std=c++11

diceware : diceware.o
	g++ diceware.o -o diceware

diceware.o : diceware.cpp
	g++ ${CFLAGS} -c diceware.cpp

clean :
	rm *.o

cleanall : clean
	rm diceware
