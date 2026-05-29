#include <stdlib.h>

typedef struct Node Node;
struct Node {
	int key;
	int value;
	Node *next;
};

typedef struct {
	Node **bucket;
	int size;
} HashMap;

unsigned int hash(int key, int size){
	return ( (unsigned int)key * 2654435761u ) % (unsigned int) size;
}

void get(HashMap *hm, int key, int *j){
	unsigned int index = hash(key, hm->size);
	Node *node = hm->bucket[index];

	while(node) {
		if (node->key == key ){
			*j = node->value;
			return;
		}

		node = node->next;
	}
}

void insert(HashMap *hm, int key, int value){
	unsigned int index = hash(key, hm->size);
	Node *node = hm->bucket[index];
	Node *cur = node;

	while(node){
		if(node->key == key){
			node->value = value;
			return;
		}

		node = node->next;
	}

	Node *new_node = malloc(sizeof(Node));
	new_node->key = key;
	new_node->value = value;
	new_node->next = cur;
	hm->bucket[index] = new_node;
}

int *twoSum(int *nums, int numsSize, int target, int *returnSize){
	int *result = malloc(2 * sizeof(int));

	HashMap *hash_map = malloc(sizeof(HashMap));
	hash_map->size = numsSize * 2;
	hash_map->bucket = calloc(numsSize * 2, sizeof(Node*));

	for (int i = 0; i < numsSize; i++){
		int complement = target - nums[i];

		int j = -1;                          /* -1 = 未発見 */
		get(hash_map, complement, &j);

		if (j != -1){
			result[0] = j;                   /* j が先に見つかったインデックス */
			result[1] = i;
			*returnSize = 2;
			return result;
		}

		insert(hash_map, nums[i], i);        /* nums[i] をキーとして登録 */
	}

	return NULL;
}
