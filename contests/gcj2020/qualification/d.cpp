/*
1. Find unfilled x can be done by bipartite match
2. Find match one by one due to Hall's marriage theorem. Find the one with more restriction first to keep Hall's condition.
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
template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class T>
using max_heap = priority_queue<T>;
//const int mod = 1000000007;
const int mod = 998244353;
const int inf = 0x3fffffff;
const int N = 2 * 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

vector<ll> col_mask;
vector<ll> row_mask;
vector<vector<int>> g;

int n, k;

struct Bipartite {
  Bipartite(int n1_, int n2_) {
    n1 = n1_;
    n2 = n2_;
    n = n1 + n2;
    g.assign(n, vector<int>());
    match.assign(n, -1);
  }
  void addedge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
  }
  int max_match() {
    int ret = 0;
    for (int i = 0; i < n1; i++) {
      vst.assign(n, 0);
      if (dfs(i)) ret++;
    }
    return ret;
  }
  const vector<int> &get_match() {
    return match;
  }
 private:
  int n1, n2, n;
  vector<vector<int>> g;
  vector<int> vst;
  vector<int> match;
  bool dfs(int u) {
    for (auto v : g[u]) {
      if (vst[v]) continue;
      vst[v] = 1;
      if (match[v] == -1 || dfs(match[v])) {
        match[v] = u;
        match[u] = v;
        return true;
      }
    }
    return false;
  }
};

void insert_g(int x, int y, int v) {
  row_mask[x] |= (1LL << v);
  col_mask[y] |= (1LL << v);
  g[x][y] = v;
}

void calc(int z) {
  Bipartite graph(n, n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (g[i][j]) continue;
      if (row_mask[i] & (1LL << z)) continue;
      if (col_mask[j] & (1LL << z)) continue;
      graph.addedge(i, n + j);
    }
  }
  graph.max_match();
  auto &m = graph.get_match();
  for (int i = 0; i < n; i++) {
    if (m[i] != -1) {
      insert_g(i, m[i] - n, z);
    }
  }
}

void solve(int ncase) {
  cin >> n >> k;
  if (k == n + 1 || k == n * n - 1 || (n == 3 && (k == 5 || k == 7))) {
    cout << "Case #" << ncase << ": IMPOSSIBLE" << endl;
    return;
  }
  row_mask.assign(n, 0);
  col_mask.assign(n, 0);
  g.assign(n, vector<int>(n));
  bool flag = false;
  set<int> s;
  for (int a = 1; !flag && a <= n; a++) {
    for (int b = 1; !flag && b <= n && b < k - (n - 2) * a; b++) {
      int c = k - (n - 2) * a - b;
      if (c < 0 || c > n || ((b == a) != (c == a))) {
        continue;
      }
      flag = true;
      for (int i = 0; i < n - 2; i++) {
        insert_g(i, i, a);
      }
      insert_g(n - 2, n - 2, b);
      insert_g(n - 1, n - 1, c);
      s.insert(a);
      s.insert(b);
      s.insert(c);
    }
  }

  vector<int> z;
  for (int x : s) z.push_back(x);
  for (int i = 1; i <= n; i++) {
    if (s.find(i) != s.end()) continue;
    z.push_back(i);
  }
  for (int x : z) {
    calc(x);
  }
  cout << "Case #" << ncase << ": POSSIBLE" << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << g[i][j] << (j < n - 1 ? ' ' : '\n');
    }
  }
}

void solve_all_cases() {
  int T = 1;
  //scanf("%d", &T);
  cin >> T;
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
  freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
#endif
  solve_all_cases();
  //test();
}
