main: ./main.cpp ./helpers/helpers.cpp ./helpers/helpers.h ./view/View.cpp ./view/View.h ./operators/wordopr.cpp ./operators/wordopr.h ./autotype/AutoTrie.cpp ./autotype/AutoTrie.h
	g++ -std=c++11 -Wall -c ./helpers/helpers.cpp -o helpers.o
	g++ -std=c++11 -Wall -c ./view/View.cpp -o view.o
	g++ -std=c++11 -Wall -c ./operators/wordopr.cpp -o wordopr.o
	g++ -std=c++11 -Wall -c ./main.cpp -o main.o
clean:
	rm -f main *.o