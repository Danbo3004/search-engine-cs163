//ID: 1751001
//Name: Nguyen Hien Tuan Duy
//Exercise

#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
#include <locale>
#include <cstring>

using namespace std;

namespace helpers{
	std::vector<std::string> stringToVector(std::string);
	std::vector<std::string> stringToRawVector(std::string stripString);
	std::vector<std::string> stripStopwords(const std::string, const std::set<std::string>&);
	void removeNonOperatorFromVector(std::vector<std::string>&);
	void removeOddCharFromVector(std::vector<std::string> &);
	std::vector<std::string> stripNakedKeepStopwords(std::string);
	//std::string removeOddCharFromString(const std::string&);

}

namespace constants{
	const std::string LOG_FILE_PATH = "./log.txt";
	const std::string stopwordsPath = "../data/stopwords.txt";
	const std::string synonymPath = "../data/synonyms.txt";
}

struct DataFile {
	vector <string> title, content;
};

DataFile readFile(int fileNumber);
void log(std::string s);

string convertNumberToString(int number);

#endif
