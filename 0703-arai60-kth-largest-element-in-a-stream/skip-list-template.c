# include<stdlib.h>
# include<time.h>
# include<limits.h>
# include<stdio.h>

# define MAX_LEVEL 5

typedef struct SkipNode SkipNode;
struct SkipNode {
	int val;
	SkipNode *forward[MAX_LEVEL];  // レベル毎の「次のノード」へのポインタ配列
};

typedef struct SkipList SkipList;
struct SkipList {
	SkipNode *head;
	int level;
	int size;
};

int nums[50] = {
      342, -17, 891, -456, 73, -999, 512, 204, -333, 777,
      -88, 650, -721, 39, 486, -542, 913, -264, 155, -800,
      701, -412, 88, -955, 367, 234, -601, 819, -143, 500,
      -76, 423, -889, 614, -307, 992, -51, 738, -472, 181,
      -934, 556, 29, -680, 847, -218, 403, -763, 115, -500
};

int random_level(){
	int level = 0;
	// 確かに再開ビットが0 or 1でコイントスは計算できる
	// 1/4を書きたいなら, & 3 とかにすればいい
	while ( (rand() & 1) && level < MAX_LEVEL - 1) {
		level += 1;
	}

	return level;
}

void add_skipList(SkipList *sl, int val){
	int level = random_level();
	level = sl->level < level ? sl->level += 1 : level;

	SkipNode *cur = sl->head;
	SkipNode **update = calloc(level + 1, sizeof(SkipNode*));

	int tmp = level;
	while(level >= 0){
		while(cur->forward[level] && cur->forward[level]->val < val){
			cur = cur->forward[level];
		}
		update[level] = cur;
		level--;
	}

	SkipNode *add_node = calloc(1, sizeof(SkipNode));
	add_node->val = val;

	while(tmp >= 0){
		SkipNode *tmp_node;
		tmp_node = update[tmp]->forward[tmp];
		update[tmp]->forward[tmp] = add_node;
		update[tmp]->forward[tmp]->forward[tmp] = tmp_node;
		tmp--;
	}

	sl->size += 1;
}

SkipList *init_skiplist(int *nums, int numsSize){
	SkipList *sl = calloc(1, sizeof(SkipList));
	sl->head = calloc(1, sizeof(SkipNode));
	sl->level = 0;
	sl->head->val = INT_MIN;
	sl->size = 0;

	for (int i = 0; i < numsSize; i++){
		add_skipList(sl, nums[i]);
	}

	return sl;
}

typedef struct Result Result;
struct Result {
	int val;
	Result *next;
};

Result *search_count(SkipList *sl, int start, int end){
	int level = sl->level;
	SkipNode *cur = sl->head;

	while(level >= 0){
		while (cur->forward[level] && cur->forward[level]->val < start){
			cur = cur->forward[level];
		}
		level--;
	}

	Result dummy;
	Result *cur_res = &dummy;
	while(cur->forward[0] && cur->forward[0]->val <= end){
		cur_res->next = calloc(1, sizeof(Result));
		cur_res->next->val = cur->forward[0]->val;
		cur_res = cur_res->next;
		cur = cur->forward[0];
	}

	return dummy.next;
}

int main(){
	SkipList *sl = init_skiplist(nums, 50);
	Result *result = search_count(sl, -200, 700);

	while(result) {
		printf("%d\n", result->val);
		result = result->next;
	}

	return 0;
}
