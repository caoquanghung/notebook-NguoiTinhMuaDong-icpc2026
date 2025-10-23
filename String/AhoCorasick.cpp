/*
    Aho-Corasick string matching algorithm with exit links and occurrence counting
    Uses a tree structure to efficiently count occurrences of patterns
    in a given text after multiple updates.

    nxt[c]: transition for character c.
    First nxt is the trie transition. After aho build, it becomes the automaton transition.
    suffixLink: longest proper suffix of the current node that is also a prefix in the trie
    exitLink: longest suffix that is an end of some inserted string (for counting occurrences)
*/
struct AhoCorasick{
private:
  struct TrieNode {
    int nxt[26];
    int exitLink;
    int suffixLink;
    int cnt;
    
    TrieNode() : exitLink(-1), suffixLink(-1), cnt(0) {
      fill(nxt, nxt + 26, -1);
    }
  };
 
  vector<TrieNode> trie;
  Tree& tree; // This is the exit tree for counting occurrences
  
public:
  AhoCorasick(Tree& _tree) : tree(_tree) {
    trie.push_back(TrieNode());
  }
 
  vector<int> insert_string(const string& s) {
    int p = 0;
    vector<int> ans = {p};
    for (char c : s) {
      c -= 'a';
      if (trie[p].nxt[c] == -1) {
        trie[p].nxt[c] = trie.size();
        trie.push_back(TrieNode());
      }
      p = trie[p].nxt[c];
      ans.push_back(p);
    }  
    ++trie[p].cnt;
    return ans;
  }
 
  void buildAho() {
    queue<int> q;
    q.push(0);
    while(!q.empty()) {
      int v = q.front(); q.pop();
      int sfLink = trie[v].suffixLink;
      if (v != 0) {
        trie[v].exitLink = (trie[sfLink].cnt > 0) ? sfLink : trie[sfLink].exitLink;
        if (trie[v].cnt > 0) {
          // build exit tree
          tree.addEdge(trie[v].exitLink == -1 ? 0 : trie[v].exitLink, v); 
        }
      }
 
      FOR(c, 26) {
        int &_nxt = trie[v].nxt[c];
        int nxtsf = (v == 0) ? 0 : trie[sfLink].nxt[c];
        if (_nxt == -1) { 
          _nxt = nxtsf;
        }
        else {  
          trie[_nxt].suffixLink = nxtsf;
          q.push(_nxt);
        }
      } 
    }
 
    tree.initDfs(0);
  }
 
  void update(int node) {
    node = (trie[node].cnt > 0) ? node : trie[node].exitLink;
    if (node > 0) tree.updateToRoot(node, +1);
  }
 
  int getApp(int node) {
    return tree.getSubTree(node);
  }
 
} Aho(globalTree);