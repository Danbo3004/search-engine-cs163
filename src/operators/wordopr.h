#if !defined(WORDOPR_H)
#define WORDOPR_H
#include <bits/stdc++.h>
#include "../helpers/helpers.h"
#include "../searchFile/searchFile.h"

using std::string;
using std::vector;
const int AND = 1;
const int OR = 2;
const int MINUS = 3;
const int WILDCARD_DIS = 6;

vector<FileResult> andOperator(WordsInFiles &words, string a, string b);
vector<FileResult> orOperator(WordsInFiles &words, string a, string b);
vector<FileResult> minusOperator(WordsInFiles &words, string a, string b);
vector<FileResult> operatorWord(WordsInFiles &words, vector<FileResult> a, vector<FileResult> b, int operation);
vector<FileResult> operatorWord(WordsInFiles &words, string a, string b, int operation);
vector<FileResult> findExact(WordsInFiles &wordsInFile, vector<string> words);
vector<FileResult> findWildcard(WordsInFiles &words, vector<string> pre, vector<string> after);
#endif // WORDOPR_H
