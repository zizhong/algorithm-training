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

int n;
ll t[N];
ll h[N];
vector<vector<int>> g;
vector<PLL> f;

void dfs(int u, int pre) {
  for (auto v : g[u]) {
    if (v == pre) continue;
    dfs(v, u);
  }
  int c[2] = {0}; // in, out of u
  ll base = 0;
  vector<ll> delta;
  for (auto v : g[u]) {
    if (v == pre) continue;
    if (h[v] < h[u]) {
      c[0]++;
      base += f[v].first;
    } else if (h[v] > h[u]) {
      c[1]++;
      base += f[v].second;
    } else {
      c[0]++;
      base += f[v].first;
      delta.push_back(f[v].second - f[v].first);
    }
  }
  sort(delta.begin(), delta.end(), greater<ll>());

  for (int my = 0; my < 2; my++) {
    if (pre != -1) {
      if (my == 0 && h[u] > h[pre] || my == 1 && h[u] < h[pre]) continue;
    }
    int k[2] = {0};
    k[0] = c[0];
    k[1] = c[1];
    if (pre != -1) k[1 - my]++;
    ll ans = base + t[u] * min(k[0], k[1]);
    ll cur = 0;
    for (int i = 0; i < delta.size(); i++) {
      cur += delta[i];
      k[0]--;
      k[1]++;
      ans = max(ans, base + cur + t[u] * min(k[0], k[1]));
    }
    if (my == 0) {
      f[u].first = ans;
    } else {
      f[u].second = ans;
    }
  }
}

void solve(int ncase) {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> t[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> h[i];
  }
  g.assign(n + 1, vector<int>());
  ll ans = 0;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
    ans += t[u] + t[v];
  }
  f.assign(n + 1, {-1, -1});
  dfs(1, -1);
  cout << ans - f[1].first << endl;
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
