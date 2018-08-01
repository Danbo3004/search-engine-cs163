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


	std::vector<std::string> stringToVector(std::string stripString){
		//to lowercase
		std::transform(stripString.begin(), stripString.end(), stripString.begin(), ::tolower);

		std::stringstream ss(stripString);
		std::istream_iterator<std::string> begin(ss);
		std::istream_iterator<std::string> end;
		std::vector<std::string> vstring(begin, end);

		return vstring;
	}


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

	void removeBracketsFromVector(std::vector<std::string>& stripVector){

	}

	std::vector<std::string> stripNakedKeepStopwords(std::string stripString){
		std::vector<std::string> vstring = stringToVector(stripString);
		removeDelimiterFromVector(vstring);
		removeBracketsFromVector(vstring);

		return vstring;
	}

}

string convertNumberToString(int number) 
{
	string res = "";
	while (number > 0) res += (number % 10 + '0'), number /= 10;
	while (res.length() < 2) res = "0" + res;
	return res;
}

DataFile readFile(int fileNumber) 
{
	int newsNumber = fileNumber % 100;
	int groupNumber = fileNumber / 100;
	string fileName = "Group" + convertNumberToString(groupNumber) + "News" + convertNumberToString(newsNumber);
	ifstream fin;
	fin.open(fileName);
	string title, content = "";
	getline(fin, title);
	while (!fin.eof()) 
	{
		string word;
		fin >> word;
		content += word + " ";
	}
	DataFile data;
	//data.title = helpers::stripStopwordstitle();
	//data.content = helpers::stripStopwords(content);
	return data;
}
