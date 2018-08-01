#include "helpers.h"

namespace helpers{
	std::vector<std::string> stripStopwords(std::string stripString, const std::set<std::string>& stopwords){
		//to lowercase
		std::transform(stripString.begin(), stripString.end(), stripString.begin(), ::tolower);

		//to vector
		std::stringstream ss(stripString);
		std::istream_iterator<std::string> begin(ss);
		std::istream_iterator<std::string> end;
		std::vector<std::string> vstring(begin, end);

		std::vector<std::string>::iterator it = vstring.begin();
		while(it != vstring.end()){
			if (stopwords.find(*it) != stopwords.end()) vstring.erase(it);
			if (it != vstring.end()) it++;
		}

		return vstring;

	}

	/*
	std::vector<std::string> stringToVector(std::string stripString){
		std::stringstream ss(stripString);
		std::istream_iterator<std::string> begin(ss);
		std::istream_iterator<std::string> end;
		std::vector<std::string> vstring(begin, end);

		return vstring;
	}
	*/

	void removeDelimiterFromVector(std::vector<std::string>& stripVector){
		//remove grammar delimiters
		for (std::vector<std::string>::iterator it = stripVector.begin(); it != stripVector.end(); it++){
			if ((*it)[(*it).length()-1] == ',' || (*it)[(*it).length()-1] == ';'
					|| (*it)[(*it).length()-1] == '?' || (*it)[(*it).length()-1] == '!'
					|| (*it)[(*it).length()-1] == '.'){
				(*it).pop_back();
			}

		}
	}
}
