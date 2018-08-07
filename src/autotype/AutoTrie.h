#ifndef AUTOTRIE_H
#define AUTOTRIE_H

#include <map>
#include <string>
#include "../helpers/helpers.h"

struct AutoTrie{
	std::map<char, AutoTrie> next;
	std::string word;
	bool isEndOfWord;

	AutoTrie(const string& character = ""){
		word = character;
		isEndOfWord = false;
	}

	void add(char);
	string find(const string&);
	void insert(const string&);
	std::vector<std::string> allPrefixes();
	std::vector<std::string> autotype(const string&);

};

#endif
