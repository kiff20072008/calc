all: calc

calc: main.o conio.o calculator.o error.o functions.o variables.o
	g++ main.o conio.o calculator.o error.o functions.o variables.o -o calc
	
main.o: main.c
	g++ -c main.c

calculator.o: calculator.c
	g++ -c calculator.c

conio.o: conio.c
	g++ -c conio.c

error.o: error.c
	g++ -c error.c
	
functions.o: functions.c
	g++ -c functions.c

variables.o: variables.c
	g++ -c variables.c

clean:
	rm -rf *.o calc