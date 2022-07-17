#include "../include/ScoreList.h"

using namespace std;

ScoreList::~ScoreList() {
    if (next != NULL)
        delete(next);
}

void ScoreList::insert(int did) {
    if (id == did)
        return;
    if (id == -1)
        id = did;
    else {
        if (next == NULL)
            next = new ScoreList(did);
        else
            next->insert(did);
    }
}