#include <bits/stdc++.h>
#include "./src/helpers/helpers.h"
#include "./src/searchFile/searchFile.h"
#include <chrono>
#include <iomanip>
#include "./src/wordopr.h"

using namespace std;

int main(int argc, char const *argv[])
{
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
    vector<FileResult> test;
    vector<string> query{"chief", "executive"};
    vector<string> pre{
        "client",
        "who"};
    vector<string> after{"same", "number"};
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    WordsInFiles words;
    words.Init();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    double initTime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1e6;

    begin = std::chrono::steady_clock::now();
    test = operatorWord(words, "chief", "executive", MINUS);
    test = operatorWord(words, "chief", "executive", AND);
    test = operatorWord(words, "chief", "executive", OR);
    test = findWildcard(words, pre, after);
    test = findExact(words, query);
    end = std::chrono::steady_clock::now();
    double searchTime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1e6;
    // for (int i = 0; i < test.size(); ++i)
    // {
    //     cout << test[i].indexFile << endl;
    //     for (int j = 0; j < test[i].listWord.size(); ++j)
    //     {
    //         cout << test[i].listWord[j].position << " ";
    //         cout << ((test[i].listWord[j].isTitle) ? "Title" : "Content") << endl;
    //         cout << endl;
    //     }
    //     cout << endl;
    // }
    // cout << test.size() << endl;
    cout << "Build trie: " << fixed << setprecision(2) << initTime << " seconds" << endl;
    cout << "5 operators: " << searchTime << fixed << setprecision(2) << "seconds" << endl;
    return 0;
}
