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
template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class T>
using max_heap = priority_queue<T>;
const int mod = 1000000007;
//const int mod = 998244353;
const int inf = 0x3fffffff;
const int N = 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
int n;
ll b[N];
vector<vector<int>> tree;

ll ans;

void add_mod(ll a) {
  ans = (ans + a % mod) % mod;
}

void dfs(int r, int pre, const unordered_map<ll, int> &z) {
  unordered_map<ll, int> nz;
  nz[b[r]]++;
  add_mod(b[r]);
  for (auto p : z) {
    ll d = gcd(b[r], p.first);
    add_mod(d % mod * p.second);
    nz[d] += p.second;
  }
  for (auto u : tree[r]) {
    if (u == pre) continue;
    dfs(u, r, nz);
  }
}

void solve(int ncase) {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &b[i]);
  }
  tree.assign(n + 1, vector<int>());
  for (int i = 1; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    tree[x].push_back(y);
    tree[y].push_back(x);
  }
  dfs(1, -1, unordered_map<ll, int>());
  cout << ans << endl;
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
  //ios::sync_with_stdio(false);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
  auto start_time = clock();
#endif
  solve_all_cases();
  //test();
#ifdef _zzz_
  cout << (clock() - start_time) * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
#endif
}
