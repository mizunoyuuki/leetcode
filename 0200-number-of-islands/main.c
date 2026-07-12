void searchLands(char **grid, int i, int i_max, int j, int j_max){
	if (i > i_max - 1 || j > j_max - 1) return;
	if (i < 0 || j < 0) return;
	if (grid[i][j] == '0') return;

	grid[i][j] = '0';

	searchLands(grid, i+1, i_max, j, j_max);
	searchLands(grid, i, i_max, j+1, j_max);
	searchLands(grid, i-1, i_max, j, j_max);
	searchLands(grid, i, i_max, j-1, j_max);

	return;
}

int numIslands(char **grid, int gridSize, int* gridColSize){
	int count = 0;

	for (int i = 0; i < gridSize; i++){
		for (int j = 0; j < *gridColSize; j++){
			if (grid[i][j] != '1') continue;

			count++;
			searchLands(grid, i, gridSize, j, *gridColSize);
		}
	}

	return count;
}
