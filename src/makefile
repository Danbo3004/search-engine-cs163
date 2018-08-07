main: ./main.cpp ./helpers/helpers.cpp ./helpers/helpers.h ./view/View.cpp ./view/View.h ./in-title/in-title.cpp ./in-title/in-title.h
	g++ -std=c++11 -Wall -c ./helpers/helpers.cpp -o helpers.o
	g++ -std=c++11 -Wall -c ./view/View.cpp -o view.o
	g++ -std=c++11 -Wall -c ./operators/wordopr.cpp -o wordopr.o
	g++ -std=c++11 -Wall -c ./in-title/in-title.cpp -o in-title.o
	g++ -std=c++11 -Wall main.cpp -o main *.o
clean:
	rm -f main *.o