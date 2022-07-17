#include <iostream>
#include <cstdlib>
#include <cstring>
#include "ListNode.h"
#include "ScoreList.h"

#ifndef TRIENODE_H
#define TRIENODE_H

using namespace std;

class TrieNode {
    private:
        TrieNode* sibling;
        TrieNode* child;
        ListNode* list;
        char value;
    public:
        TrieNode();
        ~TrieNode();
        void insert(char* token, int id);
        int tfSearchWord(int id, char* word, int cur);
        int dfSearchWord(char* word, int cur);
        void dfSearchAll(char* buffer, int cur);
        void search(char* word, int cur, ScoreList* scoreList);
};

#endif