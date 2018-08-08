#include "searchFile.h"
void unionVector(std::vector<FileResult>& results,std::vector<FileResult>& tmp ){
	std::vector<FileResult>::iterator vFileResultIter;
	if (results.size()){
		 for (std::vector<FileResult>::iterator resIt = results.begin(); resIt != results.end(); resIt++ ){
			 FileResult resi = *resIt;
			 vFileResultIter = std::find_if(tmp.begin(), tmp.end(), [&resi](const FileResult& file){
																	 return file.indexFile == resi.indexFile;
																	 });
			 //merging
			 std::set_union(resIt->listWord.begin(), resIt->listWord.end(),
									 vFileResultIter->listWord.begin(), vFileResultIter->listWord.end(),resIt->listWord.begin(),
									 [](const Word &a, const Word &b) {
										return a.position < b.position;
									});
			 if (resIt == results.end()) break;
		 }

	 }
	 else{
		 results = tmp;
	 }
}

void intersectVector(std::vector<FileResult>& results,std::vector<FileResult>& tmp ){
	std::vector<FileResult>::iterator vFileResultIter;
	if (results.size()){
		 for (std::vector<FileResult>::iterator resIt = results.begin(); resIt != results.end(); resIt++ ){
			 FileResult resi = *resIt;
			 vFileResultIter = std::find_if(tmp.begin(), tmp.end(), [&resi](const FileResult& file){
																	 return file.indexFile == resi.indexFile;
																	 });
			 //merging
			 std::set_intersection(resIt->listWord.begin(), resIt->listWord.end(),
									 vFileResultIter->listWord.begin(), vFileResultIter->listWord.end(),resIt->listWord.begin(),
									 [](const Word &a, const Word &b) {
										return a.position < b.position;
									});
			 if (resIt == results.end()) break;
		 }

	 }
	 else{
		 results = tmp;
	 }
}

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
