#ifndef _SEARCH_FILE_
#define _SEARCH_FILE_

#include "helpers.h"

using namespace std;

struct Word
{
  int position;
  int isTitle;
};

struct FileResult
{
  int indexFile;
  vector<Word> listWord;
};

struct Node
{
  vector<FileResult> files;
  int pNext[256];
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
  void Init();
};

#endif
