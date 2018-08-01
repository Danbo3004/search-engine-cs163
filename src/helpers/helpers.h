//ID: 1751001
//Name: Nguyen Hien Tuan Duy
//Exercise

#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
#include <locale>

namespace helpers{
	//std::vector<std::string> stringToVector(std::string);
	std::vector<std::string> stripStopwords(const std::string, const std::set<std::string>&);
	void removeDelimiterFromVector(std::vector<std::string>&);
}

namespace constants{
	const std::string stopwordsPath = "./data/stopwords.txt";
}


#endif


