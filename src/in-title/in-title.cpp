#include "in-title.h"

WordsInFiles TmpData;

bool cmpByNumber(FileResult a, FileResult b){
    return a.listWord.size() > b.listWord.size();
}

vector <responseFile> searchInTitle(string word){
    vector <FileResult> responses = TmpData.searchWord(word);
    vector <FileResult> inTitleResponses;
    for (int i = 0; i < (int)responses.size(); ++i){
        FileResult file = responses[i];
        for (int j = 0; j < (int)file.listWord.size(); ++i){
            Word w = file.listWord[i];
            if (w.isTitle) {
                inTitleResponses.push_back(responses[i]);
                break;
            }
        }
    }
    sort(inTitleResponses.begin(), inTitleResponses.end(), cmpByNumber);
    vector <responseFile> files;
    for (int i = 0; i < min(5, (int)inTitleResponses.size()); ++i){
        FileResult response = inTitleResponses[i];
        files.push_back(convertResponseToFile(response, true));
    }
    return files;
}

responseFile convertResponseToFile(FileResult response, bool searchInTitle){
    DataFile file = readFile(response.indexFile);
    responseFile res;
    res.indexFile = response.indexFile;
    for (int i = 0; i < (int)file.title.size(); ++i){
        res.title += file.title[i];
    }
    int firstInContent = -1;
    for (int i = 0; i < response.listWord.size(); ++i){
        Word word = response.listWord[i];
        if (!word.isTitle){
            firstInContent = i;
            break;
        }
    }
    if (searchInTitle || firstInContent == -1){
        for (int i = 0; i < min(20, (int)file.content.size()); ++i){
            res.description += file.content[i];
        }
    }
    else {
        int pos = response.listWord[firstInContent].position;
        for (int i = max(0, pos - 10); i < min(pos + 10, (int)file.content.size()); ++i){
            res.description += file.content[i];
        }
    }
    return res;
}




