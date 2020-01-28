/*
1293E

https://codeforces.com/contest/1293/problem/E

1. first think of a chain, then think of a tree
2. O(N^3) DP works like, enumerate the edge assigned with 0, and dp[u][v] is the max value.
   A key optimization is to pre calculate the info for each dfs with different root. And then 
   `dp[u][v] = child_with_root[u][v] * child_with_root[v][u] + max(dp[u][father_with_root[u][r]] + dp[v][father_with_root[v][u]])`. 
3. the range of ans is 3000 * 3000 * 3000 = 27 * 1e9, which can cause integer overflows.
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
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
vector<vector<int>> tree;
vector<vector<int>> f_r;
vector<vector<int>> c_r;
void dfs(int r, int pre, int rr) {
  f_r[rr][r] = pre;
  for(auto u : tree[r]) {
    if (u == pre) continue;
    dfs(u, r, rr);
    c_r[rr][r] += c_r[rr][u];
  }
}

vector<vector<ll>> dp;
ll f(int x, int y) {
  if (x == y) return 0;
  if (x > y) swap(x, y);
  if (dp[x][y] >= 0) {
    return dp[x][y];
  }
  if (x == f_r[x][y] || y == f_r[y][x]) {
    return dp[x][y] = c_r[x][y] * c_r[y][x];
  }
  return dp[x][y] = c_r[x][y] * c_r[y][x] + max(f(f_r[y][x], y), f(x, f_r[x][y]));
}

void solve(int ncase) {
  int n;
  cin >> n;
  tree.assign(n, vector<int>());
  for(int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    x --;
    y --;
    tree[x].push_back(y);
    tree[y].push_back(x);
  }
  f_r.assign(n, vector<int>(n, -1));
  c_r.assign(n, vector<int>(n, 1));
  for(int r = 0; r < n; r++) {
    dfs(r, -1, r);
  }
  dp.assign(n, vector<ll>(n, -1));
  ll ans = 0;
  for(int x = 0; x < n; x ++) {
    if (tree[x].size() > 1) continue;
    for(int y = x + 1; y < n; y++) {
      if (tree[y].size() > 1) continue;
      ans = max(ans, f(x, y));
    }
  }

  cout << ans << endl;
}



int main() {
  //ios::sync_with_stdio(false);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //freopen("out.txt", "w", stdout);
#endif
  //precalc();
  int T = 1;
  //scanf("%d", &T);
 //  cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}

