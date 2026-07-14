// 文字列問題に見せかけたグラフ問題
// Word Ladderの表面は、「一文字づつ変えて、hit -> cogに到達する最短手数」ですが、本質は重み無しグラフの最短経路問題
//
// グラフとして考え直すと、
// 頂点(node) 各単語(beginWord, wordList内の全ての単語)
// 辺(edge) 二つの単語が「ちょうど一文字だけ違う」時、その間に辺をはる
//
// 辺に重みがないグラフの最短経路 = 幅優先探索(BFS)
//
// なぜBFSかというと、BFSは視点から「距離1の頂点全て => 距離2の頂点全て =>」と波紋のように広がるため、最初にヒットしたendWordへの距離がそのまま最短距離になる。
//
// 双方向BFSがある。始点と終点の両方から同時に探索し、出会ったら終了。






//
// Example 1:
//
// Input: beginWord = "hit", endWord = "cog", 
// wordList = ["hot","dot","dog","lot","log","cog"]
//
// Output: 5
// Explanation: One shortest transformation sequence is 
// "hit" -> "hot" -> "dot" -> "dog" -> "cog", 
// which is 5 words long.


# include <string.h>
# include <stdlib.h>
# include <stdbool.h>

// まず小さい部品から「ちょうど1文字だけ」違うなら true
static bool isOneDiff(const char *a, const char *b){
	int diff = 0;
	for (int i = 0; a[i] != '\0'; i++){
		if (a[i] != b[i]){
			diff++;
			if (diff > 1) return false;
		}
	}

	return diff == 1;
}

// endWordがリストにあるか調べる
int ladderLength(char *beginWord, char *endWord, char **wordList, int wordListSize) {
	int endIndex = -1;
	for (int i = 0; i < wordListSize; i++){
		if (strcmp(wordList[i], endWord) == 0){
			endIndex = i;
			break;
		}
	}

	return (endIndex == -1) return 0; // ゴールが存在しない
					  //
	bool *visited = calloc(wordListSize, sizeof(bool)); // 全部falseで初期化
	int *queue = malloc(wordListSize * sizeof(int));    // 単語の添え字を入れる
	int *dist = malloc(wordListSize * sizeof(int));     // その単語までの手数
	int head = 0, tail = 0;

	// queue[tail++] = x;　で入れる(enqueue)
	// queue[head++]で取り出す     (dequeue)
	// head == tailになったら空


	// スタート地点をキューに入れる
	for (int i = 0; i < wordListSize; i++){
		if (isOneDiff(beginWord, wordList[i])) {
			visited[i] = true;
			dist[i] = 2;
			queue[tail++] = i;
		}
	}

	int answer = 0;
	while (head < tail){
		int cur = queue[head++];
		if (cur == endIndex) {
			answer = dist[cur];
			break;
		}

		for(int i = 0; i < wordListSize; i++){
			if (!visited[i] && isOneDiff(wordList[cur], wordList[i])) {
				visited[i] = true;
				dist[i] = dist[cur] + 1; // 今より一手多い
				queue[tail++] = i;
			}
		}
	}

	free(visited);
	free(queue);
	free(dist);

	return answer; // 届かなければ0のまま
}
