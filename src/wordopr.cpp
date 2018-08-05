#include "./wordopr.h"
vector<FileResult> operatorWord(WordsInFiles &words, string a, string b, int operation)
{
    vector<FileResult> wordA = words.searchWord(a);
    vector<FileResult> wordB = words.searchWord(b);
    return operatorWord(words, wordA, wordB, operation);
}

vector<FileResult> operatorWord(WordsInFiles &words, vector<FileResult> a, vector<FileResult> b, int operation)
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
                FileResult newFile;
                newFile.indexFile = index;
                for (auto &w : a[indexA].listWord)
                {
                    for (auto &nw : b[indexB].listWord)
                    {
                        cout << w.position << " " << nw.position << endl;
                        if (nw.position <= w.position + WILDCARD_DIS)
                        {
                            newFile.listWord.push_back(w);
                        }
                    }
                }
                if (newFile.listWord.size() != 0)
                    res.push_back(newFile);
            }
        }
    }
    return res;
}

vector<FileResult> findExact(WordsInFiles &wordsInFile, vector<string> words)
{
    vector<FileResult> res;
    // if the string search is empty, then return empty result
    if (words.size() == 0)
        return res;

    //search the occurrences if files of the first word
    vector<FileResult> firstWordFile = wordsInFile.searchWord(words[0]);
    if (words.size() == 1)
        return firstWordFile;

    CurrentFile currentFile;
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

        // cout << "File Index: " << fileIndex << endl;
        for (auto &word : file.listWord)
        {

            bool found = true;
            int wordIndex = word.position;
            // cout << "Word Index: " << wordIndex << endl;

            // checking for matching exactly
            for (int i = 1; i < words.size(); i++)
            {
                string temp = currentFile.getWordByIndex(fileIndex, wordIndex + i, false);
                // cout << temp << " ";
                if (words[i] != temp)
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

vector<FileResult> findWildcard(WordsInFiles &words, vector<string> pre, vector<string> after)
{
    if (pre.size() == 0)
        return findExact(words, after);
    else if (after.size() == 0)
        return findExact(words, pre);
    else
    {
        vector<FileResult> preWC = findExact(words, pre);
        cout << preWC.size() << endl;
        vector<FileResult> afterWC = findExact(words, after);
        cout << afterWC.size() << endl;
        return operatorWord(words, preWC, afterWC, ORDER_AND);
    }
}
