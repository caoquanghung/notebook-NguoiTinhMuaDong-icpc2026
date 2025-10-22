/**
 * Persistent Segment Tree for Comparing Very Large Numbers (~10^5 bits)
 * - Numbers stored as binary representation across bit positions [0, maxn]
 * - Each version represents different number, uses hashing for quick comparison
 * - Finds first differing bit from most significant position for comparison
 */
namespace PersistentSegmentTree {
    // Build initial empty tree with all bits set to 0
    node* build(int l, int r) {
        if (l == r) return new node(0);
        int mid = (l + r) / 2;
        node* left = build(l, mid), *right = build(mid + 1, r);
        return new node(sum(left->hashval, right->hashval), left, right); // Hash for quick diff detection
    }
 
    // Create new version with updated bit at position p (persistence core)
    node* update(node* root, int l, int r, int p, int val) {
        if (l == r) return new node(sum(root->hashval, val)); // val = ±Pow[i]
        int mid = (l + r) / 2;
        node* left = root->left, *right = root->right;
        if (p <= mid) left = update(left, l, mid, p, val);
        else right = update(right, mid + 1, r, p, val);
        return new node(sum(left->hashval, right->hashval), left, right);
    }
 
    // Check if bit at position x is set (traverse to leaf)
    bool getBit(node* root, int x) {
        node* cur = root;
        int l = 0, r = maxn;
        while(l != r) {
            int mid = (l + r) / 2;
            if (x <= mid) cur = cur->left, r = mid;
            else cur = cur->right, l = mid + 1;
        }
        return (cur->hashval != 0); // hashval != 0 means bit is set
    }
 
    // Add 2^bit to number (binary addition with carry propagation)
    node* addBit(node* root, int bit) {
        int i = bit;
        while(getBit(root, i) == 1) { // Handle carry: 1+1=0 with carry
            root = update(root, 0, maxn, i, mod - Pow[i]); // Set bit i to 0
            i++; // Carry to next position
        }
        root = update(root, 0, maxn, i, Pow[i]); // Set bit i to 1
        return root;
    }
 
    // Find first (most significant) differing bit position between two numbers
    int getFirstDiff(node* p, node* q, int l, int r) {
        if (l == r) return l;
        int mid = (l + r) / 2;
        if (p->right->hashval != q->right->hashval) // Check higher bits first
            return getFirstDiff(p->right, q->right, mid + 1, r);
        else return getFirstDiff(p->left, q->left, l, mid);
    }
 
    // Compare two very large numbers: returns true if p < q
    bool cmp(node* p, node *q) {
        if (!q) return true; // Edge case handling
        int bit = getFirstDiff(p, q, 0, maxn); // Find most significant differing bit
        return getBit(p, bit) < getBit(q, bit); // Compare bit values at that position
    }
};