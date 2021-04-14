/**
*  1. min cost max flow
*  2. map builder S->out(x) in(x)->T in(x)->out(y), this can help to limit the cap of x to 1.
*  3. the flow path is an euler path.
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
#define __builtin_sprintf
#include <bits/extc++.h>
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
template<typename T>
inline T read_by_char() {
  T s = 0, f = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    s = (s << 3) + (s << 1) + ch - 48;
    ch = getchar();
  }
  return s * f;
}
#define ri() read_by_char<int>()
#define rl() read_by_char<ll>()

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
ostream &operator<<(ostream &os, set<T> V) {
  os << "[";
  for (auto vv : V) os << vv << ",";
  return os << "]";
}
template<class T>
ostream &operator<<(ostream &os, multiset<T> V) {
  os << "[";
  for (auto vv : V) os << vv << ",";
  return os << "]";
}
template<class T>
ostream &operator<<(ostream &os, unordered_set<T> V) {
  os << "[";
  for (auto vv : V) os << vv << ",";
  return os << "]";
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

template<unsigned MOD_>
struct ModInt {
  static constexpr unsigned MOD = MOD_;
  unsigned x;
  void undef() { x = (unsigned) -1; }
  bool isnan() const { return x == (unsigned) -1; }
  inline int geti() const { return (int) x; }
  ModInt() { x = 0; }
  ModInt(const ModInt &y) { x = y.x; }
  ModInt(int y) {
    if (y < 0 || (int) MOD <= y) y %= (int) MOD;
    if (y < 0) y += MOD;
    x = y;
  }
  ModInt(unsigned y) { if (MOD <= y) x = y % MOD; else x = y; }
  ModInt(long long y) {
    if (y < 0 || MOD <= y) y %= MOD;
    if (y < 0) y += MOD;
    x = y;
  }
  ModInt(unsigned long long y) { if (MOD <= y) x = y % MOD; else x = y; }
  ModInt &operator+=(const ModInt y) {
    if ((x += y.x) >= MOD) x -= MOD;
    return *this;
  }
  ModInt &operator-=(const ModInt y) {
    if ((x -= y.x) & (1u << 31)) x += MOD;
    return *this;
  }
  ModInt &operator*=(const ModInt y) {
    x = (unsigned long long) x * y.x % MOD;
    return *this;
  }
  ModInt &operator/=(const ModInt y) {
    x = (unsigned long long) x * y.inv().x % MOD;
    return *this;
  }
  ModInt operator-() const { return (x ? MOD - x : 0); }

  ModInt inv() const { return pow(MOD - 2); }
  ModInt pow(long long y) const {
    ModInt b = *this, r = 1;
    if (y < 0) {
      b = b.inv();
      y = -y;
    }
    for (; y; y >>= 1) {
      if (y & 1) r *= b;
      b *= b;
    }
    return r;
  }

  friend ModInt operator+(ModInt x, const ModInt y) { return x += y; }
  friend ModInt operator-(ModInt x, const ModInt y) { return x -= y; }
  friend ModInt operator*(ModInt x, const ModInt y) { return x *= y; }
  friend ModInt operator/(ModInt x, const ModInt y) { return x *= y.inv(); }
  friend bool operator<(const ModInt x, const ModInt y) { return x.x < y.x; }
  friend bool operator==(const ModInt x, const ModInt y) { return x.x == y.x; }
  friend bool operator!=(const ModInt x, const ModInt y) { return x.x != y.x; }
};

const unsigned int mod = 1e9 + 7;
typedef ModInt<mod> mod_int;

template<class M>
struct ModCombination {
 public:
  ModCombination() {}
  ModCombination(int n) : n_(n), fac_(n + 1), facinv_(n + 1) {
    assert(1 <= n);
    fac_[0] = 1;
    for (int i = 1; i <= n; i++) fac_[i] = fac_[i - 1] * i;
    facinv_[n] = M(1) / fac_[n];
    for (int i = n; i >= 1; i--) facinv_[i - 1] = facinv_[i] * i;
  }

  M fac(int k) const {
    assert(0 <= k and k <= n_);
    return fac_[k];
  }
  M facinv(int k) const {
    assert(0 <= k and k <= n_);
    return facinv_[k];
  }
  M inv(int k) const {
    assert(1 <= k and k <= n_);
    return facinv_[k] * fac_[k - 1];
  }

  M P(int n, int k) const {
    if (k < 0 or k > n) return M(0);
    assert(n <= n_);
    return fac_[n] * facinv_[n - k];
  }
  M C(int n, int k) const {
    if (k < 0 or k > n) return M(0);
    assert(n <= n_);
    return fac_[n] * facinv_[n - k] * facinv_[k];
  }
  M H(int n, int k) const {
    if (n == 0 and k == 0) return M(1);
    return C(n + k - 1, n);
  }
  M catalan(int n) const {
    if (n == 0) return M(1);
    return C(2 * n, n) - C(2 * n, n - 1);
  }

 private:
  int n_;
  vector<M> fac_, facinv_;
};

template<typename flow_t = int, typename cost_t = long long>
struct MCMF_SSPA {
  int N;
  std::vector<std::vector<int>> adj;
  struct edge_t {
    int dest;
    flow_t cap;
    cost_t cost;
  };
  std::vector<edge_t> edges;

  std::vector<char> seen;
  std::vector<cost_t> pi;
  std::vector<int> prv;

  explicit MCMF_SSPA(int N_) : N(N_), adj(N), pi(N, 0), prv(N) {}

  void addEdge(int from, int to, flow_t cap, cost_t cost) {
    //debug(from, to, cap, cost);
    assert(cap >= 0);
    assert(cost >= 0); // TODO: Remove this restriction
    int e = int(edges.size());
    edges.emplace_back(edge_t{to, cap, cost});
    edges.emplace_back(edge_t{from, 0, -cost});
    adj[from].push_back(e);
    adj[to].push_back(e + 1);
  }

  const cost_t INF_COST = std::numeric_limits<cost_t>::max() / 4;
  const flow_t INF_FLOW = std::numeric_limits<flow_t>::max() / 4;
  std::vector<cost_t> dist;
  __gnu_pbds::priority_queue<std::pair<cost_t, int>> q;
  std::vector<typename decltype(q)::point_iterator> its;
  void path(int s) {
    dist.assign(N, INF_COST);
    dist[s] = 0;

    its.assign(N, q.end());
    its[s] = q.push({0, s});

    while (!q.empty()) {
      int i = q.top().second;
      q.pop();
      cost_t d = dist[i];
      for (int e : adj[i]) {
        if (edges[e].cap) {
          int j = edges[e].dest;
          cost_t nd = d + edges[e].cost;
          if (nd < dist[j]) {
            dist[j] = nd;
            prv[j] = e;
            if (its[j] == q.end()) {
              its[j] = q.push({-(dist[j] - pi[j]), j});
            } else {
              q.modify(its[j], {-(dist[j] - pi[j]), j});
            }
          }
        }
      }
    }

    swap(pi, dist);
  }

  std::pair<flow_t, cost_t> maxflow(int s, int t) {
    assert(s != t);
    flow_t totFlow = 0;
    cost_t totCost = 0;
    while (path(s), pi[t] < INF_COST) {
      flow_t curFlow = std::numeric_limits<flow_t>::max();
      for (int cur = t; cur != s;) {
        int e = prv[cur];
        int nxt = edges[e ^ 1].dest;
        curFlow = std::min(curFlow, edges[e].cap);
        cur = nxt;
      }
      totFlow += curFlow;
      totCost += pi[t] * curFlow;
      for (int cur = t; cur != s;) {
        int e = prv[cur];
        int nxt = edges[e ^ 1].dest;
        edges[e].cap -= curFlow;
        edges[e ^ 1].cap += curFlow;
        cur = nxt;
      }
    }
    return {totFlow, totCost};
  }
};
/*
typedef int F;
#define REP(i, n) for((i)=0;(i)<(int)(n);(i)++)
const F F_INF = (1 << 29);
const int MAXV = 4 * 10000 + 10;
const int MAXE = MAXV * 10 * 2; // E*2!

F cap[MAXE], flow[MAXE];
int to[MAXE], _prev[MAXE], last[MAXV], used[MAXV], level[MAXV];

struct MaxFlow {
  int V, E;

  MaxFlow(int n) {
    int i;
    V = n;
    E = 0;
    REP(i, V)last[i] = -1;
  }

  void add_edge(int x, int y, F f) {
    cap[E] = f;
    flow[E] = 0;
    to[E] = y;
    _prev[E] = last[x];
    last[x] = E;
    E++;
    cap[E] = 0;
    flow[E] = 0;
    to[E] = x;
    _prev[E] = last[y];
    last[y] = E;
    E++;
  }

  bool bfs(int s, int t) {
    int i;
    REP(i, V)level[i] = -1;
    queue<int> q;
    q.push(s);
    level[s] = 0;
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      for (i = last[x]; i >= 0; i = _prev[i])
        if (level[to[i]] == -1 && cap[i] > flow[i]) {
          q.push(to[i]);
          level[to[i]] = level[x] + 1;
        }
    }
    return (level[t] != -1);
  }

  F dfs(int v, int t, F f) {
    int i;
    if (v == t) return f;
    for (i = used[v]; i >= 0; used[v] = i = _prev[i])
      if (level[to[i]] > level[v] && cap[i] > flow[i]) {
        F tmp = dfs(to[i], t, min(f, cap[i] - flow[i]));
        if (tmp > 0) {
          flow[i] += tmp;
          flow[i ^ 1] -= tmp;
          return tmp;
        }
      }
    return 0;
  }

  F maxflow(int s, int t) {
    int i;
    while (bfs(s, t)) {
      REP(i, V)used[i] = last[i];
      while (dfs(s, t, F_INF) != 0);
    }
    F ans = 0;
    for (i = last[s]; i >= 0; i = _prev[i]) ans += flow[i];
    return ans;
  }

};
*/
void update(int &v, int nv) {
  if (v < 0 || nv >= 0 && v > nv) v = nv;
}
void update_max(int &v, int nv) {
  v = max(v, nv);
}

void pre_calc() {
}

const int INF = 1e9;
int n, d;
int D, N, S, T;
int in(int x) {
  return x % D;
}
int out(int x) {
  return x % D + D;
}
vector<vector<PII>> g;
void dfs_euler(int u, vector<int> &path) {
  for (auto &p : g[u]) {
    if (p.second == 0) continue;
    p.second = 0;
    dfs_euler(p.first, path);
  }
  path.push_back(u);
}

void solve(int ncase) {
  cin >> d >> n;
  D = (1 << d);
  N = 2 * D + 2;
  S = N - 2;
  T = N - 1;
  MCMF_SSPA flow(N);
  for (int i = 0; i < D; i++) {
    flow.addEdge(i, out(i), INF, 0);
    flow.addEdge(out(i), 0, INF, 1);
    for (int j = 0; j < d; j++) {
      if (i & (1 << j)) continue;
      flow.addEdge(out(i), (i | (1 << j)), INF, 1);
    }
  }
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    int x = 0;
    for (int j = 0; j < d; j++) {
      x = x * 2 + (s[j] == '1');
    }
    flow.addEdge(S, out(x), 1, 0);
    flow.addEdge(x, T, 1, 0);
  }
  auto[f, c] = flow.maxflow(S, T);
  g = vector<vector<PII>>(D);
  for (int i = 0; i < int(flow.edges.size()); i += 2) {
    int v = flow.edges[i].dest;
    int u = flow.edges[i + 1].dest;
    int cap = flow.edges[i + 1].cap;
    if (u == S || v == T || u % D == v % D) continue;
    if (__builtin_popcount(in(u) ^ in(v)) != 1 && v != 0) continue;
    while (cap--) {
      g[in(u)].push_back({in(v), 1});
    }
  }
  vector<int> path;
  path.reserve(c);
  dfs_euler(0, path);
  debug(path);
  cout << path.size() - 2 << endl;
  for (int i = path.size() - 2; i >= 1; i--) {
    cout << char(path[i] == 0 ? 'R' : ('0' + d - 1 - __builtin_ctz(path[i] ^ path[i + 1]))) << (" \n"[i == 1]);
  }
}

void solve_all_cases() {
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  // T = ri();
  int ncase = 0;
  pre_calc();
  while (T--) {
    solve(++ncase);
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  //ios_base::sync_with_stdio(true);
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //auto x = freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
  //cerr << x << " " << errno << endl;
  auto start_time = clock();
#endif
  //pre_calc();
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
