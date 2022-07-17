#include <iostream>
#include <cstdlib>

#ifndef SCORELIST_H
#define SCORELIST_H

class ScoreList {
    private:
        int id;
        ScoreList* next;
    public:
        ScoreList(int did=-1) {
            id = did;
            next = NULL;
        }
        ~ScoreList();
        void insert(int did);
        ScoreList* getNext() {
            return next;
        }
        int getId() {
            return id;
        }
};

#endif