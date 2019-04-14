#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <deque>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <ctime>
#include <queue>
#include <stack>
#include<iomanip>
#include <sstream>
#include <cmath>
//#include "utils/haha.h"
//#include "utils/max_flow.h"
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<string, int> PSI;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;
typedef pair<double, double> PDD;
typedef pair<ll, PII> PLP;
#define CLS(x, v) (memset((x), (v), sizeof((x))))
const double pi = acos(-1);
const int mod = 1000000007;
const int inf = 0x3fffffff;

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator() (const pair<T1, T2>& p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

struct Trie {
    static const int MAX_STR_LEN = 50;
    static const int MAX_STR_COUNT = 1000;
    static const int MAXNODE = MAX_STR_LEN * MAX_STR_COUNT * 26 + 10;
    struct TrieNode {
        static const int N = 26;
        TrieNode* next[N];
        int value;
        void init() {
            fill(next, next + N, nullptr);
            value = 0;
        }
        int char2index(const char c) {
            return c - 'A';
        }
        TrieNode*& getNext(const char c) {
            return next[char2index(c)];
        }
        int findPair() {
            int child_pair = 0;
            for(auto child : next) {
                if (!child) continue;
                child_pair += child->findPair();
            }
            return child_pair + ((value - 2 * child_pair) >= 2);
        }
    };
    TrieNode* PRE_ALLOC;
    int pre_alloc_index = 0;


    TrieNode* root;

    TrieNode* alloc() {
        PRE_ALLOC[pre_alloc_index].init();
        return &PRE_ALLOC[pre_alloc_index++];
    }
    Trie() {
        init();
    }
    ~Trie() {
        delete[] PRE_ALLOC;
    }
    void init() {
        pre_alloc_index = 0;
        PRE_ALLOC = new TrieNode[MAXNODE];
        root = alloc();
    }

    void insert(const string& str) {
        auto p = root;
        for(char c : str) {
            p->value++;
            auto& nextp = p->getNext(c);
            if (nullptr == nextp) {
                nextp = alloc();
            }
            p = nextp;
        }
        p->value++;
    }

    int findPair() {
        int ret = 0;
        for(auto n : root->next) {
            ret += n ? n->findPair() : 0;
        }
        return ret;
    }
};
void solve(int ncase) {
  int n;
  cin >> n;
  Trie trie;
  for(int i = 0; i < n; i++) {
    string s;
    cin >> s;
    reverse(s.begin(), s.end());
    trie.insert(s);
  }
  cout << "Case #" << ncase << ": " << trie.findPair() * 2 << endl;
}

int main() {
    //ios::sync_with_stdio(false);
    //cout << std::fixed;
    //cout << setprecision(9);
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    //precalc();
    int T = 1;
    //scanf("%d", &T);
    cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
