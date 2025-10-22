  // Build 2D prefix sum
  
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      triangular[i][j] = arr[i][j] + triangular[i-1][j] + triangular[i][j-1] - triangular[i-1][j-1];
      prefix[i][j] = arr[i][j] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];
    }
  }

  auto getTriangularSum = [&](int x, int y, int d) { // Get sum of dxd submatrix with bottom-right corner at (x,y)
    int x1 = x - d + 1, y1 = y - d + 1;
    // if out of the grid, calculate sum in grid
    if (x1 < 1) x1 = 1;
    if (y1 < 1) y1 = 1;
    // Inclusion-Exclusion principle for submatrix sum
    return triangular[x][y] - triangular[x1-1][y] - triangular[x][y1-1] + triangular[x1-1][y1-1];
  };