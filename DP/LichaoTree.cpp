// Dynamic Li Chao tree for minimum, O(log LIM) per operation.
// Usage: Node *root=new Node(); addLine(root,{slope,intercept}); getMin(root,x).
// For maximum, negate lines/results or reverse comparisons.
struct Line {
  ll slope, intercept; // y = slope*x+intercept
  Line(ll _slope = 0, ll _intercept = oo) { slope = _slope, intercept = _intercept; }
  ll getY(ll x) { return slope * x + intercept; }
};
struct Node {
  Line storedLine;
  Node *leftChild, *rightChild;
  Node(Line _line = Line()) {
    storedLine = _line;
    leftChild = rightChild = NULL;
  }
} *lichaoTrees[N]; // Array of Li Chao tree roots (for multiple trees)
void addLine(Node *root, Line newLine, int leftBound = -LIM, int rightBound = +LIM) {
  if (leftBound == rightBound) {
    if (root->storedLine.getY(leftBound) > newLine.getY(leftBound)) swap(root->storedLine, newLine);
    return;
  }
  int mid = (leftBound + rightBound) >> 1;
  if (root->storedLine.slope > newLine.slope) swap(root->storedLine, newLine);
  if (root->storedLine.getY(mid) < newLine.getY(mid)) {
    if (!root->leftChild) {
      root->leftChild = new Node(newLine);
      return;
    } else addLine(root->leftChild, newLine, leftBound, mid);
  } else {
    swap(root->storedLine, newLine);
    if (!root->rightChild) {
      root->rightChild = new Node(newLine);
      return;
    } else addLine(root->rightChild, newLine, mid + 1, rightBound);
  }
}
ll getMin(Node *root, int x, int leftBound = -LIM, int rightBound = +LIM) {
  ll result = root->storedLine.getY(x);
  if (leftBound == rightBound) return result;
  int mid = (leftBound + rightBound) >> 1;
  if (x <= mid && root->leftChild) minimize(result, getMin(root->leftChild, x, leftBound, mid));
  if (x > mid && root->rightChild) minimize(result, getMin(root->rightChild, x, mid + 1, rightBound));
  return result;
}
