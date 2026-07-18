# include <stdbool.h>
# include <string.h>
# include <stdlib.h>

typedef struct Node Node;
struct Node {
	int count;
	int wordListIndex;
};

Node **queue;
static int *visited_sheet;
static unsigned int head;
static unsigned int tail;

// 一文字違いの文字列か判定する関数
bool isOneDiff(const char *source, const char *target){
	int diff = 0;
	for (int i = 0; source[i] != '\0' && target[i] != '\0'; i++){
		if (source[i] != target[i]) diff++;
		if (diff > 1) return false;
	}

	return diff == 1;
}

bool is_there_endWord(char **wordList, int wordListSize, char *endWord){
	int endWordIndex = -1;

	for (int i = 0; i < wordListSize; i++){
		if (strcmp(endWord, wordList[i]) == 0) {
			endWordIndex = i;
			break;
		}
	}

	return endWordIndex != -1;
}

void initQueue(int size){
	queue = malloc(size * sizeof(Node*));
	visited_sheet = calloc(size, sizeof(int));
	head = 0;
	tail = 0;

	return;
}

Node *dequeue(){
	return queue[tail++];
}

void enqueue(Node *node){
	queue[head++] = node;
	visited_sheet[node->wordListIndex] = 1;

	return;
}

int ladderLength(char *beginWord, char *endWord, char **wordList, int wordListSize){
	int count = 0;
	if (!is_there_endWord(wordList, wordListSize, endWord)) return count;
	if (wordListSize == 0) return 1;

	// staticなqueue, visited_sheet, head, tailを持つ
	initQueue(wordListSize);

	for (int i = 0; i < wordListSize; i++){
		if (isOneDiff(beginWord, wordList[i])){
			if (strcmp(wordList[i], endWord) == 0) return 2;

			Node *node = malloc(sizeof(Node));
			node->count = 2;
			node->wordListIndex = i;

			queue[head++] = node;
			visited_sheet[i] = 1;
		}
	}

	while (tail < head) {
		Node* c_node = dequeue();
		int current_index = c_node->wordListIndex;

		for (int i = 0; i < wordListSize; i++){
			if (isOneDiff(wordList[current_index], wordList[i]) && !visited_sheet[i]){
				if (strcmp(wordList[i], endWord) == 0) return c_node->count + 1;

				Node *node = calloc(1, sizeof(Node));
				node->count = c_node->count + 1;
				node->wordListIndex = i;

				enqueue(node);
			}
		}
		if (head == tail) return 0;
	}

    return 0;
}
