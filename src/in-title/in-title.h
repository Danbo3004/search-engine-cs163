#ifndef in_title_h
#define in_title_h

#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "helpers.h"
#include "searchFile.h"

using namespace std;

struct responseFile {
    int indexFile;
    string description, title;
    responseFile() {
        description = "";
        title = "";
    }
};

vector <responseFile> searchInTitle(string word);

bool cmpByNumber(FileResult a, FileResult b);

responseFile convertResponseToFile(FileResult response, bool searchInTitle);

#endif
