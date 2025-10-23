/**
 * Convex Hull Trick (CHT) Implementation
 * Used for optimizing DP problems where we need to find maximum/minimum
 * of linear functions efficiently.
 * 
 * This implementation finds MAXIMUM values (convex hull).
 * For minimum, change comparison operators and maximize to minimize.
 */

struct Line {
    ll a, b;  // Represents line y = a*x + b
    
    Line(ll _a = 0, ll _b = 0) {
        a = _a, b = _b;
    }
    
    // Calculate y-value for given x
    ll gety(ll x) {
        return a * x + b;
    }
 
    // Find x-coordinate where this line intersects with another line
    db intersect(const Line &other) const {
        return 1.0 * db(b - other.b) / db(other.a - a);  
    }
 
    // Comparison operator for sorting lines by slope
    bool operator < (const Line &other) const {
       // For getMax (convex hull): sort by increasing slope (a < other.a)
       // For getMin (concave hull): sort by decreasing slope (a > other.a)
        return a < other.a;
    }
};

struct ConvexHullTrick{
    int pt = 0;           // Pointer for current optimal line in query
    vector<Line> dq;      // Deque to store lines forming the convex hull
 
    ConvexHullTrick() {
        pt = 0;
        dq.clear();
    }
 
    // Add a new line to the convex hull
    void addLine(Line newLine) {
        // IMPORTANT: Lines must be added in sorted order by slope (a value)
        
        // If new line has same slope as last line, keep the better one
        if (!dq.empty() && newLine.a == dq.back().a) {
            // For maximum: keep line with larger b (higher y-intercept)
            // For minimum: use minimize instead of maximize
            maximize(newLine.b, dq.back().b);
            dq.pop_back();
        } 
        
        // Remove lines that become redundant after adding the new line
        // A line becomes redundant if its intersection with the new line
        // comes before its intersection with the previous line
        while(dq.size() >= 2 && newLine.intersect(dq[SZ(dq) - 2]) <= dq.back().intersect(dq[SZ(dq) - 2]))
            dq.pop_back();
 
        // Add the new line to the hull
        dq.push_back(newLine);
    }
 
    // Query maximum value at x
    ll getMAX(ll x) {
        // IMPORTANT: Queries must be made in non-decreasing order of x
        if (dq.empty()) return -1e18;
        
        // Move pointer to the right while the next line gives better value
        // This works because x values are queried in increasing order
        while(pt + 1 < dq.size() && dq[pt + 1].gety(x) >= dq[pt].gety(x)) 
            ++pt;
            
        return dq[pt].gety(x);
    }
};