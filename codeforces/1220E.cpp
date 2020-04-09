/**
* Tarjan scc
* Tarjan Bridge
* Tarjan vertex cut
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
const int mod = 1000000007;
//const int mod = 998244353;
const int inf = 0x3fffffff;
//const int N = 2 * 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
 
struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
 
vector<int> w;
 
int n, m;
vector<vector<int>> g;
 
#if 0
// tarjan scc https://www.byvoid.com/zhs/blog/scc-tarjan
vector<int> scc;
stack<int> st;
vector<bool> in_stack;
vector<int> dfn;
vector<int> low;
int time_stamp, scc_idx;
void tarjan_scc_init() {
  scc.assign(n + 1, 0);
  in_stack.assign(n + 1, 0);
  dfn.assign(n + 1, -1);
  low.assign(n + 1, -1);
  time_stamp = 0;
  scc_idx = 0;
  tarjan_scc(1);
}
void tarjan_scc(int r) {
  dfn[r] = low[r] = time_stamp++;
  st.push(r);
  in_stack[r] = true;
  for (auto u : g[r]) {
    if (dfn[u] < 0) {
      tarjan_scc(u);
      low[r] = min(low[r], low[u]);
    } else if (in_stack[u]) {
      low[r] = min(low[r], dfn[u]);
    }
  }
  if (dfn[r] == low[r]) {
    int v = -1;
    do {
      v = st.top();
      st.pop();
      in_stack[v] = false;
      scc[v] = scc_idx;
    } while (r != v);
    scc_idx++;
  }
}
/// tarjan_scc END
#endif
 
// tarjan bridge https://oi-wiki.org/graph/cut/
vector<int> dfn;
vector<int> low;
vector<int> father;
vector<int> is_bridge;
int time_stamp;
set<PII> bridge;
void tarjan_bridge_init() {
  dfn.assign(n + 1, -1);
  low.assign(n + 1, -1);
  father.assign(n + 1, -1);
  is_bridge.assign(n + 1, 0);
  time_stamp = 0;
  bridge.clear();
}
 
void tarjan_bridge(int r, int pre) {
  father[r] = pre;
  dfn[r] = low[r] = time_stamp++;
  for (auto u : g[r]) {
    if (dfn[u] < 0) {
      tarjan_bridge(u, r);
      low[r] = min(low[r], low[u]);
      if (low[u] > dfn[r]) {
        is_bridge[u] = 1;
        bridge.insert(PII(u, father[u]));
        bridge.insert(PII(father[u], u));
      }
    } else if (dfn[u] != dfn[r] && u != pre) {
      low[r] = min(low[r], dfn[u]);
    }
  }
}
 
vector<vector<int>> tree;
vector<ll> tree_w;
vector<int> cc;
vector<int> cnt;
vector<int> choose;
int cc_idx;
void dfs_without_bridge(int r) {
  cc[r] = cc_idx;
  for (auto u : g[r]) {
    if (cc[u] < 0) {
      if (bridge.find(PII(r, u)) == bridge.end()) {
        dfs_without_bridge(u);
      }
    }
  }
}
void to_tree() {
  cc.assign(n + 1, -1);
 
  cc_idx = 0;
  for (int i = 1; i <= n; i++) {
    if (cc[i] == -1) {
      dfs_without_bridge(i);
      cc_idx++;
    }
  }
  cnt.assign(cc_idx, 0);
  tree_w.assign(cc_idx, 0LL);
  for (int i = 1; i <= n; i++) {
    tree_w[cc[i]] += w[i];
    cnt[cc[i]]++;
  }
  tree.assign(cc_idx, vector<int>());
  choose.assign(cc_idx, false);
  for (auto p : bridge) {
    int u = cc[p.first];
    int v = cc[p.second];
    tree[u].push_back(v);
  }
}
 
ll ans;
ll max_leaf = 0;
 
bool dfs1(int r, int pre) {
  if (cnt[r] > 1) choose[r] = true;
  for (auto u : tree[r]) {
    if (u == pre) continue;
    if (dfs1(u, r)) choose[r] = true;
  }
 
  if (choose[r]) ans += tree_w[r];
  return choose[r];
}
 
void dfs2(int r, int pre, ll v) {
  bool leaf = true;
  for (auto u : tree[r]) {
    if (u == pre) continue;
    dfs2(u, r, choose[u] ? 0 : v + tree_w[u]);
  }
  if (leaf) {
    max_leaf = max(max_leaf, v);
  }
}
 
void solve(int ncase) {
  scanf("%d%d", &n, &m);
  g.assign(n + 1, vector<int>());
  w.assign(n + 1, 0);
  ll sum = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &w[i]);
    sum += w[i];
  }
 
  for (int i = 0; i < m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  int s;
  scanf("%d", &s);
  tarjan_bridge_init();
  tarjan_bridge(1, -1);
  to_tree();
  s = cc[s];
  ans = 0;
  dfs1(s, -1);
  dfs2(s, -1, choose[s] ? 0 : tree_w[s]);
  cout << ans + max_leaf << endl;
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
