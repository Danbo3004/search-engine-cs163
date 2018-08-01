#include "searchFile.h"

int Trie::findNode(string Word)
{
  if (listNode.size() == 0) 
  {
    Node newNode;
    newNode.init();
    listNode.push_back(newNode);
  }
  int cur = 0;
  int curWord = 0;
  while (cur != -1 && curWord < Word.length())
  {
    cur = listNode[cur].pNext[Word[curWord]];
    curWord++;
  }
  return cur;
};

void Trie::insertWord(int indexFile, int position, int isTitle, string word)
{
  if (listNode.size() == 0) 
  {
    Node newNode;
    newNode.init();
    listNode.push_back(newNode);
  }
  int cur = 0;
  Word newWord;
  newWord.position = position;
  newWord.isTitle = isTitle;
  int curWord = 0;
  while (curWord < word.length())
  {
    if (listNode[cur].pNext[word[curWord]] == -1)
    {
      Node newNode;
      newNode.init();
      listNode.push_back(newNode);
      listNode[cur].pNext[word[curWord]] = listNode.size() - 1;
    }
    cur = listNode[cur].pNext[word[curWord++]];
  }
  if (listNode[cur].files.back().indexFile == indexFile)
  {
    listNode[cur].files.back().listWord.push_back(newWord);
  }
  else
  {
    FileResult newFile;
    newFile.indexFile = indexFile;
    newFile.listWord.push_back(newWord);
    listNode[cur].files.push_back(newFile);
  }
}

vector<FileResult> WordsInFiles::searchWord(string Word)
{
  int resNode;
  vector<FileResult> res;
  resNode = data.findNode(Word);
  if (resNode == -1)
    return res;
  else
  {
    res = data.listNode[resNode].files;
    return res;
  }
}

void WordsInFiles::Init()
{
  for (int i = 0; i < 100; ++i) {
  }
}