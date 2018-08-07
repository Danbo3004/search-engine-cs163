#ifndef synonym_h
#define synonym_h

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "../helpers/helpers.h"
#include "../searchFile/searchFile.h"

using namespace std;

vector <string> getSynonyms(string word);

vector <FileResult> searchSynonym(string word);

bool cmpByNumber(FileResult a, FileResult b);

#endif /* synonym_h */
