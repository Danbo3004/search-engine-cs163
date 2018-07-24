//ID: 1751001
//Name: Nguyen Hien Tuan Duy
//Exercise

#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <windows.h>
#include <math.h>
#include <windows.h>                  // For gotoxy() and Sleep function
#include <ctime>		           	 // For Displaying time
#include <iomanip>
#include <limits>
#include <climits>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <cstddef>
#include <stdio.h>
#include <set>

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


