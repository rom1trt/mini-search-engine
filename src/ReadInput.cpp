#include "../include/ReadInput.h"

using namespace std;

// @param: lineCounter: Number of lines of file
// @param: maxLength: Max length of document
// @param: doc: File's path
int read_size(int* lineCounter, int* maxLength, char* doc) {
    FILE* file = fopen(doc, "r");
    if (file == NULL) {
        cout << "Error while opening file" << endl;
        return -1;
    }
    char* line = NULL;
    // Return the size of the line that has been allocatd (nb characters)
    size_t falseBuffer = 0;
    int curLength;
    // Count how many lines we have
    while ((curLength=getline(&line, &falseBuffer, file)) != -1) {
        // Reach the end of a line
        if (*maxLength < curLength)
            *maxLength = curLength;
        (*lineCounter)++;
        free(line);
        line = NULL;
        falseBuffer=0;
    }
    fclose(file);
    free(line);
    // If no lines or no text (after tab) in file
    if (*lineCounter == 0 || *maxLength < 3) {
        cout << "Document does not meet requirements!" << endl;
        return -1;
    }
    return 1;
}

void split(char* temp, int id, TrieNode* trie, MyMap* myMap) {
    char* token = strtok(temp, " \t");
    int i = 0;
    while (token != NULL) {
        i++;
        trie->insert(token, id);
        token = strtok(NULL, " \t");
    }
    myMap->setLength(id, i);
    free(token);
}

int read_input(MyMap* myMap, TrieNode* trie, char* doc) {
    FILE *file = fopen(doc, "r");
    char* line = NULL;
    size_t falseBuffer = 0;
    int curLength = 0;
    char* temp = (char*) malloc(myMap->getBufferSize()*sizeof(char));

    for (int i=0;i<myMap->getSize();i++) {
        getline(&line, &falseBuffer, file);
        if (myMap->insert(line, i) == -1)
        {
            cout << "Document does not meet the requirements" << endl;
            fclose(file);
            free(line);
            free(temp);
            return - 1;
        }
        strcpy(temp, myMap->getDocument(i));
        split(temp, i, trie, myMap);
        free(line);
        line = NULL;
        falseBuffer = 0;
    }
    fclose(file);
    free(temp);
    return 1;
}