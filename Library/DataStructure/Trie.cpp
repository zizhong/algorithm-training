struct TrieNode {
    static const int N = 26;
    TrieNode* next[N];
    bool is_end = false;
    TrieNode() {
        fill(next, next + N, nullptr);
        is_end = false;
    }
    int char2index(const char c) {
        return c - 'a';
    }
    TrieNode*& getNext(const char c) {
        return next[char2index(c)];
    }
    ~TrieNode() {
        for(int i = 0; i < N; i++) delete next[i];
    }
};
struct Trie {
    
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }
    ~Trie() {
        delete root;
    }

    void insert(const string& str) {
        auto p = root;
        for(char c : str) {
            auto& nextp = p->getNext(c);
            if (nullptr == nextp) {
                nextp = new TrieNode();
            }
            p = nextp;
        }
        p->is_end = true;
    }
};
