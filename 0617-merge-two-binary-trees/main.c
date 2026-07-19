void DFSearch(struct TreeNode* rnode, struct TreeNode* node1, struct TreeNode* node2){
	if (node1 == NULL && node2 == NULL) return;

	int val = 0;
	if (node1) val += node1->val;
	if (node2) val += node2->val;

	rnode->val = val;

	struct TreeNode *n1l = node1 ? node1->left : NULL;
	struct TreeNode *n1r = node1 ? node1->right : NULL;
	struct TreeNode *n2l = node2 ? node2->left : NULL;
	struct TreeNode *n2r = node2 ? node2->right : NULL;

	if (n1l || n2l) rnode->left = calloc(1, sizeof(struct TreeNode));
	if (n1r || n2r) rnode->right = calloc(1, sizeof(struct TreeNode));

	DFSearch(rnode->left, n1l, n2l);
	DFSearch(rnode->right, n1r, n2r);

	return;
}

struct TreeNode* mergeTrees(struct TreeNode* root1, struct TreeNode* root2){
	struct TreeNode *result = calloc(1, sizeof(struct TreeNode));

	if (!root1 && !root2) {
		return NULL;
	}

	DFSearch(result, root1, root2);

	return result;
}

