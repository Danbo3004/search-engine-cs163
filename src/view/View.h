//ID: 1751001
//Name: Nguyen Hien Tuan Duy
//Exercise

#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <fstream>
#include <ctime>		           	 // For Displaying time
#include <climits>
#include <string>
#include <set>

/*/-------------not cross-platform-----------------------------------------------------------------------------------------
#include <windows.h>
#include <conio.h>
*///-----------------------------------------------------------------------------------------------------------------------


#include "../helpers/helpers.h"

namespace view{
	class View{
	private:
		std::set<std::string> stopwordsSet;
	public:
		View();
		void searchView();
		void resultView(); //pass in object
		void gotoxy(int , int );
		void time();
		void typeInput(std::string& field, const int& fieldLim = INT_MAX);
	};

}
#endif


