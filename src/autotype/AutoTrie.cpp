#include "AutoTrie.h";

void AutoTrie::add(char c){
	if (word == ""){
		next[c] = AutoTrie(std::string(1,c));
	}
	else{
		next[c] = AutoTrie(word+c);
	}
}

std::string AutoTrie::find(const string &query){
	AutoTrie* node = this;
	for (int i =0; i< query.length(); i++){
		if (node -> next.find(query[i]) == node -> next.end()) return "";
		else node = &node -> next[query[i]];
	}
	return node->word;
}

void AutoTrie::insert(const string &query){
	AutoTrie* node = this;
	for (int i =0 ; i<query.length(); i++){
		if (node -> next.find(query[i]) == node -> next.end()){
			node -> add(query[i]);
		}
		node = &node->next[query[i]];
	}
	node->isEndOfWord = true;
}

std::vector<std::string> AutoTrie::allPrefixes(){
	std::vector<std::string> results;
	if (isEndOfWord) results.push_back(word);
	if (next.size()){
		map<char, AutoTrie>::iterator it;
		std::vector<std::string> pre;
		for (it = next.begin(); it!=next.end(); it++){
			pre = it->second.allPrefixes();
			results.insert(results.end(), pre.begin(), pre.end());
		}
	}
	return results;
}

std::vector<std::string> AutoTrie::autotype(const string &prefix){
	AutoTrie* node = this;
	std::vector<std::string> results;
	for (int i = 0; i< prefix.length(); i++){
		if (node->next.find(prefix[i]) == node->next.end()) return results;
		else node = &node->next[prefix[i]];

	}
	return node->allPrefixes();
}
