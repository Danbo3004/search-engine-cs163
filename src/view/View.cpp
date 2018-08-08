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
		//-------------not cross-platform-----------------------------------------------------------------------------------------
		char ch;
		int i = 0;
		std::vector<std::string> historyList;

		ch = getch();
		while(ch != 13){                  // get input until 'Enter' key is pressed
			if(ch == '\b'){
				if(field.size() > 0 ){
					field.erase(field.begin() + field.size() -1);
					std::cout << "\b \b";
					i--;
				}
				history(field,historyList);
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
		///-----------------------------------------------------------------------------------------------------------------------
		//getline(std::cin,field);
	}

	void View::searchView(){
		while(true){
			std::string query = "" ;
			//-------------not cross-platform-----------------------------------------------------------------------------------------
			title();
			time();
			gotoxy(20,20);
			///-----------------------------------------------------------------------------------------------------------------------
			std::cout << "Search:  ";
			typeInput(query);
			//query = "hello AND world";
			trie.insert(query);


			std::vector<FileResult> results = searchFor(query);
			std::cout<<results.size();
			system("pause");
			display(results,query);


		}
	}

	void View::display(std::vector<FileResult> results, std::string query){
		system("cls");

		std::vector<std::string> cleanString = helpers::stripNakedKeepStopwords(query);
		std::set<std::string> searchQuery;
		std::copy( cleanString.begin(), cleanString.end(), std::inserter( searchQuery, searchQuery.end() ) );

		for (int i = 0; i < std::min((int)results.size(),5); ++i)
		{
			DataFile resFile = readFile(results[i].indexFile);
			cout<<results[i].listWord.size()<<endl;

			cout<<"Title: ";
			SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 6);
			for (int j = 0; j<std::min(20,(int)resFile.title.size()); j++){
				if (std::find(searchQuery.begin(), searchQuery.end(), resFile.title[j]) != searchQuery.end()){
					SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 2);
					cout << resFile.title[j]<<" ";
					SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 15);
				}
				else{
					cout << resFile.title[j]<<" ";
				}
			}
			SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 15);

			cout << endl;

			cout << "Content: ";
			for (int j = 0; j<(int)resFile.content.size(); j++){
				int tmp = j;//+resFile.title.size();
				if (std::find(searchQuery.begin(), searchQuery.end(), resFile.content[j]) != searchQuery.end()){
				//if (std::find_if(results[i].listWord.begin(), results[i].listWord.end(),[&tmp](const Word& w){
				//																			 return w.position == tmp;
				//																			 }) != results[i].listWord.end()){
					SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 2);
					cout << resFile.content[j]<<" ";
					SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 15);
				}
				else{
					cout << resFile.content[j]<<" ";
				}
			}

			cout<<endl<<endl;
		}
		system("pause");
	}

	std::vector<FileResult> View::searchFor(std::string& query){
		std::vector<std::string> vstring = helpers::stringToRawVector(query);
		std::vector<std::string> cleanString;

		std::vector<std::string>::iterator it;
		std::string s;
		std::string::iterator sIter;

		std::vector<FileResult> results;
		std::vector<FileResult> tmp;
		std::vector<FileResult>::iterator vFileResultIter;
		std::string phraseA = "", phraseB = "";

		int count = 0;

		bool called = false;

		//find and remove query cues first
		//find AND -> in string /
		//find OR  -> in string /
		//find ""  -> in string /
		//find intitle: (intitle:hammer nails  <=> exist "hammer" in the title) -> in vector
		//find filetype: [nope]
		//find + -> in the vector (stripStopwords won't strip) /
		//find - -> same /
		//find .. -> hmmmmmm brute? single query is find though
		//find ~ -> itself /


		//-------------MINUS-----------------------------------------------------------------------------------------
		it = std::find_if(vstring.begin(), vstring.end(), [](const string& s){
															 return s.front() == '-';
															 });
		if (it != vstring.end()){
			vstring.erase(it);
			called = true;
		}

		//------------------------------------------------------------------------------------------------------

		//-------------AND-----------------------------------------------------------------------------------------
		//how about multiple ANDs?
		//find -> intersect
		for(it = std::find(vstring.begin(), vstring.end(), "AND"); it != vstring.end(); vstring.erase(vstring.begin(),it+1)){
			 called = true;
			 if (it == vstring.end()) break;
			 s = *(it-1)+" "+*(it+1);

			 cleanString = helpers::stripStopwords(s, stopwordsSet);
			 phraseA = cleanString.front();
			 phraseB = cleanString.back();
			 tmp = andOperator(wordsInFiles,phraseA,phraseB);
			 if (results.size()){

				 for (std::vector<FileResult>::iterator resIt = results.begin(); resIt != results.end(); resIt++ ){

					 FileResult resi = *resIt;
					 vFileResultIter = std::find_if(tmp.begin(), tmp.end(), [&resi](const FileResult& file){
																			 return file.indexFile == resi.indexFile;
																			 });
					 cout << s << endl;
					 if(vFileResultIter == tmp.end()){
						 results.erase(resIt);
					 }
					 else{
						 //merging
						 std::set_intersection(resIt->listWord.begin(), resIt->listWord.end(),
												 vFileResultIter->listWord.begin(), vFileResultIter->listWord.end(),resIt->listWord.begin(),
												 [](const Word &a, const Word &b) {
													return a.position < b.position;
												});
					 }
					 if (resIt == results.end()) break;
				 }

			 }
			 else{
				 results = tmp;
			 }
		}
		///-----------------------------------------------------------------------------------------------------------------------


		//-------------OR-----------------------------------------------------------------------------------------
		//and multiple ORs
		for(it = std::find(vstring.begin(), vstring.end(), "OR"); it != vstring.end(); vstring.erase(vstring.begin(),it+1)){
			 called = true;
			 if (it == vstring.end()) break;
			 s = *(it-1)+" "+*(it+1);

			 cleanString = helpers::stripStopwords(s, stopwordsSet);
			 phraseA = cleanString.front();
			 phraseB = cleanString.back();
			 tmp = orOperator(wordsInFiles,phraseA,phraseB);
			 if (results.size()){

				 for (std::vector<FileResult>::iterator resIt = results.begin(); resIt != results.end(); resIt++ ){
					 //merging
					 std::set_union(resIt->listWord.begin(), resIt->listWord.end(),
											 vFileResultIter->listWord.begin(), vFileResultIter->listWord.end(),resIt->listWord.begin(),
											 [](const Word &a, const Word &b) {
												return a.position < b.position;
											});
					 if (resIt == results.end()) break;
				 }

			 }
			 else{
				 results = tmp;
			 }
		}
		//------------------------------------------------------------------------------------------------------

		//-------------WILDCARD-----------------------------------------------------------------------------------------
		//find -> union
		sIter = find(query.begin(), query.end(), '*');
		if(sIter != query.end()){
			 called = true;
			 phraseA = std::string(query.begin(), sIter-1);
			 phraseB = std::string(sIter+1,query.end());

			 cout<<phraseA<<phraseB<<endl;

			 std::vector<std::string> vectorA = helpers::stripStopwords(phraseA, stopwordsSet);
			 std::vector<std::string> vectorB = helpers::stripStopwords(phraseB, stopwordsSet);

			 tmp = findWildcard(wordsInFiles,vectorA,vectorB);
			 if (results.size()){

				 for (std::vector<FileResult>::iterator resIt = results.begin(); resIt != results.end(); resIt++ ){
					 //merging
					 std::set_union(resIt->listWord.begin(), resIt->listWord.end(),
											 vFileResultIter->listWord.begin(), vFileResultIter->listWord.end(),resIt->listWord.begin(),
											 [](const Word &a, const Word &b) {
												return a.position < b.position;
											});
					 if (resIt == results.end()) break;
				 }

			 }
			 else{
				 results = tmp;
			 }
		}
		///-----------------------------------------------------------------------------------------------------------------------

		//-------------EXACT-----------------------------------------------------------------------------------------
		if(vstring.size() == 1 || (vstring.front().front() == 34 && vstring.back().back() == 34)){
			called = true;
			cleanString = helpers::stripNakedKeepStopwords(query);
			results = findExact(wordsInFiles, cleanString);
		}
		///-----------------------------------------------------------------------------------------------------------------------


		//-------------DEFAULT AND PLUS-----------------------------------------------------------------------------------------
		for(it = vstring.begin(); it != vstring.end() - 1; it++){
			 if (called) break;

			 s = *(it)+" "+*(it+1);

			 cleanString = helpers::stripStopwords(s, stopwordsSet);
			 phraseA = cleanString.front();
			 phraseB = cleanString.back();

			 if (phraseA.front() == '+') phraseA.erase(0,1);
			 if (phraseB.front() == '+') phraseB.erase(0,1);
			 tmp = andOperator(wordsInFiles,phraseA,phraseB);
			 if (results.size()){
				 for (std::vector<FileResult>::iterator resIt = results.begin(); resIt != results.end(); resIt++ ){
					 //merging
					 std::set_union(resIt->listWord.begin(), resIt->listWord.end(),
											 vFileResultIter->listWord.begin(), vFileResultIter->listWord.end(),resIt->listWord.begin(),
											 [](const Word &a, const Word &b) {
												return a.position < b.position;
											});
					 if (resIt == results.end()) break;
				 }

			 }
			 else{
				 results = tmp;
			 }
			 cout<<phraseA<<endl<<phraseB<<endl;
		}
		///-----------------------------------------------------------------------------------------------------------------------

		//descending sort
		 std::sort(results.begin(), results.end(), [](const FileResult& fileA, const FileResult& fileB) -> bool{
			 return fileA.listWord.size() > fileB.listWord.size();
		 });

		 return results;
	}

	//-------------not cross-platform-----------------------------------------------------------------------------------------
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
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 15);
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

	///-----------------------------------------------------------------------------------------------------------------------


}


