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
int ladderLength(char *beginWord, char* endWord, char** wordList, int wordListSize){
}
