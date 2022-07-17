# Makefile

CC = g++ -fsanitize=address
CPPFLAGS = -MMD -Iinclude

OBJ = SearchEngine.o ReadInput.o Map.o TrieNode.o ListNode.o Search.o ScoreList.o MaxHeap.o
DEP = ${OBJ:.o=.d}

default: searchengine clean
searchengine: SearchEngine.o ReadInput.o Map.o TrieNode.o ListNode.o Search.o ScoreList.o MaxHeap.o
	$(CC) $(CPPFLAGS) -o searchengine SearchEngine.o ReadInput.o Map.o TrieNode.o ListNode.o Search.o ScoreList.o MaxHeap.o
MaxHeap.o: src/MaxHeap.cpp include/MaxHeap.h
	$(CC) $(CPPFLAGS) -c src/MaxHeap.cpp
ScoreList.o: src/ScoreList.cpp include/ScoreList.h
	$(CC) $(CPPFLAGS) -c src/ScoreList.cpp
Search.o: src/Search.cpp include/Search.h
	$(CC) $(CPPFLAGS) -c src/Search.cpp
ListNode.o: src/ListNode.cpp include/ListNode.h
	$(CC) $(CPPFLAGS) -c src/ListNode.cpp
TrieNode.o: src/TrieNode.cpp include/TrieNode.h
	$(CC) $(CPPFLAGS) -c src/TrieNode.cpp
Map.o: src/Map.cpp include/Map.h
	$(CC) $(CPPFLAGS) -c src/Map.cpp
ReadInput.o: src/ReadInput.cpp include/ReadInput.h
	$(CC) $(CPPFLAGS) -c src/ReadInput.cpp
SearchEngine.o: src/SearchEngine.cpp include/SearchEngine.h
	$(CC) $(CPPFLAGS) -c src/SearchEngine.cpp

clean:
	${RM} ${OBJ} ${DEP}

-include ${DEP}

# END