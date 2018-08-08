#ifndef _SEARCH_FILE_
#define _SEARCH_FILE_

#include "../helpers/helpers.h"

using namespace std;

struct Word
{
  int position;
  bool isTitle;
};

struct FileResult
{
  int indexFile;
  vector<Word> listWord;
};

void unionVector(std::vector<FileResult>&,std::vector<FileResult>&);
void intersectVector(std::vector<FileResult>&,std::vector<FileResult>&);

struct Node
{
  vector<FileResult> files;
  int pNext[300];
  void init()
  {
    memset(pNext, -1, sizeof pNext);
  }
};

struct Trie
{
  vector<Node> listNode;
  void insertWord(int indexFile, int position, int isTitle, string Word);
  int findNode(string Word);
};

class WordsInFiles
{
private:
  Trie data;

public:
  vector<FileResult> searchWord(string word);
  WordsInFiles();
};

class CurrentFile
{
  private:
    int indexFile = -1;
    DataFile file;
  public:
    string getWordByIndex(int fileRequest, int wordIndex, bool isTitle);  
};

#endif
