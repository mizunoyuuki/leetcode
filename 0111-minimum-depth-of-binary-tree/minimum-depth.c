// struct TreeNode {
// 	int val;
// 	struct TreeNode *left;
// 	struct TreeNode *right;
// }

typedef struct TreeNode TreeNode;
typedef struct Node Node;
struct Node {
	int depth;
	struct TreeNode* treeNode;
};

int BFSearch(struct TreeNode* root){
	Node **queue = malloc(100000 * sizeof(Node*));
	int head = 0;
	int tail = 0;

	Node *first_node = malloc(sizeof(Node));
	first_node->depth = 1;
	first_node->treeNode = root;

	queue[head++] = first_node;
	// ここで準備は完了
	
	while(tail < head){
		Node *node = queue[tail++];
		int depth = node->depth;
		if (node->treeNode->left == NULL && node->treeNode->right == NULL){
			return depth;
		}

	       	if (node->treeNode->left){
			Node *ln = calloc(1, sizeof(Node));
			ln->treeNode = node->treeNode->left;
			ln->depth = depth + 1;
			queue[head++] = ln;
		}

		if (node->treeNode->right) {
			Node *rn = calloc(1, sizeof(Node));
			rn->treeNode = node->treeNode->right;
			rn->depth = depth + 1;
			queue[head++] = rn;
		}
	}

	return -1;
}

int minDepth(struct TreeNode* root){
	if (root == NULL) return 0;
	if (root->right == NULL && root->left == NULL) return 1;

	int result = BFSearch(root);

	return result;
}

