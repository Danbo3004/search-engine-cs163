#include "./inTitle.h"

bool cmpInTitleByNumber(FileResult a, FileResult b)
{
  return a.listWord.size() > b.listWord.size();
}

vector <FileResult> searchInTitle(WordsInFiles &wordsInFiles, vector <string> words)
{
  map <int, int> fileCount;
  map <int, int> filePos;
  vector<FileResult> res;
  for (int i = 0; i < (int)words.size(); ++i)
  {
    string word = words[i];
    vector<FileResult> found = wordsInFiles.searchWord(word);
    for (int j = 0; j < (int)found.size(); ++j)
    {
      FileResult file = found[j];
      bool inTitle = false;
      for (int k = 0; k < (int)file.listWord.size(); ++k)
      {
        Word tmp = file.listWord[k];
        if (tmp.isTitle)
        {
          inTitle = true;
          break;
        }
      }
      if (inTitle){
        if (!fileCount.count(file.indexFile)){
          if (i != 0) break;
          fileCount[file.indexFile] = 1;
          filePos[file.indexFile] = res.size();
          FileResult newFile;
          newFile.indexFile = file.indexFile;
          newFile.listWord.push_back(file.listWord[0]);
          res.push_back(newFile);
        }
        else {
          ++fileCount[file.indexFile];
          int pos = filePos[file.indexFile];
          FileResult newFile = res[pos];
          newFile.listWord.push_back(file.listWord[0]);
          res[pos] = newFile;
        }
      }
    }
  }

  //cout << "Found: " << res.size() << "\n";

//  // Including all words
//  vector <FileResult> filterRes;
//  int len = words.size();
//  for (int i = 0; i < (int)res.size(); ++i){
//    FileResult file = res[i];
//    if (fileCount[file.indexFile] == len) {
//      filterRes.push_back(file);
//    }
//  }
//
//  sort(filterRes.begin(), filterRes.end(), cmpInTitleByNumber);
//  vector<FileResult> fiveRes;
//  for (int i = 0; i < min(5, (int)filterRes.size()); ++i)
//  {
//    fiveRes.push_back(filterRes[i]);
//  }
//  return fiveRes;
  return res;
}
