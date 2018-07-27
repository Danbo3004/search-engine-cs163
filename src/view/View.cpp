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
		ch = getch();
		while(ch != '\n'){                  // gets input until 'Enter' key is pressed
			if(ch == '\b'){
				if(field.size() > 0 ){
					field.erase(field.begin() + field.size() -1);
					std::cout << "\b \b";
					i--;
				}
				ch = getch();
			}
			else{
				if(i<fieldLim){
					field.push_back(ch);
					std::cout<<ch;
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
		std::string query = "" ;
		/*/-------------not cross-platform-----------------------------------------------------------------------------------------
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

		time();
		gotoxy(20,20);
		*///-----------------------------------------------------------------------------------------------------------------------
		std::cout << "Search:  ";
		typeInput(query);

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
	*///-----------------------------------------------------------------------------------------------------------------------

}

