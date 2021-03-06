/*
* Greedy + SegTree to solve reverse pair
* https://codeforces.com/gym/304511/problem/D
* Calculate at least how many swaps needed to get a palindrome.
*    for each position, use the charactor with the least swaps. The swap number can be calculated by a SegTree.
*/
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <deque>
#include <set>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <ctime>
#include <queue>
#include <stack>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <fstream>
#include <bitset>
#include <complex>
#include <numeric>
//#include "utils/haha.h"
//#include "utils/max_flow.h"
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<string, int> PSI;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<int, ll> PIL;
typedef pair<ll, ll> PLL;
typedef pair<double, double> PDD;
typedef pair<ll, PII> PLP;
#define CLS(x, v) (memset((x), (v), sizeof((x))))

template<class TH>
void _dbg(const char *sdbg, TH h) { cerr << sdbg << '=' << h << endl; }
template<class TH, class... TA>
void _dbg(const char *sdbg, TH h, TA... a) {
  while (*sdbg != ',')cerr << *sdbg++;
  cerr << '=' << h << ',';
  _dbg(sdbg + 1, a...);
}

template<class T>
ostream &operator<<(ostream &os, vector<T> V) {
  os << "[";
  for (auto vv : V) os << vv << ",";
  return os << "]";
}
template<class L, class R>
ostream &operator<<(ostream &os, pair<L, R> P) {
  return os << "(" << P.first << "," << P.second << ")";
}

#ifdef _zzz_
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class T>
using max_heap = priority_queue<T>;
//const int N = 1e6 + 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

template<unsigned MOD_>
struct ModInt {
  static constexpr unsigned MOD = MOD_;
  unsigned x;
  void undef() { x = (unsigned) -1; }
  bool isnan() const { return x == (unsigned) -1; }
  inline int geti() const { return (int) x; }
  ModInt() { x = 0; }
  ModInt(const ModInt &y) { x = y.x; }
  ModInt(int y) {
    if (y < 0 || (int) MOD <= y) y %= (int) MOD;
    if (y < 0) y += MOD;
    x = y;
  }
  ModInt(unsigned y) { if (MOD <= y) x = y % MOD; else x = y; }
  ModInt(long long y) {
    if (y < 0 || MOD <= y) y %= MOD;
    if (y < 0) y += MOD;
    x = y;
  }
  ModInt(unsigned long long y) { if (MOD <= y) x = y % MOD; else x = y; }
  ModInt &operator+=(const ModInt y) {
    if ((x += y.x) >= MOD) x -= MOD;
    return *this;
  }
  ModInt &operator-=(const ModInt y) {
    if ((x -= y.x) & (1u << 31)) x += MOD;
    return *this;
  }
  ModInt &operator*=(const ModInt y) {
    x = (unsigned long long) x * y.x % MOD;
    return *this;
  }
  ModInt &operator/=(const ModInt y) {
    x = (unsigned long long) x * y.inv().x % MOD;
    return *this;
  }
  ModInt operator-() const { return (x ? MOD - x : 0); }

  ModInt inv() const { return pow(MOD - 2); }
  ModInt pow(long long y) const {
    ModInt b = *this, r = 1;
    if (y < 0) {
      b = b.inv();
      y = -y;
    }
    for (; y; y >>= 1) {
      if (y & 1) r *= b;
      b *= b;
    }
    return r;
  }

  friend ModInt operator+(ModInt x, const ModInt y) { return x += y; }
  friend ModInt operator-(ModInt x, const ModInt y) { return x -= y; }
  friend ModInt operator*(ModInt x, const ModInt y) { return x *= y; }
  friend ModInt operator/(ModInt x, const ModInt y) { return x *= y.inv(); }
  friend bool operator<(const ModInt x, const ModInt y) { return x.x < y.x; }
  friend bool operator==(const ModInt x, const ModInt y) { return x.x == y.x; }
  friend bool operator!=(const ModInt x, const ModInt y) { return x.x != y.x; }
};
const int mod = (1e9) + 7;
typedef ModInt<mod> mod_int;

struct SegTree {
  vector<int> v;
  SegTree(int n) {
    v.assign(n * 4 + 10, 0);
    build(1, 1, n);
  }
  void build(int idx, int l, int r) {
    if (l == r) {
      v[idx] = 1;
      return;
    }
    int m = (l + r) / 2;
    build(lc(idx), l, m);
    build(rc(idx), m + 1, r);
    push_up(idx);
  }
  inline int lc(int idx) { return 2 * idx; }
  inline int rc(int idx) { return 2 * idx + 1; }
  void update(int idx, int l, int r, int x, int delta) {
    if (x < l || x > r) return;
    if (l == r) {
      v[idx] += delta;
      return;
    }
    int m = (l + r) / 2;
    update(lc(idx), l, m, x, delta);
    update(rc(idx), m + 1, r, x, delta);
    push_up(idx);
  }
  auto query(int idx, int l, int r, int L, int R) -> int {
    if (R < l || r < L) return 0;
    if (L <= l && r <= R) return v[idx];
    int m = (l + r) / 2;
    return query(lc(idx), l, m, L, R) +
        query(rc(idx), m + 1, r, L, R);
  }
  void push_up(int idx) {
    v[idx] = v[lc(idx)] + v[rc(idx)];
  }
};
int len;
int calc_picked_cost(const vector<vector<int>> &pos,
                     const vector<int> &picked,
                     int idx,
                     SegTree &seg_tree) {
  int pick_a = pos[idx][picked[idx]];
  int pick_b = pos[idx][pos[idx].size() - 1 - picked[idx]];
  return seg_tree.query(1, 1, len, 1, pick_a) +
      seg_tree.query(1, 1, len, pick_b + 2, len);
}
void pick_it(const vector<vector<int>> &pos,
             vector<int> &picked,
             int idx,
             SegTree &seg_tree) {
  int pick_a = pos[idx][picked[idx]];
  int pick_b = pos[idx][pos[idx].size() - 1 - picked[idx]];
  seg_tree.update(1, 1, len, pick_a + 1, -1);
  seg_tree.update(1, 1, len, pick_b + 1, -1);
  picked[idx]++;
}
const int NC = 128;
void solve(int ncase) {
  string s;
  cin >> s;
  len = s.size();
  vector<vector<int>> opos(NC);
  vector<vector<int>> pos;
  for (int i = 0; i < s.size(); i++) {
    opos[s[i]].push_back(i);
  }
  int odd = 0;
  for (int i = 0; i < NC; i++) {
    if (opos[i].size() & 1) {
      odd++;
      if (odd > 1) {
        cout << "rkmdsxmds buKeai" << endl;
        return;
      }
    }
  }
  vector<int> picked;
  for (int i = 0; i < NC; i++) {
    if (opos[i].size()) {
      pos.push_back(opos[i]);
      picked.push_back(0);
    }
  }
  SegTree seg_tree(s.size());
  ll ret = 0;
  for (int i = 0, k = s.size() - 1; i < k; i++, k--) {
    int pick = -1, cost = 2 * s.size() + 1;
    for (int j = 0; j < pos.size(); j++) {
      if ((int) pos[j].size() - 2 * picked[j] >= 2) {
        int picked_cost = calc_picked_cost(pos, picked, j, seg_tree);
        if (picked_cost < cost) {
          pick = j;
          cost = picked_cost;
        }

      }
    }
    pick_it(pos, picked, pick, seg_tree);
    ret += cost;

  }
  cout << ret << endl;
}

void solve_all_cases() {
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  //pre_calc();
  while (T--) {
    solve(++ncase);
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << std::fixed;
  cout << setprecision(2);
#ifdef _zzz_
  //ios_base::sync_with_stdio(true);
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //auto x = freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
  //cerr << x << " " << errno << endl;
  auto start_time = clock();
#endif
  solve_all_cases();
  //test();
#ifdef _zzz_
  cout << (clock() - start_time) * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
#endif
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/
