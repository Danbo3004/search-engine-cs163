main: ./main.cpp ./helpers/helpers.cpp ./helpers/helpers.h ./view/View.cpp ./view/View.h
	g++ -std=c++11 -Wall -c ./helpers/helpers.cpp -o helpers.o
	g++ -std=c++11 -Wall -c ./view/View.cpp -o view.o
	g++ -std=c++11 -Wall main.cpp -o main *.o
clean:
	rm -f *.o main
