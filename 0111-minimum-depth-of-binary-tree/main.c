// struct TreeNode {
// 	int val;
// 	struct TreeNode *left;
// 	struct TreeNode *right;
// }

// DFS
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int DFSearch(struct TreeNode* node, int depth){
	// これは番兵値
	// 「子が存在しなかった」を表す番兵値。正常な値の集合に含まれない特別な値で状態を符号化する古典的なテクニック。Cの文字列終端'\0'やEOF(-1), mallocのNULLなどいたるところにある。
	int left_result = -1;
	int right_result = -1;

	if (node->left) {
		left_result = DFSearch(node->left, depth + 1);
	}
	if (node->right) {
		right_result = DFSearch(node->right, depth + 1);
	}

	if (left_result == -1 && right_result == -1){ 
		return depth;
	} else if (left_result != -1 && right_result == -1){
		return left_result;
	} else if (left_result == -1 && right_result != -1){
		return right_result;
	} else {
		return left_result > right_result ? right_result : left_result;
	}
}

int minDepth(struct TreeNode* root){
	if (root == NULL) return 0;
	if (root->right == NULL && root->left == NULL) return 1;

	int result = DFSearch(root, 1);

	return result;
}
