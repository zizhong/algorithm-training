// reverse pairs

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

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

int sgn(int x) { return x == 0 ? 0 : (x > 0 ? 1 : -1); }

struct SegTree {
  vector<int> v;
  SegTree(int n) {
    v.assign(n * 4 + 10, 0);
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
  int query(int idx, int l, int r, int L, int R) {
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

void solve(int ncase) {
  int n;
  cin >> n;
  string s;
  cin >> s;
  vector<vector<int>> idx(26);
  for (int i = 0; i < s.size(); i++) {
    idx[s[i] - 'a'].push_back(i);
  }
  vector<int> head(26);
  string sb = s;
  reverse(sb.begin(), sb.end());
  SegTree seg_tree(n);
  ll ret = 0;
  for (auto c : sb) {
    int ci = c - 'a';
    int x = idx[ci][head[ci]++];
    ret += seg_tree.query(1, 1, n, x, n);
    seg_tree.update(1, 1, n, x, 1);
  }
  cout << ret << endl;
}

void solve_all_cases() {
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
//  pre_calc();
  while (T--) {
    solve(++ncase);
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << std::fixed;
  cout << setprecision(9);
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
