#include "in-title.h"

bool cmpByNumber(FileResult a, FileResult b)
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
  sort(res.begin(), res.end(), cmpByNumber);
  vector<FileResult> fiveRes;
  for (int i = 0; i < min(5, (int)res.size()); ++i)
  {
    fiveRes.push_back(res[i]);
  }
  return fiveRes;
}
