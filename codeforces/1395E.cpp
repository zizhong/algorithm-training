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

//const int mod = 998244353;
const int mod = 1e9 + 7;
//const int N = 1e6 + 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
const int N = 2 * 100010;

int n, m, k;
vector<vector<PII>> g;

int BAD[100][100];
map<int, int> idx2cnt[N];
inline int get_idx(int sz, int i) {
  return sz * 10 + i;
}
vector<int> path;
int ans;
void dfs(int sz) {
  if (sz == k + 1) {
    //debug(path);
    ans++;
    return;
  }
  for (int i = 0; i < sz; i++) {
    int idx = get_idx(sz, i);
    if (BAD[idx][idx]) continue;
    bool flag = true;
    for (auto x : path) {
      if (BAD[idx][x]) {
        flag = false;
        break;
      }
    }
    if (!flag) continue;
    path.push_back(idx);
    dfs(sz + 1);
    path.pop_back();
  }
}

void solve(int ncase) {
  cin >> n >> m >> k;
  g.assign(n + 1, vector<PII>());
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    g[u].push_back({w, v});
  }
  for (int i = 1; i <= n; i++) {
    sort(g[i].begin(), g[i].end());
    for (int j = 0; j < g[i].size(); j++) {
      int v = g[i][j].second;
      idx2cnt[v][get_idx(g[i].size(), j)]++;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (auto x : idx2cnt[i]) {
      for (auto y : idx2cnt[i]) {
        if (x.first == y.first) {
          if (x.second > 1) BAD[x.first][x.first] = 1;
        } else {
          BAD[x.first][y.first] = 1;
        }
      }
    }
  }
  dfs(1);
  cout << ans << endl;
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
  cout << setprecision(6);
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
  //cout << (clock() - start_time) * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
#endif
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/
