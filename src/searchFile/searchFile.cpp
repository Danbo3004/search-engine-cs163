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
    cur = listNode[cur].pNext[int(Word[curWord]) + 127];
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
    if (listNode[cur].pNext[int(word[curWord]) + 127] == -1)
    {
      Node newNode;
      newNode.init();
      listNode.push_back(newNode);
      listNode[cur].pNext[int(word[curWord]) + 127] = listNode.size() - 1;
    }
    cur = listNode[cur].pNext[int(word[curWord++]) + 127];
  }
  if (listNode[cur].files.size() != 0 && listNode[cur].files.back().indexFile == indexFile)
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

WordsInFiles::WordsInFiles()
{

  for (int g = 1; g <= 25; g++)
  {
    // if (g == 8 || g == 10 || g== 14 || g == 16 || g == 19 || g == 20
    // || g == 23 || g == 24 ) continue;

    for (int i = 0; i < 100; ++i)
    {
      int indexFile = g * 100 + i;
      // int indexRead = 9*100 + i;
      // log(std::to_string(indexFile));
      // log("");
      // cout << indexFile << ": " << endl;
      DataFile dataFile = readFile(indexFile);
      // cout << dataFile.content.size() << "  " << dataFile.title.size() << endl;
      // cout << indexFile << ": ";
      // cout << dataFile.content.size () << "  " << dataFile.title.size() << endl;
      for (int j = 0; j < dataFile.title.size(); ++j)
        data.insertWord(indexFile, j, 1, dataFile.title[j]);
      for (int j = 0; j < dataFile.content.size(); ++j)
        data.insertWord(indexFile, j, 0, dataFile.content[j]);
      // cout << "Insert done" << endl;
    }
  }
}

string CurrentFile::getWordByIndex(int fileRequest, int wordIndex, bool isTitle)
{
  if (fileRequest != indexFile)
    file = readFile(fileRequest);
  indexFile = fileRequest;
  if (isTitle)
  {
    if (file.title.size() <= wordIndex)
      return "";
    else
      return file.title[wordIndex];
  }
  else
  {
    if (file.content.size() <= wordIndex)
      return "";
    else
      return file.content[wordIndex];
  }
}
