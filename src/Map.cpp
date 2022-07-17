#include "../include/Map.h"

using namespace std;

MyMap::MyMap(int size, int bufferSize):size(size),bufferSize(bufferSize)
{
    documents = (char**) malloc(size*sizeof(char*));
    lengths = (int*) malloc(size*sizeof(int));
    for (int i=0;i<size;i++) {
        documents[i]=(char*) malloc(bufferSize*sizeof(char));
    }
}

MyMap::~MyMap() {
    for(int i=0;i<size;i++) {
        free(documents[i]);
    }
    free(documents);
    free(lengths);
}

int MyMap::insert(char* line, int i) {
    int cur;
    // break the string when it encounters a tab
    char* token = token = strtok(line, " \t");
    // Str to Int
    cur = atoi(token);
    if (cur != i) {
        token = NULL;
        free(token);
        return -1;
    }
    token = strtok(NULL, "\n");
    // Get rid of the useless spaces
    while (token[0] == ' ') {
        token++;
    }
    int end = 0;
    while (token[end] != '\0') {
        end++;
    }
    end--;
    while (end != 0 && token[end] == ' ') {
        token[end--] = '\0';
    }
    // Copies a character string from src to destination
    strcpy(documents[i], token);
    token = NULL;
    free(token);
    return 0;
}