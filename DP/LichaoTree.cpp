/**
 * Li Chao Tree Implementation
 * 
 * ⚠️  IMPORTANT: This implementation is optimized for MINIMUM queries! ⚠️
 * 
 * For MAXIMUM queries, you have two options:
 * 1. Negate all slopes and y-intercepts when adding lines, then negate query results
 * 2. Modify comparison operators in addLine and use maximize in getMin (see inline comments)
 * 
 * Features:
 * - Add lines dynamically: O(logn) per line
 * - Query minimum at any point: O(logn) per query
 * - Supports coordinate compression and large coordinate ranges
 * 
 * Usage:
 * Node* root = new Node();
 * addLine(root, Line(slope, intercept));
 * ll minValue = getMin(root, queryPoint);
 * 
 * Time Complexity: O(logn) per operation
 * Space Complexity: O(n log n) in worst case
 */

struct Line {
    ll slope, intercept;  // Represents line y = slope*x + intercept
    
    Line(ll _slope = 0, ll _intercept = oo) {
        slope = _slope, intercept = _intercept;
    }
 
    // Calculate y-value for given x
    ll getY(ll x) {
        return slope * x + intercept;
    }
};
 
struct Node {
    Line storedLine;      // Line stored at this node
    Node *leftChild, *rightChild;  // Pointers to left and right children
 
    Node(Line _line = Line()) {
        storedLine = _line;
        leftChild = rightChild = NULL;
    }
 
} *lichaoTrees[N];  // Array of Li Chao tree roots (for multiple trees)
 
// Add a new line to the Li Chao Tree
void addLine(Node *root, Line newLine, int leftBound = -LIM, int rightBound = +LIM) {
    // Base case: leaf node
    if (leftBound == rightBound) {
        // Keep the line that gives smaller value at this point (for minimum query)
        // For MAXIMUM: change > to < in the condition below
        if (root->storedLine.getY(leftBound) > newLine.getY(leftBound)) 
            swap(root->storedLine, newLine);
        return;
    }
 
    int mid = (leftBound + rightBound) >> 1;
    
    // Ensure storedLine has smaller slope (for minimum query optimization)
    // For MAXIMUM: change > to < in the condition below
    if (root->storedLine.slope > newLine.slope) 
        swap(root->storedLine, newLine);
    
    // Check which line is better at the midpoint
    // For MINIMUM: if stored line is worse at mid, go left; otherwise go right
    // For MAXIMUM: change < to > in the condition below
    if (root->storedLine.getY(mid) < newLine.getY(mid)) {
        // Current stored line is better, so newLine might be better on the left side
        if (!root->leftChild) {
            root->leftChild = new Node(newLine);
            return;
        }
        else addLine(root->leftChild, newLine, leftBound, mid);
    }
    else {
        // newLine is better at mid, so make it the stored line and recurse right
        swap(root->storedLine, newLine);
        if (!root->rightChild) {
            root->rightChild = new Node(newLine);
            return;
        }
        else addLine(root->rightChild, newLine, mid + 1, rightBound);
    }
}
 
// Query minimum value at position x
// For MAXIMUM queries: change function name to getMax and use maximize instead of minimize
ll getMin(Node *root, int x, int leftBound = -LIM, int rightBound = +LIM) {
    // Start with the value from the line stored at current node
    ll result = root->storedLine.getY(x);
    
    // Base case: leaf node
    if (leftBound == rightBound) return result;
    
    int mid = (leftBound + rightBound) >> 1;
    
    // Recursively check left subtree if x is in left half and left child exists
    if (x <= mid && root->leftChild) 
        minimize(result, getMin(root->leftChild, x, leftBound, mid));
        // For MAXIMUM: use maximize(result, getMax(root->leftChild, x, leftBound, mid));
    
    // Recursively check right subtree if x is in right half and right child exists
    if (x > mid && root->rightChild)  
        minimize(result, getMin(root->rightChild, x, mid + 1, rightBound));
        // For MAXIMUM: use maximize(result, getMax(root->rightChild, x, mid + 1, rightBound));
    
    return result;
}