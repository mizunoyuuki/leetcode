void searchIsland(int** grid, int i, int i_max, int j, int j_max, int *count){
	if (i > i_max - 1 || j > j_max - 1) return;
	if (i < 0 || j < 0 ) return;
	if (grid[i][j] == 0) return;

	grid[i][j] = 0;
	(*count) += 1;

	searchIsland(grid, i+1, i_max, j, j_max, count);
	searchIsland(grid, i, i_max, j+1, j_max, count);
	searchIsland(grid, i-1, i_max, j, j_max, count);
	searchIsland(grid, i, i_max, j-1, j_max, count);

	return;
}

int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize){
	int max = 0;
	for (int i = 0; i < gridSize; i++){
		for (int j = 0; j < *gridColSize; j++){
			if (grid[i][j] == 0) continue;

			int count = 0;
			searchIsland(grid, i, gridSize, j, *gridColSize, &count);
			if (max < count) max = count;
		}
	}

	return max;
}
