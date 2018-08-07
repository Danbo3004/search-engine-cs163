#include "View.h"

namespace view{
	View::View(){
		std::ifstream in(constants::stopwordsPath.c_str());
		std::string word;
		while (std::getline(in,word)){
			stopwordsSet.insert(word);
		}
		in.close();
	}

	void View::typeInput(std::string& field, const int& fieldLim/* = INT_MAX*/){
		/*/-------------not cross-platform-----------------------------------------------------------------------------------------
		char ch;
		int i = 0;
		std::vector<std::string> historyList;

		ch = getch();
		while(ch != 13){                  // gets input until 'Enter' key is pressed
			if(ch == '\b'){
				if(field.size() > 0 ){
					field.erase(field.begin() + field.size() -1);
					std::cout << "\b \b";
					history(field,historyList);
					i--;
				}
				ch = getch();
			}
			else{
				if(i<fieldLim){
					field.push_back(ch);
					std::cout<<ch;
					history(field,historyList);
					ch = getch();
					i++;
				}
				else{
					ch = getch();
				}
			}
		}
		*///-----------------------------------------------------------------------------------------------------------------------
		getline(std::cin,field);
	}

	void View::searchView(){
		while(true){
			std::string query = "" ;
			/*/-------------not cross-platform-----------------------------------------------------------------------------------------
			title();

			time();
			gotoxy(20,20);
			*///-----------------------------------------------------------------------------------------------------------------------
			std::cout << "Search:  ";
			typeInput(query);
			trie.insert(query);
			//find and remove query cues first
			//find AND -> in string
			//find OR  -> in string
			//find ""  -> in string
			//find intitle: (intitle:hammer nails  <=> exist "hammer" in the title) -> in vector
			//find filetype: [nope]
			//find + -> in the vector (stripStopwords won't strip)
			//find - -> same
			//find .. -> hmmmmmm brute? single query is find though
			//find ~ -> itself

		}
	}

	/*/-------------not cross-platform-----------------------------------------------------------------------------------------
	void View::gotoxy(int x, int y){         //For Setting the position of Cursor
		COORD coord = {0,0};
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition( GetStdHandle (STD_OUTPUT_HANDLE), coord );
	}

	void View::time(){
		//  FOR current time and date
		gotoxy(20,28);

		time_t now = std::time(0);
		struct tm currentTime = *localtime(&now);
		std::cout << "\n\n\t\t Current Date & Time is: "<<std::asctime(&currentTime);        // For Displaying Date and Time
		// Creating Object of Time
	}

	COORD View::GetConsoleCursorPosition(HANDLE hConsoleOutput) 	//For Getting the current position
	{
	    CONSOLE_SCREEN_BUFFER_INFO cbsi;
	    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	    {
	        return cbsi.dwCursorPosition;
	    }
	    else
	    {
	        // The function failed. Call GetLastError() for details.
	        COORD invalid = { 0, 0 };
	        return invalid;
	    }
	}

	void View::title(){
		system("cls");
		std::cout <<"\n\n";
		std::cout <<"\t\t\t";
		std::cout <<" .----------------.  .----------------.  .----------------.  .----------------. \n";
		std::cout <<"\t\t\t";
		std::cout <<"| .--------------. || .--------------. || .--------------. || .--------------. |\n";
		std::cout <<"\t\t\t";
		std::cout <<"| |      __      | || |   ______     | || |     ______   | || |    _______   | |\n";
		std::cout <<"\t\t\t";
		std::cout <<"| |     /  \\     | || |  |_   __ \\   | || |   .' ___  |  | || |   /  ___  |  | |\n";
		std::cout <<"\t\t\t";
		std::cout <<"| |    / /\\ \\    | || |    | |__) |  | || |  / .'   \\_|  | || |  |  (__ \\_|  | |\n";
		std::cout <<"\t\t\t";
		std::cout <<"| |   / ____ \\   | || |    |  ___/   | || |  | |         | || |   '.___`-.   | |\n";
		std::cout <<"\t\t\t";
		std::cout <<"| | _/ /    \\ \\_ | || |   _| |_      | || |  \\ `.___.'\\  | || |  |`\\____) |  | |\n";
		std::cout <<"\t\t\t";
		std::cout <<"| ||____|  |____|| || |  |_____|     | || |   `._____.'  | || |  |_______.'  | |\n";
		std::cout <<"\t\t\t";
		std::cout <<"| |              | || |              | || |              | || |              | |\n";
		std::cout <<"\t\t\t";
		std::cout <<"| '--------------' || '--------------' || '--------------' || '--------------' |\n";
		std::cout <<"\t\t\t";
		std::cout <<"'----------------'  '----------------'  '----------------'  '----------------' \n\n\n";

		gotoxy(46,14);
		std::cout <<"(Simple Search Engine)";
	}

	void View::history(const string& field, std::vector<std::string>& history ){

		COORD coord = GetConsoleCursorPosition(GetStdHandle (STD_OUTPUT_HANDLE));
		for (int i = 0; i<history.size(); i++){
			gotoxy(0,coord.Y+i+1);
			printf("\33[2K\r");
		}
		if (!field.length()){
			gotoxy(coord.X, coord.Y);
			return;
		}
		history =  trie.autotype(field);

		for (int i =0 ; i<history.size(); i++){
			gotoxy(29,coord.Y+i+1);
			std::cout<<history[i];
		}
		gotoxy(coord.X, coord.Y);
	}

	*///-----------------------------------------------------------------------------------------------------------------------


}


