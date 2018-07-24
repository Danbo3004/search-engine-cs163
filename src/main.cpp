#include "helpers/helpers.h"
#include "view/View.h"
#include <stdio.h>

int main(){
	//test bed

	/*//-------------------------------stripStopwords test-----------------------------
	std::string s = "           a friendly,  Hello World Fuck. You                  ";
	std::set<std::string> stopwordsSet;
	freopen(constants::stopwordsPath.c_str(), "r", stdin);
	std::string word;
	while (std::getline(std::cin,word)){
		stopwordsSet.insert(word);
	}
	fclose(stdin);
	std::vector<std::string> vstrings = helpers::stripStopwords(s, stopwordsSet);
	std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	*///--------------------------------------------------------------------------------

	view::View facade;
	facade.searchView();


	return 0;
}
