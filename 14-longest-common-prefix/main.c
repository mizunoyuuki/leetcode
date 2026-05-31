/* longest common prefix 
 * 最長共通接頭辞
 *
 * 文字列の配列の中から、最も長い共通の接頭辞を探す
 *
 * 入力
 * strs = ["flower", "flow", "flight"];
 * "fl"
 *
 * 入力
 * strs = ["dog", "racecar", "car"]
 * ""
 *
 * */

char *longestCommonPrefix(char **strs, int strsSize) {
	for (int j = 0; strs[0][j] != '\0'; j++) {
		for (int i = 1; i < strsSize; i++) {
			if (strs[i][j] == '\0' || strs[0][j] != strs[i][j]) {
				strs[0][j] = '\0';
				return strs[0];
			}
		}
	}
	return strs[0];
}
