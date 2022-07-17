#include <iostream>
#include <cstdlib>
#include <cstring>
#include "ScoreList.h"

#ifndef LISTNODE_H
#define LISTNODE_H

using namespace std;

class ListNode {
    private:
        ListNode* next; // Next list item
        int id; // Document ID
        int times; // How many times it appear in the document
    public:
        ListNode(int did) {
            id = did;
            times = 0;
            next = NULL;
        };
        ~ListNode();
        void add(int did);
        int search(int did);
        // How many documents is the word in
        int volume();
        // To update the score list
        void passDocuments(ScoreList* scoreList);
};

#endif