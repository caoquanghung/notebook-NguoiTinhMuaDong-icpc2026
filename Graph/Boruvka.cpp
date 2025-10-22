/*
How It Works:
Start with each vertex as its own component
Repeat until all vertices are in one component:
For each component, find the minimum weight edge connecting it to any other component
Add all these minimum edges to the MST
Merge the connected components

Why It's Useful:
Works well for dense graphs where you want parallelization
Naturally divides work into independent subtasks per component
*/
DSU dsu(n);
long long mstWeight = 0;
int edgesUsed = 0;
    
// Keep merging components until we have one component
while (edgesUsed < n - 1) {
  // For each component, find the minimum weight edge
  // that connects it to another component
  vector<int> minEdge(n, -1);
        
    for (int i = 0; i < m; i++) {
        int w = edges[i].weight;
        
        int compU = dsu.find(edges[i].u);
        int compV = dsu.find(edges[i].v);
        
        // If edge connects different components
        if (compU != compV) { // now checking components U and V
            if (minEdge[compU] == -1 || edges[minEdge[compU]].weight > edges[i].w) {
                minEdge[compU] = i;
            }
            if (minEdge[compV] == -1 || edges[minEdge[compV]].weight > edges[i].w) {
                minEdge[compV] = i;
            }
        }
    }
    /// In other cases, we can traverse all vertices and find the minimum edge for each component
    /// This is more efficient when the number of edges is much larger than the number of vertices 
    
    // Add all minimum edges to MST
    for (int i = 0; i < n; i++) {
        if (minEdge[i] != -1) {
            int u = edges[minEdge[i]].u, v = edges[minEdge[i]].v, w = edges[minEdge[i]].weight;
            
            if (dsu.unite(u, v)) {
                mstWeight += w;
                edgesUsed++;
            }
        }
    }
  }