// Block-cut tree, O(N+M). Original/articulation vertices are round nodes;
// each biconnected component becomes a square node. Result has at most 2N nodes.
stack<int> st; // Stack to track current path for biconnected component detection
// Tarjan's algorithm to find biconnected components and build block-cut tree
void dfs(int u) {
  st.push(u);                  // Add current vertex to path stack
  num[u] = low[u] = ++timeDfs; // Initialize discovery and low-link values
  for (int v : adj[u]) {
    if (num[v]) minimize(low[u], num[v]); // Back edge: update low-link
    else {
      dfs(v);                   // Tree edge: recurse on child
      minimize(low[u], low[v]); // Update low-link from child
      // Found biconnected component: low[v] == num[u] means u is articulation point
      if (low[v] == num[u]) {
        ++numNode;               // Create new block node (square node)
        add_edge(u, numNode, 1); // Connect articulation point to block
        // Pop all vertices in this biconnected component
        int x = -1;
        do {
          x = st.top();
          st.pop();
          comp[x] = numNode;       // Mark vertex as belonging to this block
          add_edge(numNode, x, 0); // Connect block to vertex
        } while (x != v);
      }
    }
  }
}
