// CHT maximum: add slopes and query x in non-decreasing order, O(1) amortized.
// For minimum, reverse comparisons/maximize.
struct Line {
  ll a, b; // y = ax+b
  Line(ll _a = 0, ll _b = 0) { a = _a, b = _b; }
  ll gety(ll x) { return a * x + b; }
  db intersect(const Line &other) const { return 1.0 * db(b - other.b) / db(other.a - a); }
  bool operator<(const Line &other) const { return a < other.a; }
};
struct ConvexHullTrick {
  int pt = 0;
  vector<Line> dq;
  ConvexHullTrick() {
    pt = 0;
    dq.clear();
  }
  void addLine(Line newLine) {
    if (!dq.empty() && newLine.a == dq.back().a) {
      maximize(newLine.b, dq.back().b);
      dq.pop_back();
    }
    while (dq.size() >= 2 && newLine.intersect(dq[SZ(dq) - 2]) <= dq.back().intersect(dq[SZ(dq) - 2])) dq.pop_back();
    dq.push_back(newLine);
  }
  ll getMAX(ll x) {
    if (dq.empty()) return -1e18;
    while (pt + 1 < dq.size() && dq[pt + 1].gety(x) >= dq[pt].gety(x)) ++pt;
    return dq[pt].gety(x);
  }
};
