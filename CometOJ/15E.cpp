/**
* 1. a greedy algorithm to get the max independent set from a tree. (first get the leaves, and then remove the fathers,...)
* 2. a simple tree dp + a slightly complex reverse tree dp + a simple tree dp 
        to get if the root can be selected for each node as root. 
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
const double pi = acos(-1);

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
  return os << "(" << P.st << "," << P.nd << ")";
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
//const int mod = 1000000007;
const int mod = 998244353;

//const int N = 1e6 + 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

void pre_calc() {

}

int n, m;
vector<vector<int>> tree;
vector<int> fa;
vector<int> f;
vector<int> sum_f;
vector<int> up;

void dfs_f(int u, int pre) {
  int cnt_f = 0;
  fa[u] = pre;
  for (auto v : tree[u]) {
    if (v == pre) continue;
    dfs_f(v, u);
    cnt_f += f[v];
  }
  sum_f[u] = cnt_f;
  if (cnt_f == 0) f[u] = 1;
  return;
}

// for each u, consider if father is chosen after removing subtree(u)
// that is a reverse order tree dp.
int dfs_up(int u, int pre) {
  if (pre == 0) {
    up[u] = 0;
  } else {
    int cnt_f = up[pre] + sum_f[pre] - f[u];
    if (cnt_f > 0) up[u] = 0;
    else up[u] = 1;
  }
  for (auto v : tree[u]) {
    if (v == pre) continue;
    dfs_up(v, u);
  }
}

void solve(int ncase) {
  scanf("%d%d", &n, &m);
  tree.assign(n + 1, vector<int>());
  fa.assign(n + 1, 0);
  f.assign(n + 1, 0);
  up.assign(n + 1, -1);
  sum_f.assign(n + 1, -1);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    tree[x].push_back(y);
    tree[y].push_back(x);
  }
  dfs_f(1, 0);
  up[0] = 0;
  dfs_up(1, 0);
  vector<int> cc(n + 1);
  for (int i = 1; i <= n; i++) {
    int cnt_f = up[i];
    for (auto v : tree[i]) {
      if (v == fa[i]) continue;
      cnt_f += f[v];
    }
    if (cnt_f > 0) cc[i] = 0;
    else cc[i] = 1;
  }
  ll ansb = accumulate(f.begin(), f.end(), 0);
  ll ans = ansb;
  printf("%lld\n", ans);
  int has_r = cc[1];
  while (m--) {
    int x;
    scanf("%d", &x);
    ans = (n * ans % mod + (has_r > 0 ? 0 : ansb)) % mod;
    printf("%lld\n", ans);
    if (has_r) {
      has_r = 0;
    } else {
      has_r = cc[x];
    }
  }
}
void solve_all_cases() {
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  pre_calc();
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
  ios_base::sync_with_stdio(true);
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
  auto start_time = clock();
#endif
  solve_all_cases();
//  test();
#ifdef _zzz_
  cout << (clock() - start_time) * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
#endif
}
