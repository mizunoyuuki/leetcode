typedef struct Node Node;

struct Node {
    int val;
    int count;
    Node *left;
    Node *right;
};

typedef struct KthLargest {
	int k;
	Node *root;
} KthLargest;

void binarytree_insert(Node *cur, int val){
    // 一番下に来た
    if (cur->val < val){
        if (cur->right == NULL){
             Node *new = calloc(1, sizeof(Node));
             new->val = val;
	     new->count = 1;
             cur->right = new;
             return;
        }
        binarytree_insert(cur->right, val);
    } else if (cur->val > val) {
        if (cur->left == NULL){
             Node *new = calloc(1, sizeof(Node));
             new->val = val;
	     new->count = 1;
             cur->left = new;
             return;
        }
        binarytree_insert(cur->left, val);
    } else if (cur->val == val){
        cur->count += 1;
        return;
    }
}

Node* binarytree_search(Node *cur, int k, int *count){
    if (cur == NULL) return NULL;

    Node *right = binarytree_search(cur->right, k, count);

    if (right) return right;

    *count += cur->count;

    if (*count >= k) return cur;

    Node *left = binarytree_search(cur->left, k, count);

    if (left) return left;

    return NULL;
}


KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    Node *root = calloc(1, sizeof(Node));
    
    if (numsSize == 0){
        root->val = 10;
        root->count = 0;
    } else {
        root->val = nums[0];
        root->count = 1;
    }
    KthLargest *kl = calloc(1, sizeof(KthLargest));
    kl->k = k;
    kl->root = root;

    // 二分木の初期化
    for(int i = 1; i < numsSize; i++){
        binarytree_insert(root, nums[i]);
    }

    return kl;
}

int kthLargestAdd(KthLargest* obj, int val) {
    binarytree_insert(obj->root, val);


    int count = 0;
    Node *result = binarytree_search(obj->root, obj->k, &count);

    return result->val;
}

void kthLargestFree(KthLargest* obj) {

}
