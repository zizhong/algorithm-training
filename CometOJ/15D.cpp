/**
* https://cometoj.com/contest/15/problem/D?problem_id=216
* bitmask DP, with generated tree.
* iterative version. recursive was TLE.
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

const int N = 16;
int n, m;
int e[N][N];
ll f[1 << N][N];
void update(ll &v1, ll v2) {
  if (v1 < v2) v1 = v2;
}
vector<vector<int>> num;
void solve(int ncase) {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int x, y, w;
    scanf("%d%d%d", &x, &y, &w);
    x--;
    y--;
    e[x][y] = e[y][x] = w;
  }
  int T = (1 << n) - 1;
  num.assign((1 << n), vector<int>());
  for (int s = 0; s <= T; s++) {
    for (int i = 0; i < n; i++) {
      if ((s & (1 << i))) num[s].push_back(i);
    }
  }
  CLS(f, -1);
  for (int s = 1; s < (1 << n); s++) {
    if (num[s].size() == 1) {
      f[s][num[s][0]] = 0;
      continue;
    }
    for (auto u : num[s]) {
      int ss = s ^(1 << u);
      for (int t = ss; t; t = ((t - 1) & ss)) {
        if (f[s ^ t][u] < 0) continue;
        int cnt = num[t].size();
        for (auto v : num[t]) {
          if (e[u][v] == 0 || f[t][v] < 0) continue;
          update(f[s][u], f[t][v] + f[s ^ t][u] + e[u][v] * 1LL * cnt * (n - cnt));
        }
      }
    }
  }

  ll ans = 0;
  for (int i = 0; i < n; i++) ans = max(ans, f[T][i]);
  printf("%lld\n", ans);
}
void solve_all_cases() {
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
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
