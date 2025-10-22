// note: Mo with update queries
// time complexity: O((n + q) * n^(2/3) * log n) with set
// space complexity: O(n + q)
// 1. Block size: B = n^(2/3)
// 2. Sort queries by (l / B, r / B, t)
// 3. Maintain current [L,R] and time T
// 4. Move L, R, T to match each query, updating answer accordingly
// 5. Use a data structure (like set) to maintain current distinct elements in [L,R]
// 6. Handle updates by applying or reverting them as T changes
// 7. Carefully manage adding/removing elements and applying/reverting updates
// 8. Answer each query after adjusting L, R, T
// 9. Output answers in original query order

// First set up L = 1, R = 0, T = 0 (empty range, no updates applied)
// Then for each query (l, r, t):
// - While T < t: apply next update, increment T
// - While T > t: revert last update, decrement T
// - While R < r: add element at R+1, increment R
// - While R > r: remove element at R, decrement R
// - While L < l: remove element at L, increment L
// - While L > l: add element at L-1, decrement L
// After adjusting L, R, T, the current data structure state reflects the array
// with all updates up to time t applied, and the range [l, r].
// The answer for the query can then be computed from this state. 