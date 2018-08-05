#include <bits/stdc++.h>
#include "./src/searchFile/searchFile.h"

using namespace std;

const int AND = 1;
const int OR = 2;
const int MINUS = 3;
const int ORDER_AND = 4;

vector<FileResult> operatorWord(string a, string b, int operation)
{
    WordsInFiles words;
    vector<FileResult> wordA = words.searchWord(a);
    vector<FileResult> wordB = words.searchWord(b);
    return operatorWord(wordA, wordB, operation);
}

vector<FileResult> operatorWord(vector<FileResult> a, vector<FileResult> b, int operation)
{
    vector<FileResult> res;
    map<int, int> fileCount;
    for (auto &file : a)
        fileCount[file.indexFile]++;
    for (auto &file : b)
        fileCount[file.indexFile] += 2;
    for (auto &file : fileCount)
    {
        int wordCounts = file.second;
        int index = file.first;
        int indexA, indexB;
        for (int i = 0; i < a.size(); i++)
        {
            if (a[i].indexFile == index)
            {
                indexA = i;
                break;
            }
        }
        for (int i = 0; i < b.size(); i++)
        {
            if (b[i].indexFile == index)
            {
                indexB = i;
                break;
            }
        }
        if (operation == AND)
        {
            if (wordCounts == 3)
            {
                FileResult newFile;
                newFile.indexFile = index;
                newFile.listWord = a[indexA].listWord;
                newFile.listWord.insert(newFile.listWord.end(),
                                        b[indexB].listWord.begin(), b[indexB].listWord.end());
                res.push_back(newFile);
            }
        }
        else if (operation == OR)
        {
            FileResult newFile;
            newFile.indexFile = index;
            newFile.listWord = a[indexA].listWord;
            newFile.listWord.insert(newFile.listWord.end(),
                                    b[indexB].listWord.begin(), b[indexB].listWord.end());
            res.push_back(newFile);
        }
        else if (operation == MINUS)
        {
            if (wordCounts == 1)
            {
                FileResult newFile;
                newFile.indexFile = index;
                newFile.listWord = a[indexA].listWord;
                res.push_back(newFile);
            }
        }
        else
        {
            if (wordCounts == 3)
            {
                int sizeA = a[indexA].listWord.size();
                if (a[indexA].listWord[sizeA - 1].position > b[indexB].listWord[0].position)
                {
                    FileResult newFile;
                    newFile.indexFile = index;
                    newFile.listWord = a[indexA].listWord;
                    newFile.listWord.insert(newFile.listWord.end(),
                                            b[indexB].listWord.begin(), b[indexB].listWord.end());
                    res.push_back(newFile);
                }
            }
        }
    }
    return res;
}

vector<FileResult> findExact(vector<string> words)
{
    vector<FileResult> res;
    // if the string search is empty, then return empty result
    if (words.size() == 0)
        return res;

    //search the occurrences if files of the first word
    WordsInFiles wordsInFile;
    vector<FileResult> firstWordFile = wordsInFile.searchWord(words[0]);

    for (auto &file : firstWordFile)
    {
        // for every file having the first word
        // go to every position of first word
        // check the next word is the same as the query string
        // if we get match, then add the position of the first word to the result file result

        // initialize the new file result
        FileResult result;
        result.indexFile = file.indexFile;

        int fileIndex = file.indexFile;

        // currentFile is used for getting the word in the current checking file
        CurrentFile currentFile;
        bool found = true;

        for (auto &word : file.listWord)
        {
            int wordIndex = word.position;

            // checking for matching exactly
            for (int i = 1; i < words[i].size(); i++)
            {
                if (words[i] != currentFile.getWordByIndex(fileIndex, wordIndex + i, false))
                {
                    found = false;
                    break;
                }
            }

            // if match, add the current word to the result of current file
            if (found)
            {
                result.listWord.push_back(word);
            }
        }

        // only add file having matching to the result
        if (result.listWord.size() != 0)
            res.push_back(result);
    }

    return res;
}

vector<FileResult> findWildcard(vector<string> pre, vector<string> after)
{
    if (pre.size() == 0)
        return findExact(after);
    else if (after.size() == 0)
        return findExact(pre);
    else
    {
        vector<FileResult> preWC = findExact(pre);
        vector<FileResult> afterWC = findExact(after);
        return operatorWord(preWC, afterWC, ORDER_AND);
    }
}

int main(int argc, char const *argv[])
{
    vector<FileResult> a;
    vector<FileResult> b;
    cout << "AND" << endl;
    vector<FileResult> res = operatorWord(a, b, AND);
    for (auto &file : res)
    {
        cout << file.indexFile << endl;
        for (auto &word : file.listWord)
            cout << word.position << " ";
        cout << endl;
    }

    cout << "OR" << endl;
    res = operatorWord(a, b, OR);
    for (auto &file : res)
    {
        cout << file.indexFile << endl;
        for (auto &word : file.listWord)
            cout << word.position << " ";
        cout << endl;
    }
    cout << "MINUS" << endl;
    res = operatorWord(a, b, MINUS);
    for (auto &file : res)
    {
        cout << file.indexFile << endl;
        for (auto &word : file.listWord)
            cout << word.position << " ";
        cout << endl;
    }

    return 0;
}
