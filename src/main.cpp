#include "helpers/helpers.h"
#include "autotype/AutoTrie.h"
// #include "view/View.h"
#include "inTitle/inTitle.h"
#include <stdio.h>
#include <bits/stdc++.h>
#include "operators/wordopr.h"
#include "searchFile/searchFile.h"
#include "synonym/synonym.h"
#include <chrono>
#include <iomanip>

int main()
{
	//test bed

	/*//-------------------------------stripStopwords test-----------------------------
	std::string s = "           a friendly,  Hello World Fuck. You                  ";
	std::set<std::string> stopwordsSet;
	freopen(constants::stopwordsPath.c_str(), "r", stdin);
	std::string word;
	while (std::getline(std::cin,word)){
		stopwordsSet.insert(word);
	}
	fclose(stdin);
	std::vector<std::string> vstrings = helpers::stripStopwords(s, stopwordsSet);
	std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	*/
	//--------------------------------------------------------------------------------

	/*//-------------------------------Autotype test-----------------------------
	AutoTrie trie;
	trie.insert("he");
	trie.insert("hello world");
	std::vector<std::string> vstrings = trie.autotype("h");
	std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	*/
	//--------------------------------------------------------------------------------

	// int index = 1000;
	// CurrentFile cf;
	// for (int  i = 1; i < 10; i++) {
	//     cout << cf.getWordByIndex(index, 170 + i, false) << " ";
	// }
	// DataFile data = readFile(index);
	// cout << "Title: " << endl;
	// for (auto s : data.title) {
	//     cout << s << " ";
	// }
	// cout << endl;
	// cout << "Content: " << endl;
	// for (auto s : data.content) {
	//     cout << s << " ";
	// }
	// cout << "--------------------------------------------------" << endl;
	//--------------------------------------------------------------------------------

	// view::View facade;
	// facade.searchView();
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	WordsInFiles words;
	words.Init();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	double initTime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1e6;
	vector<FileResult> test;
	vector<string> query{"uber"};
	vector<string> pre{
		"client",
		"who"};
	vector<string> after{"same", "number"};
	begin = std::chrono::steady_clock::now();
	// for (int i = 0; i < 20; i++) {
		// test = operatorWord(words, "chief", "executive", MINUS);
		test = operatorWord(words, "chief", "asdsadasdasd", AND);
		// test = operatorWord(words, "chief", "executive", OR);
		// test = findWildcard(words, pre, after);
		// test = findExact(words, query);
	// }
	end = std::chrono::steady_clock::now();
	double searchTime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1e6;
	CurrentFile currentFile;
	for (int i = 0; i < test.size(); ++i)
	{
		cout << test[i].indexFile << endl;
		CurrentFile currentFile;
		int k = 0;
		string s = currentFile.getWordByIndex(test[i].indexFile, 0, true);
		cout << "Title: ";
		while (s != "")
		{
			cout << s << " ";
			k++;
			s = currentFile.getWordByIndex(test[i].indexFile, k, true);
		}
		cout << endl;
		cout << "Content: " << endl;
		for (int j = 0; j < test[i].listWord.size(); ++j)
		{
			cout << "...";
			for (int jj = test[i].listWord[j].position - 6; jj < test[i].listWord[j].position + 6; jj++)
			{
				string tmp = currentFile.getWordByIndex(test[i].indexFile, jj, false);
				if (tmp != "")
					cout << tmp << " ";
			}
			// cout << test[i].listWord[j].position << " ";
			// cout << ((test[i].listWord[j].isTitle) ? "Title" : "Content") << endl;
			// cout << endl;
			cout << "...";
			cout << endl;
			cout << endl;
		}
		cout << endl;
	}
	cout << test.size() << endl;
	cout << "5 operators: " << searchTime << fixed << setprecision(2) << "seconds" << endl;
	cout << "Build trie: " << fixed << setprecision(2) << initTime << " seconds" << endl;

	// view::View facade;
	// facade.searchView();

	// WordsInFiles words;
	// words.Init();
	return 0;
}
