main: ./main.cpp ./helpers/helpers.cpp ./helpers/helpers.h ./view/View.cpp ./view/View.h ./operators/wordopr.cpp ./operators/wordopr.h ./autotype/AutoTrie.cpp ./autotype/AutoTrie.h ./searchFile/searchFile.cpp ./searchFile/searchFile.h ./synonym/synonym.h ./synonym/synonym.cpp
	g++ -std=c++11 -Wall -c ./helpers/helpers.cpp -o helpers.o
	# g++ -std=c++11 -Wall -c ./view/View.cpp -o view.o
	g++ -std=c++11 -Wall -c ./operators/wordopr.cpp -o wordopr.o
	g++ -std=c++11 -Wall -c ./autotype/AutoTrie.cpp -o autotrie.o
	g++ -std=c++11 -Wall -c ./searchFile/searchFile.cpp -o searchfile.o
	g++ -std=c++11 -Wall -c ./synonym/synonym.cpp -o synonym.o
	g++ -std=c++11 -Wall ./main.cpp -o main *.o
clean:
	rm -f main *.o