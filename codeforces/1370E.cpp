// DP

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
int n;
vector<vector<int>> tree;
void dfs(int u, int pre, int start, int d, vector<vector<int>> &dis) {
  dis[start][u] = d;
  for (auto v : tree[u]) {
    if (v == pre) continue;
    dfs(v, u, start, d + 1, dis);
  }
}
void solve(int ncase) {
  cin >> n;
  tree.assign(n + 1, vector<int>());
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  vector<vector<int>> dis(n + 1, vector<int>(n + 1));
  for (int i = 1; i <= n; i++) {
    dfs(i, -1, i, 0, dis);
  }
  cout << "? " << n;
  for (int i = 1; i <= n; i++) cout << " " << i;
  cout << endl;
  cout.flush();
  int e, d, nd;
  cin >> e >> nd;
  d = (nd + 1) / 2;
  vector<int> nq;
  for (int i = 1; i <= n; i++) {
    if (dis[e][i] == d) nq.push_back(i);
  }
  cout << "? " << nq.size();
  for (int i = 0; i < nq.size(); i++) cout << " " << nq[i];
  cout << endl;
  cout.flush();
  int e1 = e, e2, d2;
  cin >> e2 >> d2;
  for (int q = 1; q < 12; q++) {
    debug(e1, e2);
    d = (d + 1) / 2;
    nq.clear();
    for (int i = 1; i <= n; i++) {
      if (dis[e1][i] + dis[e2][i] == dis[e1][e2]) continue;
      if (dis[e1][i] == d || dis[e2][i] == d) {
        nq.push_back(i);
      }
    }
    if (nq.size() == 0) {
      cout << "! " << e1 << " " << e2 << endl;
      cout.flush();
      string ret;
      cin >> ret;
      return;
    }
    cout << "? " << nq.size();
    for (int i = 0; i < nq.size(); i++) cout << " " << nq[i];
    cout << endl;
    cout.flush();
    cin >> e >> d2;
    if (d2 != nd) {
      cout << "! " << e1 << " " << e2 << endl;
      cout.flush();
      string ret;
      cin >> ret;
      return;
    }
    if (dis[e][e1] < dis[e][e2]) e1 = e;
    else e2 = e;
  }
  cout << "! " << e1 << " " << e2 << endl;
  cout.flush();
  string ret;
  cin >> ret;
  return;
}
 
void solve_all_cases() {
  int T = 1;
  //scanf("%d", &T);
  cin >> T;
  int ncase = 0;
  //pre_calc();
  while (T--) {
    solve(++ncase);
  }
}
 
int main() {
  //ios_base::sync_with_stdio(0);
  //cin.tie(0);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  ios_base::sync_with_stdio(true);
  //freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
  auto start_time = clock();
#endif
  solve_all_cases();
//  test();
#ifdef _zzz_
  cout << (clock() - start_time) * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
#endif
}
