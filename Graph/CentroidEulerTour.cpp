/* Centroid Decomposition using Euler Tour + Segment Tree
S = sum of all vertices' weight. Centroid x: sum[x] * 2 > S (subtree ≥ S/2 + 1)
Find position p on euler tour: sum(1,p) ≥ S/2+1. Let v = vertex at tin[v]=p
Centroid is ancestor of v (proof: tin[centroid] ≤ p ≤ tout[centroid])
*/

int findCentroid() {
    ll totalSum = ST.it[1].sum; // Total weight sum
    int p = ST.Find(s1 / 2 + 1); // Find position with prefix sum ≥ S/2+1
    p = label[p]; // Convert euler tour position to vertex
    if (getsubtree(p) * 2LL > s1) return p; // p is already centroid
    REPD(i, 18, 0) if (par[p][i] != 0) { // Binary lifting to find centroid ancestor
        if (getsubtree(par[p][i]) * 2LL <= s1) // Jump if ancestor subtree too small
            p = par[p][i];
    }
    if (p == 1) return p; // Root case
    return par[p][0]; // Return parent (the actual centroid)
}