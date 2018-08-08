#include "synonym.h"

// get all synonyms of the word
vector <string> getSynonyms(string word) {
   ifstream file;
   file.open(constants::synonymPath);
   if (!file.is_open()){
       cout << "File error\n";
   }
   vector <string> synonyms;
   string line;
   while (file >> line){
       if (line.find(word) != string::npos){ // find matching word
            string str = "";
            for (int i = 0; i < line.length(); ++i){ // break words
                if (line[i] == ',') {
                   if (str != word) synonyms.push_back(str);
                   str = "";
                   continue;
                }
                str += line[i];
            }
           if (str != "") synonyms.push_back(str);
           break;
       }
   }
   file.close();
   return synonyms;
}

// sort by number of presences of word
bool cmpSynonymByNumber(FileResult a, FileResult b){
   return a.listWord.size() > b.listWord.size();
}

vector <FileResult> searchSynonym(WordsInFiles &wordsInFiles, string word){
   vector <string> synonyms = getSynonyms(word); // list of synonyms

   // search for each word
   vector <FileResult> responses;
   for (int i = 0; i < (int) synonyms.size(); ++i){
       string w = synonyms[i];
       vector <FileResult> found = wordsInFiles.searchWord(w);
       responses.insert(responses.end(), found.begin(), found.end());
   }
   
   sort(responses.begin(), responses.end(), cmpSynonymByNumber);
   
   vector <FileResult> res;
   // get 5 best FileResult
   for (int i = 0; i < min(5, (int)responses.size()); ++i){
       FileResult response = responses[i];
       res.push_back(response);
   }
   return res;
}


