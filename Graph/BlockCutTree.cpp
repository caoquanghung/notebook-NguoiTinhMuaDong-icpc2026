
/**
 * Block-Cut Tree (Bridge-Block Tree / Block Graph)
 * 
 * DEFINITION:
 * A block-cut tree is an auxiliary tree structure built from a connected graph
 * that helps solve queries involving articulation points and biconnected components.
 * 
 * CONSTRUCTION:
 * 1. Find all biconnected components (blocks) in the original graph
 * 2. Create two types of nodes in the block-cut tree:
 *    - SQUARE nodes: represent biconnected components (blocks)
 *    - ROUND nodes: represent articulation points (cut vertices)
 * 3. Connect each articulation point to all blocks it belongs to
 * 
 * PROPERTIES:
 * - The block-cut tree is always a tree (no cycles)
 * - Non-articulation points belong to exactly one block
 * - Articulation points appear as separate nodes AND belong to multiple blocks
 * - Tree has at most 2N nodes (N original + N blocks in worst case)
 * 
 * APPLICATIONS:
 * - Path queries avoiding articulation points
 * - Distance queries in graphs with bridges/cut vertices
 * - Finding alternative paths when certain vertices are removed
 * - LCA-based queries on the block structure
 * 
 * TIME COMPLEXITY: O(N + M) using Tarjan's algorithm
 */

stack<int> st; // Stack to track current path for biconnected component detection

// Tarjan's algorithm to find biconnected components and build block-cut tree
void dfs(int u) {
    st.push(u); // Add current vertex to path stack
    num[u] = low[u] = ++timeDfs; // Initialize discovery and low-link values
    
    for (int v : adj[u]) {
        if (num[v]) minimize(low[u], num[v]); // Back edge: update low-link
        else {
            dfs(v); // Tree edge: recurse on child
            minimize(low[u], low[v]); // Update low-link from child
            
            // Found biconnected component: low[v] == num[u] means u is articulation point
            if (low[v] == num[u]) {
                ++numNode; // Create new block node (square node)
                add_edge(u, numNode, 1); // Connect articulation point to block
                
                // Pop all vertices in this biconnected component
                int x = -1;
                do {
                    x = st.top(); st.pop();
                    comp[x] = numNode; // Mark vertex as belonging to this block
                    add_edge(numNode, x, 0); // Connect block to vertex
                } while(x != v);    
            }   
        }
    }
}