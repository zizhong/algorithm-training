// http://poj.org/problem?id=2887
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#define __builtin_sprintf

using namespace std;


struct BlockListNode {
  string s;
  BlockListNode *next;
  BlockListNode(): next(NULL){}
};
const int BLOCK_SIZE = 1024;

struct BlockList {
  BlockListNode *p;
  BlockList(const string &s) {
    p = NULL;
    for (int i = (int) s.size() - 1; i >= 0; i -= BLOCK_SIZE) {
      BlockListNode *b = new BlockListNode();
      int st = max(0, i - BLOCK_SIZE + 1);
      int ed = i;
      b->s = s.substr(st, ed - st + 1);
      b->next = p;
      p = b;
    }
  }
  char query(int index) {
    int sz = 0;
    for (BlockListNode *ptr = p; ptr; ptr = ptr->next) {
      if (sz + ptr->s.size() >= index) {
        return ptr->s[index - sz - 1];
      }
      sz += ptr->s.size();
    }
    return 0;
  }

  void insert_before(char c, int index) {
    int sz = 0;
    for (BlockListNode *ptr = p; ptr; ptr = ptr->next) {
      if (sz + ptr->s.size() >= index) {
        ptr->s.insert(index - sz - 1, 1, c);
        check_split(ptr);
        return;
      }
      sz += ptr->s.size();
      if (ptr->next == NULL) {
        ptr->s.push_back(c);
        check_split(ptr);
      }
    }

  }
  void check_split(BlockListNode *ptr) {
    if (ptr->s.size() == 2 * BLOCK_SIZE) {
      BlockListNode* nb = new BlockListNode();
      nb->s = ptr->s.substr(BLOCK_SIZE);
      ptr->s = ptr->s.substr(0, BLOCK_SIZE);
      nb->next = ptr->next;
      ptr->next = nb;
    }
  }

  void del(int index) {
    int sz = 0;
    for (BlockListNode *ptr = p; ptr; ptr = ptr->next) {
      if (sz + ptr->s.size() >= index) {
        ptr->s.erase(index - sz - 1);
        return;
      }
      sz += ptr->s.size();
    }
  }
};

void solve(int ncase) {
  string s;
  cin >> s;
  BlockList bl(s);

  int nq;
  cin >> nq;
  for (int q = 0; q < nq; q++) {
    string t;
    cin >> t;
    if (t[0] == 'Q') {
      int index;
      cin >> index;
      cout << bl.query(index) << endl;
    } else if (t[0] == 'I') {
      string ch;
      int index;
      cin >> ch >> index;
      bl.insert_before(ch[0], index);
    } else if (t[0] == 'D') {
      int index;
      cin >> index;
      bl.del(index);
    }
  }
}

void solve_all_cases() {
  int T = 1;
  //pre_calc();
  // scanf("%d", &T);
  //cin >> T;
  //debug(T);
  //T = ri();
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

#ifdef _zzz_
  //ios_base::sync_with_stdio(true);
  freopen("C:\\Users\\grain\\CLionProjects\\Contest\\input\\in.txt", "r", stdin);
  //freopen("C:\\Users\\grain\\Downloads\\punched_cards_sample_ts1_input.txt", "r", stdin);
  //auto x = freopen("C:\\Users\\grain\\CLionProjects\\Contest\\output\\out.txt", "w", stderr);
  //cerr << x << " " << errno << endl;
  auto t1 = std::chrono::high_resolution_clock::now();
  auto start_time = clock();
#endif

  solve_all_cases();
  //test();
#ifdef _zzz_
  // cerr << (std::chrono::high_resolution_clock::now() - t1).count() << endl;
  cerr << (clock() - start_time) * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
#endif
}
