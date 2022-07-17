#include <iostream>
#include <cstdlib>
#include <cstring>
#include "TrieNode.h"
#include "ScoreList.h"
#include "MaxHeap.h"
#include "Map.h"
#include <cmath>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

void search(char* toke, TrieNode* trie, MyMap* myMap, int k);
void df(TrieNode* trie);
int tf(char* token, TrieNode* trie);