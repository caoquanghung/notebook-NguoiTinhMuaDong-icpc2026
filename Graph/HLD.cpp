int depth[N];
int headChain[N], par[N], chain[N], numChain = 1;
int sz[N];
int pos, posArr[N];
vector<int> adj[N];
// HLD with posArr[u] is position of parent edge of u
void dfs(int u, int p) {
  sz[u] = 1;
  for (int v : adj[u])
    if (v != p) {
      depth[v] = depth[u] + 1;
      par[v] = u;
      dfs(v, u);
      sz[u] += sz[v];
    }
}
void hld(int u, int p) {
  if (!headChain[numChain]) { headChain[numChain] = u; }
  chain[u] = numChain;
  posArr[u] = ++pos;
  int nxt = -1;
  for (int v : adj[u])
    if (v != p) {
      if (nxt == -1 || sz[nxt] < sz[v]) { nxt = v; }
    }
  if (nxt != -1) hld(nxt, u);
  for (int v : adj[u])
    if (v != p && v != nxt) {
      ++numChain;
      hld(v, u);
    }
}
int query(int u, int v) {
  int res = 0;
  while (chain[u] != chain[v]) {
    if (chain[u] < chain[v]) swap(u, v);
    res = max(res, getMax(posArr[headChain[chain[u]]], posArr[u] + 1));
    u = par[headChain[chain[u]]];
  }
  if (posArr[u] > posArr[v]) swap(u, v);
  res = max(res, getMax(posArr[u], posArr[v] + 1));
  return res;
}
