#include "../include/SearchEngine.h"

using namespace std;

int inputManager(char* input, TrieNode* trie, MyMap* myMap, int k) {
    char* token = strtok(input, " \t\n");
    if (!strcmp(token, "/search"))
        search(token, trie, myMap, k);
    else if (!strcmp(token, "/df"))
        df(trie);
    else if (!strcmp(token, "/tf")) {
        if (tf(token, trie) == -1)
            return -1;
    }
    else if (!strcmp(token, "/exit")) {
        cout << "Exiting..." << endl;
        token = NULL;
        free(token);
        return 2;
    }
    else
        return -1;
    token = NULL;
    free(token);
    return 1;
}

// Command idea: /searchengine -d <document-id> -k <n> (n biggest documents)
int main(int argc, char **argv) {
    if (argc != 5) {
        cout << "Wrong number of arguments" << endl;
    }
    if (strcmp(argv[1], "-d") || strcmp(argv[3], "-k")) {
        cout << "Wrong attributes" << endl;
    }
    cout << "Please Wait..." << endl;
    int lineCounter = 0;
    int maxLength = -1;
    int k = atoi(argv[4]); // Str to Int

    int readSize = read_size(&lineCounter, &maxLength, argv[2]);
    if (readSize == -1) {
        return -1;
    }
    MyMap* myMap = new MyMap(lineCounter, maxLength);
    TrieNode* trie = new TrieNode();
    int readInput = read_input(myMap, trie, argv[2]);
    // Error opening the file
    if (readInput ==  -1) {
        delete(myMap);
        return -1;
    }
    cout << "Database Ready" << endl;
    char* input = NULL;
    size_t inputLength = 0;
    while (1) {
        getline(&input, &inputLength, stdin);
        int ret = inputManager(input, trie, myMap, k);
        if (ret == -1)
            cout << "Wrong input" << endl;
        else if (ret == 2) {
            free(input);
            break;
        }
        inputLength = 0;
    }
    delete(myMap);
    delete(trie);
    return 1;
}