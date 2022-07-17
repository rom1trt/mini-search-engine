#include <iostream>
#include "Map.h"
#include "TrieNode.h"

int read_size(int* lineCounter, int* maxLength, char* doc);
void split(char* temp, int id, TrieNode* trie, MyMap* myMap);
int read_input(MyMap* myMap, TrieNode* trie, char* doc);