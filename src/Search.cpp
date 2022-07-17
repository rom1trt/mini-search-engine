#include "../include/Search.h"

const float K1 = 1.2;
const float B = 0.75;

void search(char* token,TrieNode* trie,MyMap* map,int k)
{
    char wordArray[10][256];
    double IDF[10];
    token = strtok(NULL, " \t\n");
    ScoreList* scoreList = new ScoreList();
    int i;
    for(i=0;i<10;i++) {
        if(token == NULL)
            break;
        strcpy(wordArray[i], token);
        double c = ((double)map->getSize()-(double)trie->dfSearchWord(wordArray[i],0)+0.5)/((double)trie->dfSearchWord(wordArray[i],0)+0.5);
        IDF[i] = log10(c);
        trie->search(wordArray[i], 0, scoreList);
        token = strtok(NULL, " \t\n");
    }
    double avgdl = 0;
    for(int m=0;m<map->getSize();m++)
        avgdl += (double)map->getLength(m);
    avgdl /= (double)map->getSize();
    double score = 0;
    ScoreList* tempList = scoreList;
    MaxHeap* heap = new MaxHeap(k);
    int ceil = 0;
    while(tempList != NULL) {
        for(int l=0;l<i;l++)
            score += IDF[l]*((double)trie->tfSearchWord(tempList->getId(),wordArray[l],0)*(K1+1.0))/((double)trie->tfSearchWord(tempList->getId(),wordArray[l],0)+K1*(1.0-B+B*(double)map->getLength(tempList->getId())/(double)avgdl));
        heap->insert(score,tempList->getId());
        score=0;
        tempList=tempList->getNext();
        ceil++;
    }
    if (ceil > k)
        ceil = k;
        
    struct winsize w;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&w);

    for (int l=0;l<ceil;l++) {
        int id = heap->getId();
        if (id == -1)
            break;
        double score = (double)heap->remove();
        cout << "( " << id;
        int x = 10;
        int f = 1;
        while (id/x != 0) {
            x *= 10;
            f++;
        }
        while (5-f >= 0) {
            cout << " ";
            f++;
        }
        printf(")[%10.6f] ", score);
        char* line = (char*)malloc(map->getBufferSize()*sizeof(char));
        strcpy(line, map->getDocument(id));
        char* temp = strtok(line, " \t\n");
        int curLength = 0;
        int counter = 0;
        int newLine = 1;
        int lineFlag = 0;
        int underline[2][100];
        int uCounter = 0;
        while (temp != NULL) {
            if (newLine) {
                curLength += 20;
                if (counter != 0) {
                    for (int co=0;co < 20;co++)
                        cout << " ";
                }
                newLine = 0;
            }

            for (int n=0;n<i;n++) {
                if (!strcmp(wordArray[n], temp)) {
                    if (curLength+strlen(temp)+1 <= w.ws_col) {
                        underline[0][uCounter] = curLength;
                        underline[1][uCounter] = strlen(temp);
                        uCounter++;
                        lineFlag = 1;
                    }
                    break;
                }
            }
            curLength += strlen(temp) + 1;
            if (curLength-1 >= w.ws_col) {
                curLength = 0;
                newLine = 1;
                cout << endl;
                if (lineFlag) {
                    char* outputLine = (char*)malloc((w.ws_col+1)*sizeof(char));
                    for (int j=0;j<w.ws_col;j++)
                        outputLine[j] = ' ';
                    outputLine[w.ws_col] = '\0';
                    lineFlag = 0;
                    for (int j=0;j<uCounter;j++) {
                        for (int v=underline[0][j];v<underline[0][j]+underline[1][j];v++)
                            outputLine[v] = '^';
                    }
                    uCounter = 0;
                    cout << outputLine;
                    free(outputLine);
                }
                continue;
            }
            cout << temp << " ";
            temp = strtok(NULL, " \t\n");
            counter++;
        }
        cout << endl;
        free(line);
        free(temp);
    }
    delete(heap);
    delete(scoreList);
    cout << endl;
}


void df(TrieNode* trie) {
    char* token2 = strtok(NULL, " \t\n");
    if (token2 != NULL)
        cout << token2 << " " << trie->dfSearchWord(token2, 0) << endl;
    else {
        char* buffer = (char*) malloc(256*sizeof(char));
        // Set all the memory spaces to \0 (unsigned char)
        memset(buffer,'\0',256);
        trie->dfSearchAll(buffer, 0);
        free(buffer);
    }
    token2 = NULL;
    free(token2);
}

int tf(char* token, TrieNode* trie) {
    char* token2 = strtok(NULL, " \t\n");
    if (token2 == NULL) {
        free(token2);
        return -1;
    }
    for (int l=0; l<strlen(token2);l++) {
        if (!isdigit(token2[l])) {
            token2 = NULL;
            free(token2);
            return -1;
        }
    }
    int id = atoi(token2);
    token2 = strtok(NULL, " \t\n");
    if (token2 == NULL) {
        free(token2);
        return -1;
    }
    cout << id << " " << token2 << " " << trie->tfSearchWord(id, token2, 0) << endl;
    return 0;
}