// 同じものがあるかどうかのチェック・
// Input: strs = ["eat","tea","tan","ate","nat","bat"]
// Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
typedef struct HashMap HashMap;

struct HashMap {
};

char *strSort(char *str){
    int len =rstrlen(str);
}

char *** groupAnagrams(char **strs, int strsSize, int *returnSize, int **returnColumnSizes){
    char *sorted_strs = malloc(strsSize * sizeof(char*));
    for (int i=0; i < strsSize; i++){
        char *sorted_str[i] = strSort(strs[i]);
    }
}