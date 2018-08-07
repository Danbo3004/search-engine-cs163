#include "price.h"

vector<FileResult> searchPrice(WordsInFiles &wordsInFiles, string object, string price)
{
  map<int, int> fileIndex;
  vector<FileResult> res;

  vector<FileResult> objectFiles = wordsInFiles.searchWord(object);
  for (int i = 0; i < (int)objectFiles.size(); ++i)
  {
    FileResult newFile;
    newFile.indexFile = objectFiles[i].indexFile;
    newFile.listWord.push_back(objectFiles[i].listWord[0]);
    objectFiles[i] = newFile;
    fileIndex[newFile.indexFile] = i;
  }

  vector<FileResult> priceFiles = wordsInFiles.searchWord(price);
  for (int i = 0; i < (int)priceFiles.size(); ++i)
  {
    FileResult file = priceFiles[i];
    if (fileIndex.count(file.indexFile))
    {
      int pos = fileIndex.count(file.indexFile);
      objectFiles[pos].listWord.push_back(file.listWord[0]);
      res.push_back(objectFiles[pos]);
    }
  }

  vector<FileResult> fiveRes;
  for (int i = 0; i < min(5, (int)res.size()); ++i)
  {
    fiveRes.push_back(res[i]);
  }
  return fiveRes;
}

int convertStringToNumber(string str){
  int num = 0;
  for (int i = 0; i < (int)str.length(); ++i){
    num = num * 10 + str[i] - '0';
  }
  return num;
}

vector<FileResult> searchInRange(WordsInFiles &wordsInFiles, string object, string minPrice, string maxPrice){
  int low = convertStringToNumber(minPrice.substr(1, minPrice.length() - 1));
  int high = convertStringToNumber(maxPrice.substr(1, maxPrice.length() - 1));

  vector <FileResult> res;

  for (int p = low; p < high; ++p){
    string price = "$" + convertNumberToString(p);
    vector <FileResult> files = searchPrice(wordsInFiles, object, price);
    while (res.size() < 5 && !files.empty()){
      res.push_back(files.back());
      files.pop_back();
    }
  }
  
  return res;
}