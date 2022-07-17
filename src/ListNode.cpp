#include "../include/ListNode.h"

ListNode::~ListNode() {
    if (next != NULL)
        delete(next);
}

void ListNode::add(int did) {
    if (did == id)
        times++;
    else {
        if (next == NULL)
            next = new ListNode(did);
        next->add(did);
    }
}

int ListNode::search(int did) {
    if (did == id)
        return times;
    else {
        if (next == NULL)
            return 0;
        else
            return next->search(did);
    }
}

int ListNode::volume() {
    if (next != NULL)
        return 1 + next->volume();
    else
        return 1;
}

void ListNode::passDocuments(ScoreList* scoreList) {
    scoreList->insert(id);
    if (next != NULL)
        next->passDocuments(scoreList);
}
