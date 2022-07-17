#include <iostream>
#include <cstdlib>
#include <cstring>

#ifndef MAP_H
#define MAP_H

using namespace std;

class MyMap
{
    private:
        int size; // Number of documents
        int bufferSize; // Length of the biggest document
        char** documents; // Each document
        int* lengths; // Each document's length
    public:
        MyMap(int size, int bufferSize);
        ~MyMap();
        const int getSize() {
            return size;
        };
        const int getBufferSize() {
            return bufferSize;
        };
        int getLength(int id) {
            return lengths[id];
        };
        void setLength(int id, int length) {
            lengths[id]=length;
        };
        int insert(char* line, int i);
        void print(int i) {
            cout << i << " " << documents[i] << endl;
        };
        char* getDocument(int i) {
            return documents[i];
        };
};

#endif