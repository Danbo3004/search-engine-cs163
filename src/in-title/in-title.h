#ifndef in_title_h
#define in_title_h

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include "../helpers/helpers.h"
#include "../searchFile/searchFile.h"

using namespace std;

vector <FileResult> searchInTitle(WordsInFiles &wordsInFiles, vector <string> words);

bool cmpByNumber(FileResult a, FileResult b);

#endif
