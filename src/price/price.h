#ifndef _PRICE_
#define _PRICE_

#include <vector>
#include <map>
#include <algorithm>
#include "../helpers/helpers.h"
#include "../searchFile/searchFile.h"

vector <FileResult> searchPrice(WordsInFiles &wordsInFiles, string object, string price);

vector<FileResult> searchInRange(WordsInFiles &wordsInFiles, string object, string minPrice, string maxPrice);

int convertStringToNumber(string str);

#endif