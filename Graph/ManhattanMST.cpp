struct Point {
  int x, y;
  Point() { x = y = 0; }
  Point(int _x, int _y) {
    x = _x;
    y = _y;
  }
  bool operator<(const Point &other) const { return (x + y) < (other.x + other.y); }
};
vector<tuple<long long, int, int>> calcMahattanEdge(vector<Point> &pts) {
  vector<tuple<long long, int, int>> edges;
  vector<int> ind;
  for (int i = 0; i < (int)pts.size(); i++) ind.push_back(i);
  for (int rot = 0; rot < 4; rot++) {
    sort(ind.begin(), ind.end(), [&](int u, int v) { return pts[u] < pts[v]; });
    map<long long, int, greater<long long>> active;
    for (int i : ind) {
      for (auto it = active.lower_bound(pts[i].x); it != active.end(); active.erase(it++)) {
        int j = it->second;
        if (pts[i].x - pts[i].y > pts[j].x - pts[j].y) break;
        edges.push_back({(pts[i].x - pts[j].x + pts[i].y - pts[j].y), i, j});
      }
      active[pts[i].x] = i;
    }
    for (int i = 0; i < (int)pts.size(); i++) {
      if (rot & 1) pts[i].x *= -1;
      else swap(pts[i].x, pts[i].y);
    }
  }
  return edges;
}
