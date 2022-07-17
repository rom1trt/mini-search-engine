#include "../include/TrieNode.h"

TrieNode::TrieNode() {
    sibling = NULL;
    child = NULL;
    list = NULL;
    value = -1;
}

TrieNode::~TrieNode() {
    if (list != NULL) {
        delete(list);
    }
    if (child != NULL) {
        delete(child);
    }
    if (sibling != NULL) {
        delete(sibling);
    }
}

void TrieNode::insert(char* token, int id) {
    if (value == -1 || value == token[0]) {
        value = token[0];
        if (strlen(token) == 1) {
            if (list == NULL)
                list = new ListNode(id);
            list->add(id);

        }
        else {
            if (child == NULL)
                child = new TrieNode();
            child->insert(token+1, id);
        }
    }
    else {
        if (sibling == NULL)
            sibling = new TrieNode();
        sibling->insert(token, id);
    }
}

int TrieNode::tfSearchWord(int id, char* word, int cur) {
    if (word[cur] == value) {
        if (cur == strlen(word) - 1) {
            if (list != NULL)
                return list->search(id);
            else
                return 0;
        }
        else {
            if (child != NULL)
                return child->tfSearchWord(id, word, cur+1);
            else
                return 0;
        }

    }
    else {
        if (sibling != NULL)
            return sibling->tfSearchWord(id, word, cur);
        else
            return 0;
    }
}

int TrieNode::dfSearchWord(char* word, int cur) {
    if (word[cur] == value) {
        if (cur == strlen(word) - 1) {
            if (list != NULL)
                return list->volume();
            else
                return 0;
        }
        else {
            if (child != NULL)
                return child->dfSearchWord(word, cur+1);
            else
                return 0;
        }
    }
    else {
        if (sibling != NULL)
            return sibling->dfSearchWord(word, cur);
        else
            return 0;
    }
}

void TrieNode::dfSearchAll(char* buffer, int cur) {
    buffer[cur] = value;
    if (list != NULL)
        cout << buffer << " " << list->volume() << endl;
    if (child != NULL)
        child->dfSearchAll(buffer, cur + 1);
    if (sibling != NULL)
        sibling->dfSearchAll(buffer, cur);
    buffer[cur] = '\0';
}

void TrieNode::search(char* word, int cur, ScoreList* scoreList) {
    if (word[cur] == value) {
        if (cur == strlen(word) - 1) {
            if (list != NULL)
                return list->passDocuments(scoreList);
            else
                return;
        }
        else {
            if (child != NULL)
                child->search(word, cur + 1, scoreList);
            else
                return;
        }
    }
    else {
        if (sibling != NULL) 
            sibling->search(word, cur, scoreList);
        else
            return;
    }
} 