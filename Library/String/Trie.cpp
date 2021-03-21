struct TrieNode {
  static const int N = 26;
  TrieNode *next[N];
  bool is_end = false;
  TrieNode() {
    init();
  }
  void init() {
    fill(next, next + N, nullptr);
    is_end = false;
  }
  int char2index(const char c) {
    return c - 'a';
  }
  TrieNode *&getNext(const char c) {
    return next[char2index(c)];
  }
  ~TrieNode() {
  }
};
TrieNode node[(int) 1e6];
int node_idx;

struct Trie {

  TrieNode *root;
  Trie() {
    node_idx = 0;
    root = alloc();
  }
  TrieNode *alloc() {
    node[node_idx].clear();
    return &node[node_idx++];
  }

  void insert(const string &str) {
    auto p = root;
    for (char c : str) {
      auto &nextp = p->getNext(c);
      if (nullptr == nextp) {
        nextp = new TrieNode();
      }
      p = nextp;
    }
    p->is_end = true;
  }
};
