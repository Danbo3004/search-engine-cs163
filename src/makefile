main: ./main.cpp ./helpers/helpers.cpp ./helpers/helpers.h ./view/View.cpp ./view/View.h ./operators/wordopr.cpp ./operators/wordopr.h ./autotype/AutoTrie.cpp ./autotype/AutoTrie.h ./searchFile/searchFile.cpp ./searchFile/searchFile.h ./inTitle/inTitle.h ./inTitle/inTitle.cpp ./synonym/synonym.h ./synonym/synonym.cpp ./price/price.h ./price/price.cpp
	g++ -std=c++11 -Wall -c ./helpers/helpers.cpp -o helpers.o
	# g++ -std=c++11 -Wall -c ./view/View.cpp -o view.o
	g++ -std=c++11 -Wall -c ./operators/wordopr.cpp -o wordopr.o
	g++ -std=c++11 -Wall -c ./autotype/AutoTrie.cpp -o autotrie.o
	g++ -std=c++11 -Wall -c ./searchFile/searchFile.cpp -o searchfile.o
	g++ -std=c++11 -Wall -c ./inTitle/inTitle.cpp -o inTitle.o
	g++ -std=c++11 -Wall -c ./price/price.cpp -o price.o
	g++ -std=c++11 -Wall -c ./synonym/synonym.cpp -o synonym.o
	g++ -std=c++11 -Wall ./main.cpp -o main *.o
log:
	rm -f log.txt
clean: log
	rm -f main *.o

