# define MAX_LEVEL 16

typedef struct SkipNode SkipNode;
struct SkipNode {
	int val;
	SkipNode *forward[MAX_LEVEL];  // レベル毎の「次のノード」へのポインタ配列
};

typedef SkipList SkipList;
struct SkipList {
	SkipNode *head;
	int level;
	int size;
};

