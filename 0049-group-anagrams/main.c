// 同じものがあるかどうかのチェック・
// Input: strs = ["eat","tea","tan","ate","nat","bat"]
// Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

# include <stdlib.h>
# define MAX_INDEX 20011

typedef struct HashMap HashMap;
typedef struct Node Node;
typedef struct SortTmp SortTmp;

struct Node {
	char *sorted_str;
	int len;
	Node *next;

	char *origin_str;
	Node *anagram;

	Node *next_group;
	int count;
};

struct SortTmp {
	char *sorted;
	char *origin;
};

struct HashMap {
	Node **buckets;
};

void swap(char *str, int i, int j){
	char tmp = str[i];
	str[i] = str[j];
	str[j] = tmp;
}

int strLen(char *str){
	int len = 0;
	while(*str != '\0'){
		len++;
		str++;
	}

	return len;
}

int cmpstr(char *str1, char *str2){
	int len1 = strLen(str1);
	int len2 = strLen(str2);
	if (len1 != len2) return 0;

	for (int i=0; i < len1; i++){
		if (str1[i] != str2[i]) return 0;
	}

	return 1;
}

Node *hashMapInsert(HashMap *hm, unsigned int index, SortTmp *st){
	Node *c_node = hm->buckets[index];

	// hash値にすでに値がある場合
	if (c_node){
		Node *insert_node = NULL;
		while (c_node){
			if (cmpstr(c_node->sorted_str, st->sorted)){
				insert_node = c_node;
				break;
			}
			c_node = c_node->next;
		}

		// 一致する文字列が会った場合
		if (insert_node){
			Node *tmplist = insert_node->anagram;
			Node *new_anagram = calloc(1, sizeof(Node));
			new_anagram->origin_str = st->origin;
			new_anagram->anagram = tmplist;
			insert_node->anagram = new_anagram;
			insert_node->count += 1;

			return NULL;
		} else {
		// ハッシュ値は存在したが、競合値であった場合
			Node *tmp = hm->buckets[index];

			Node *node = calloc(1, sizeof(Node));
			Node *anagram = calloc(1, sizeof(Node));
			anagram->origin_str = st->origin;

			node->sorted_str = st->sorted;
			node->anagram = anagram;
			node->count += 1;
			node->len = strLen(st->origin) + 1;
			node->next = tmp;

			hm->buckets[index] = node;

			return node;
		}
	} else {
		Node *root_node = calloc(1, sizeof(Node));
		Node *anagram = calloc(1, sizeof(Node));
		anagram->origin_str = st->origin;
		root_node->sorted_str = st->sorted;
		root_node->anagram = anagram;
		root_node->count += 1;
		root_node->len = strLen(st->origin);
		hm->buckets[index] = root_node;

		return root_node;
	}
}

void quickSort(char *str, int left, int right){
	if (left >= right) return;

	int pivot = right;

	int store = left;
	for (int i = left; i < right; i++){
		if (str[i] < str[pivot]) {
			swap(str, store, i);
			store++;
		} } swap(str, store, pivot);

	quickSort(str, left, store-1);
	quickSort(str, store+1, right);

	return;
}



char *strSort(char *str){
	// 文字列をアルファベット順にソートして、新しい変数ポインタで返す
	int len = strLen(str);

    	char *sorted_str = malloc(len+1);
	char *base = sorted_str;

	while (*str != '\0'){
		*sorted_str = *str;
		sorted_str++;
		str++;
	}
	*sorted_str = '\0';

	// lenは、最後の\0を含まないながさ
	quickSort(base, 0, len-1);
	
	return base;
}

unsigned int hashStr2Int(char *str){
	// 文字列をハッシュ化する
	unsigned int hash = 5381;
	unsigned int c;
	while ((c = *str++)){
		hash = hash * 33 + c;
	}

	return (unsigned int) (hash % MAX_INDEX);
}

HashMap *initHashMap(){
	HashMap *hm = malloc(sizeof(HashMap));
	hm->buckets = calloc(MAX_INDEX, sizeof(Node*));

	return hm;
}

void push (Node *grn, Node *group_root_node){
	Node *tmp = grn->next_group;
	grn->next_group = group_root_node;
	grn->next_group->next_group = tmp;

	return;
}

char ***groupAnagrams(char **strs, int strsSize, int *returnSize, int **returnColumnSizes){
    SortTmp *tmp = calloc(strsSize, sizeof(SortTmp));
    HashMap *hm = initHashMap();
    Node *grn = NULL;

    for (int i=0; i < strsSize; i++){
	    tmp[i].origin = strs[i];
	    tmp[i].sorted = strSort(strs[i]);
    }


    for (int i=0; i < strsSize; i++){
	    unsigned int hash_i = hashStr2Int(tmp[i].sorted);
	    Node *group_root_node = hashMapInsert(hm, hash_i, &tmp[i]);
	    if (group_root_node) {
		    if (grn == NULL){
			    grn = group_root_node;
		    } else {
			    push(grn,group_root_node);
		    }
	    }
	    

    }
    int layer_1 = 0;
    Node *tmp_grn = grn;
    while(tmp_grn){
	    layer_1 += 1;
	    tmp_grn = tmp_grn->next_group;
    }

    *returnSize = layer_1;

    *returnColumnSizes = calloc(layer_1, sizeof(int));

    char ***result =  calloc(layer_1, sizeof(char**));

    for (int i=0; i < layer_1; i++){
	    Node *cur_ana = grn->anagram;
	    (*returnColumnSizes)[i] = grn->count;

	    char **result_i = calloc(grn->count, sizeof(char*));
	    for(int j=0; j < grn->count; j++){
		    result_i[j] = cur_ana->origin_str;
		    cur_ana = cur_ana->anagram;
	    }
	    result[i] = result_i;
	    grn = grn->next_group;
    }

    return result;
}
