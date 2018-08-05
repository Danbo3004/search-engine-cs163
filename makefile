main: main.cpp ./src/helpers/helpers.cpp ./src/helpers/helpers.h ./src/searchFile/searchFile.cpp ./src/searchFile/searchFile.h ./src/wordopr.h ./src/wordopr.cpp makefile
	g++ -std=c++11 -Wall -c ./src/helpers/helpers.cpp -o helpers.o
	g++ -std=c++11 -Wall -c ./src/searchFile/searchFile.cpp -o searchFile.o
	g++ -std=c++11 -Wall -c ./src/wordopr.cpp -o wordopr.o
	g++ -std=c++11 -Wall main.cpp -o main *.o
clean: 
	rm -f main *.o