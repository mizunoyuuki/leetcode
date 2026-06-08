/* 優先度付きキュー 
 * //https://zenn.dev/derbuihan/articles/06deb2f379da4d
 * このサイトを元に優先度付きキューを実装してみる。
 *
 *
 * 優先度付きキューとは、キーと値のペアを格納するデータ構造
 * キーには優先度が設定されており、値はそのキーに対応するデータ。
 * 優先度付きキューは、キーの値が大きい順にデータを取り出すことができる。
 *
 *
 * 優先度付きキューは、二分木を使って実装される。各ノードにおいて、親ノードよりも小さい値を持つノードは左に、大きい値を持つノードは右に配置される木構造
 *
 * こうすることで、データの挿入や取り出しの計算量がO(log(n))で行うことができる。
 *
 *
 * データ構造
 * typedef struct PgNode PgNode;
 * struct PqNode {
 *   int id;
 *   float priority;
 *   PgNode *left;
 *   PgNode *right;
 * };
 *
 * typedef struct PriorityQueue PriorityQueue;
 * struct PriorityQueue {
 *   PqNode *root;
 *   int size;
 * };
 */


/* 優先度付きキューの構造体 */
typedef struct PqNode PqNode;
struct PqNode {
	int id;
	float priority;
	PqNode *left;
	PqNode *right;
};

typedef struct PriorityQueue PriorityQueue;
struct PriorityQueue {
	PqNode *root;
	int size;
};

PriorityQueue *new_priority_queue() {
	PriorityQueue *queue = malloc(sizeof(PriorityQueue));
	queue->root = NULL;
	queue->size = 0;

	return queue;
}

static PqNode *new_pq_node(int id, float priority){
	PqNode *node = malloc(sizeof(PqNode));
	node->id = id;
	node->priority = priority;
	node->left = NULL;
	node->right = NULL;
	return node;
}

static void push_node(PqNode **head, PqNode *node){
	if (*head == NULL){
		*head = node;
		return;
	}

	if ((*head)->priority < node->priority){
		push_node(&(*head)->right, node);
	} else {
		push_node(&(*head)->left, node);
	}
}

void push_priority_queue(PriorityQueue *queue, int id, float priority) {
	PqNode *node = new_pq_node(id, priority);
	push_node(&queue->root, node);
	queue->size++;
}

void pop_priority_queue(PriorityQueue *queue, int *result_id, float *result_priority) {
	if (queue->root == NULL) {
		return;
	}

	PqNode *parent = NULL;
	PgNode *node = queue->root;
	while (node->right) {
		parent = node;
		node = node->right;
	}

	*result_id = node->id;
	*result_priority = node->priority;

	if (parent == NULL) {
		queue->root = node->left;
	} else {
		parent->right = node->left;
	}

	queue->size--;
}





