#include "helpers.h"

namespace helpers{
	std::vector<std::string> stripStopwords(std::string stripString, const std::set<std::string>& stopwords){
		std::vector<std::string> vstring = stringToVector(stripString);

		removeNonOperatorFromVector(vstring);

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

	std::vector<std::string> stringToRawVector(std::string stripString){
		std::stringstream ss(stripString);
		std::istream_iterator<std::string> begin(ss);
		std::istream_iterator<std::string> end;
		std::vector<std::string> vstring(begin, end);

		return vstring;
	}

	void removeNonOperatorFromVector(std::vector<std::string>& stripVector){
		//remove everything except operator
		std::vector<std::string>::iterator it = stripVector.begin();
		while (it != stripVector.end()){
			while (!(	it == stripVector.end()
						|| (*it).length() <= 0
						|| ('A'<= (*it).back() && (*it).back() <= 'Z')
						|| ('a'<= (*it).back() && (*it).back() <= 'z')
						|| ('0'<= (*it).back() && (*it).back() <= '9')
						|| ((*it).back() == 34 || (*it).back() == '*')
					)){
				(*it).pop_back();
			}

			while (!(	it == stripVector.end()
						|| (*it).length() <= 0
						|| ('A'<=(*it)[0] && (*it)[0] <= 'Z')
						|| ('a'<=(*it)[0] && (*it)[0] <= 'z')
						|| ('0'<=(*it)[0] && (*it)[0] <= '9')
						|| (*it)[0] == '$'
						|| (*it)[0] == 34
						|| (*it)[0] == '*'
						|| (*it)[0] == '+'
						|| (*it)[0] == '-'
						|| (*it)[0] == '~'
					)){
				(*it).erase(0,1);
			}

			if (it != stripVector.end()) it++;

		}
	}

	void removeOddCharFromVector(std::vector<std::string>& stripVector){
		//remove odd leading and trailing character
		std::vector<std::string>::iterator it = stripVector.begin();
		while (it != stripVector.end()){
			while (!(	it == stripVector.end()
						|| (*it).length() <= 0
						|| ('A'<= (*it).back() && (*it).back() <= 'Z')
						|| ('a'<=(*it).back() && (*it).back() <= 'z')
						|| ('0'<=(*it).back() && (*it).back() <= '9')
					)){
				(*it).pop_back();
			}

			while (!(	it == stripVector.end()
						|| (*it).length() <= 0
						|| ('A'<=(*it)[0] && (*it)[0] <= 'Z')
						|| ('a'<=(*it)[0] && (*it)[0] <= 'z')
						|| ('0'<=(*it)[0] && (*it)[0] <= '9')
						|| (*it)[0] == '$'
				)){
				(*it).erase(0,1);
			}

			if (it != stripVector.end()) it++;
		}

	}



	std::vector<std::string> stripNakedKeepStopwords(std::string stripString){
		//std::string newString = removeOddCharFromString(stripString);
		std::vector<std::string> vstring = stringToVector(stripString);
		removeOddCharFromVector(vstring);

		return vstring;
	}

}

string convertNumberToString(int number) 
{
	string res = std::to_string(number);
	if (res.size() < 2) res  = "0" + res;
	return res;
}

DataFile readFile(int fileNumber) 
{
	int newsNumber = fileNumber % 100;
	// int groupNumber = fileNumber / 100;
	int groupNumber = 9;
	string fileName = "Group" + convertNumberToString(groupNumber) + "News" + convertNumberToString(newsNumber);
	fileName = "../newsdata/" + fileName + ".txt";
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
	data.title = helpers::stripNakedKeepStopwords(title);
	data.content = helpers::stripNakedKeepStopwords(content);
	return data;
}
