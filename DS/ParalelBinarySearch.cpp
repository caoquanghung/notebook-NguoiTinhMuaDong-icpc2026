
    void solveQueries(int low, int high, vector<Event>& events, vector<Query>& queries) {
        if (low > high || queries.empty()) return; 
        int mid = (low + high) >> 1;
 
        vector<Event> left_events, right_events;
        vector<Query> left_queries, right_queries;
 
        int event_id = 0;
        for (int query_id = 0; query_id < queries.size(); ++query_id) {
            const Query& query = queries[query_id];
            while(event_id < events.size() && events[event_id].timeStamp < query.timeStamp) {
                const Event& e = events[event_id];
                ++event_id;
 
                if (e.val <= mid) {
                    FenwickTree::upd(e.position, e.delta);
                    left_events.push_back(e);
                }
                else {
                    right_events.push_back(e);
                }
            }
 
            int Count = FenwickTree::query(query.l, query.r);
            if (Count >= query.k) {
                answers[query.timeStamp] = mid;
                left_queries.push_back(queries[query_id]);
            }
            else {
                queries[query_id].k -= Count;
                right_queries.push_back(queries[query_id]);
            }
        }
 
        for (const Event& e : left_events) 
            FenwickTree::upd(e.position, -e.delta);
 

        solveQueries(low, mid - 1, left_events, left_queries);
        solveQueries(mid + 1, high, right_events, right_queries);
    }