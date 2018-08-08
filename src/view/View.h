#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <fstream>
#include <ctime>		           	 // For Displaying time
#include <climits>
#include <string>
#include <set>
#include <vector>

//-------------not cross-platform-----------------------------------------------------------------------------------------
#include <windows.h>
#include <conio.h>
///-----------------------------------------------------------------------------------------------------------------------


#include "../helpers/helpers.h"
#include "../autotype/AutoTrie.h"
#include "../operators/wordopr.h"

namespace view{
	class View{
	private:
		std::set<std::string> stopwordsSet;
		AutoTrie trie;
		WordsInFiles wordsInFiles;
	public:
		View();
		void searchView();
		void resultView(); //pass in object
		void gotoxy(int , int );
		void time();
		void typeInput(std::string& field, const int& fieldLim = INT_MAX);
		COORD GetConsoleCursorPosition(HANDLE);
		void title();
		void history(const string&, std::vector<std::string>&);
		std::vector<FileResult> searchFor(std::string&);
	};

}
#endif


