/**
 * Deque Optimization for Dynamic Programming (Convex Hull Trick variant)
 * 
 * PROBLEM TYPE: dp[i] = min(dp[j] + cost(j,i)) for j < i
 * REQUIREMENT: cost(a,c) + cost(b,d) ≤ cost(a,d) + cost(b,c) ∀ a≤b≤c≤d (Quadrangle Inequality)
 * 
 * KEY INSIGHT: If cost satisfies QI, optimal transition points have monotonic property:
 * opt[i] ≤ opt[i+1] (optimal j for position i is ≤ optimal j for position i+1)
 * 
 * ALGORITHM: Maintain deque of candidate transitions with their "useful ranges"
 * - Each item stores [l,r,opt]: transition 'opt' is best for range [l,r]
 * - Process positions left-to-right, maintain that ranges don't overlap
 * - Binary search to find where new transition becomes better
 * 
 * COMPLEXITY: O(n log n) vs O(n²) naive → crucial for n ≤ 10⁶
 */

ll cost(int l, int r) { // simulate a cost function
    ++l;
    int mid = (l + r) >> 1;
    return 1LL * a[mid] * (mid - l + 1) - (pre[mid] - pre[l - 1]) 
            + pre[r] - pre[mid - 1] - 1LL * a[mid] * (r - mid + 1);
}

struct Item {
    int l, r, opt; // Range [l,r] where transition 'opt' is optimal
    Item(int _l = 0, int _r = 0, int _opt = 0) {
        l = _l, r = _r, opt = _opt;
    }
}; deque<Item> dq; // Maintains non-overlapping ranges of optimal transitions

ll dp[N];

void solve(){   
    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;  
    dq.eb(1, n, 0); // Initially, transition 0 is optimal for range [1,n]
    REP(i, 1, n) {
        while(!dq.empty() && dq.front().r < i) // Remove expired ranges
            dq.pop_front();

        int opt_i = dq.front().opt; // Get optimal transition for position i
        dp[i] = dp[opt_i] + cost(opt_i, i) + k;

        dq.front().l = i + 1; // Current range now starts from i+1        
        if (dq.front().l > dq.front().r) dq.pop_front(); // Remove empty range

        while(!dq.empty()) { // Remove transitions that are now suboptimal
            auto [l, r, opt] = dq.back();
            if (dp[i] + cost(i, l) < dp[opt] + cost(opt, l)) 
                dq.pop_back(); // Transition i is better than opt at position l
            else break;
        }   
        
        if (dq.empty()) { // New transition i dominates everything
            dq.eb(i + 1, n, i);
            continue;
        }
        else { // Find where transition i becomes better than current best
            auto &[l, r, opt] = dq.back();
            int lo = l, hi = r, p = r + 1;
            while(lo <= hi) { // Binary search for crossover point
                int mid = (lo + hi) >> 1;
                if (dp[i] + cost(i, mid) < dp[opt] + cost(opt, mid))
                    p = mid, hi = mid - 1;
                else lo = mid + 1;
            }

            if (p == n + 1) continue; // Transition i never becomes better
            r = p - 1; // Shrink current range
            dq.eb(p, n, i); // Add new range where i is optimal
        }
    }   
    cout << dp[n] << ln;
}