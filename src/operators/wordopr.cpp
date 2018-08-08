#include "./wordopr.h"
#include <chrono>

vector<FileResult> andOperator(WordsInFiles& words, string a, string b) {
    return operatorWord(words, a, b, AND);
}

vector<FileResult> orOperator(WordsInFiles& words, string a, string b) {
    return operatorWord(words, a, b, OR);
}
vector<FileResult> minusOperator(WordsInFiles& words, string a, string b) {
    return operatorWord(words, a, b, MINUS);
}
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
    map<int, int> indexOfA;
    map<int, int> indexOfB;
    for (int i = 0; i < a.size(); i++)
    {
        fileCount[a[i].indexFile]++;
        indexOfA[a[i].indexFile] = i;
    }
    for (int i = 0; i < b.size(); i++)
    {
        fileCount[b[i].indexFile] += 2;
        indexOfB[b[i].indexFile] = i;
    }
    for (auto &file : fileCount)
    {
        int wordCounts = file.second;
        int index = file.first;
        if (operation == AND)
        {
            if (wordCounts == 3)
            {
                FileResult newFile;
                newFile.indexFile = index;
                newFile.listWord = a[indexOfA[index]].listWord;
                newFile.listWord.insert(newFile.listWord.end(),
                                        b[indexOfB[index]].listWord.begin(), b[indexOfB[index]].listWord.end());
                res.push_back(newFile);
            }
        }
        else if (operation == OR)
        {
            FileResult newFile;
            newFile.indexFile = index;
            if (indexOfA.find(index) != indexOfA.end())
                newFile.listWord = a[indexOfA[index]].listWord;
            newFile.listWord.insert(newFile.listWord.end(),
                                    b[indexOfB[index]].listWord.begin(), b[indexOfB[index]].listWord.end());
            res.push_back(newFile);
        }
        else if (operation == MINUS)
        {
            if (wordCounts == 1)
            {
                FileResult newFile;
                newFile.indexFile = index;
                newFile.listWord = a[indexOfA[index]].listWord;
                res.push_back(newFile);
            }
        }
    }
    return res;
}

vector<FileResult> findExact(WordsInFiles &wordsInFile, vector<string> words)
{
    vector<FileResult> res;
    // double initTime = 0;
    // if the string search is empty, then return empty result
    if (words.size() == 0)
        return res;

    //search the occurrences if files of the first word
    vector<FileResult> unionFile = wordsInFile.searchWord(words[0]);
    if (words.size() == 1)
        return unionFile;
    for (int i = 1; i < words.size(); i++)
    {
        vector<FileResult> next = wordsInFile.searchWord(words[i]);
        unionFile = operatorWord(wordsInFile, unionFile, next, AND);
    }

    CurrentFile currentFile;

    // currentFile is used for getting  word in the current checking file
    // cout << unionFile.size() << endl;
    for (auto &file : unionFile)
    {
        // for every file having the first word
        // go to every position of first word
        // check the next word is the same as the query string
        // if we get match, then add the position of the first word to the result file result

        // initialize the new file result
        FileResult result;
        result.indexFile = file.indexFile;

        int fileIndex = file.indexFile;

        // cout << "File Index: " << fileIndex << endl;
        for (auto &word : file.listWord)
        {

            bool found = true;
            int wordIndex = word.position;
            // cout << "Word Index: " << wordIndex << endl;

            // checking for matching exactly
            for (int i = 0; i < words.size(); i++)
            {

                // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                string temp = currentFile.getWordByIndex(fileIndex, wordIndex + i, false);
                // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                // initTime += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
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
    // std::cout << "Total time for find: " << initTime << endl;

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
        vector<FileResult> res;
        vector<FileResult> preWC = findExact(words, pre);
        vector<FileResult> afterWC = findExact(words, after);
        map<int, int> fileCount;
        map<int, int> indexFirst;
        map<int, int> indexSecond;
        for (int i = 0; i < preWC.size(); i++)
        {
            fileCount[preWC[i].indexFile]++;
            indexFirst[preWC[i].indexFile] = i;
        }

        for (int i = 0; i < afterWC.size(); i++)
        {
            fileCount[afterWC[i].indexFile]++;
            indexSecond[afterWC[i].indexFile] = i;
        }
        for (auto &file : fileCount)
        {
            if (file.second == 2)
            {
                int index = file.first;
                FileResult newFile;
                newFile.indexFile = index;
                // cout << index << endl;
                // cout << indexFirst[index] << " " << indexSecond[index] << endl;
                vector<Word> prePos = preWC[indexFirst[index]].listWord;
                vector<Word> postPos = afterWC[indexSecond[index]].listWord;
                for (auto &preW : prePos)
                {
                    for (auto &postW : postPos)
                    {
                        if (preW.position + pre.size() + WILDCARD_DIS > postW.position)
                        {
                            newFile.listWord.push_back(preW);
                        }
                    }
                }
                if (newFile.listWord.size() != 0)
                    res.push_back(newFile);
            }
        }
        return res;
    }
}
