// https://www.facebook.com/codingcompetitions/hacker-cup/2019/round-1/problems/C
// max flow, min cut

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

//const int N = 1e6 + 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

struct edge { int to, cap, rev; };

const int INF = 0x3fffffff;
const int MAXV = 64 * 2 + 10;
vector<edge> G[MAXV];
int level[MAXV];
int iter[MAXV];

void add_edge(int from, int to, int cap) {
  //cout << from << "->" << to << ": " << cap << endl;
  G[from].push_back(edge{to, cap, (int) G[to].size()});
  G[to].push_back(edge{from, 0, (int) G[from].size() - 1});
}

void bfs(int s) {
  memset(level, -1, sizeof(level));
  queue<int> que;
  level[s] = 0;
  que.push(s);
  while (que.size()) {
    int v = que.front();
    que.pop();
    for (auto &e: G[v]) {
      if (e.cap > 0 && level[e.to] < 0) {
        level[e.to] = level[v] + 1;
        que.push(e.to);
      }
    }
  }
}

int dfs(int v, int t, int f) {
  if (v == t) return f;
  for (int &i = iter[v]; i < G[v].size(); i++) {
    edge &e = G[v][i];
    if (e.cap > 0 && level[v] < level[e.to]) {
      int d = dfs(e.to, t, min(f, e.cap));
      if (d > 0) {
        e.cap -= d;
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int max_flow(int s, int t) {
  int flow = 0;
  for (;;) {
    bfs(s);
    if (level[t] < 0) return flow;
    memset(iter, 0, sizeof(iter));
    int f;
    while ((f = dfs(s, t, INF)) > 0) flow += f;
  }
}

void init_max_flow() {
  for (auto &v : G) v.clear();
  memset(level, 0, sizeof(level));
}

struct Seg {
  int x, a, b;
  void init() {
    cin >> x >> a >> b;
  }
  bool operator<(const Seg &rhs) const {
    if (x == rhs.x) return a < rhs.a;
    return x < rhs.x;
  }
};
int n, h;

vector<Seg> vs;
vector<PII> calc_cover(int st, int ed, int step, int idx) {
  vector<PII> cover;
  set<PII> s;
  s.emplace(vs[idx].a, vs[idx].b);
  for (int i = st; i <= ed && !s.empty(); i += step) {
    set<PII> ns;
    for (auto &p : s) {
      if (p.first >= vs[i].b || p.second <= vs[i].a) {
        ns.emplace(p);
        continue;
      }

      PII c(max(vs[i].a, p.first), min(vs[i].b, p.second));
      cover.emplace_back(i, c.second - c.first);
      if (p == c) {
        continue;
      }
      if (p.first == c.first) {
        ns.emplace(c.second, p.second);
        continue;
      }
      if (p.second == c.second) {
        ns.emplace(p.first, c.first);
        continue;
      }
      ns.emplace(p.first, c.first);
      ns.emplace(c.second, p.second);
    }
    s = ns;
  }
  return cover;
}

void solve(int ncase) {
  cin >> n >> h;
  vs.resize(n);
  bool imp = false;
  for (int i = 0; i < n; i++) {
    vs[i].init();
    if (vs[i].a == 0 && vs[i].b == h) {
      imp = true;
    }
  }
  cout << "Case #" << ncase << ": ";
  if (imp) {
    cout << -1 << endl;
    return;
  }
  sort(vs.begin(), vs.end());

  init_max_flow();
  int s = n;
  int t = n + 1;
  for (int i = 0; i < n; i++) {
    auto cover = calc_cover(i + 1, n - 1, 1, i);
    for (auto &p : cover) {
      add_edge(i, p.first, p.second);
      add_edge(p.first, i, p.second);
    }
    if (vs[i].a == 0) add_edge(s, i, INF);
    if (vs[i].b == h) add_edge(i, t, INF);
  }
  int flow = max_flow(s, t);
  cout << (flow >= INF ? -1 : flow) << endl;
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
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  ios_base::sync_with_stdio(true);
  freopen("C:\\Users\\grain\\Desktop\\ladders_and_snakes_input.txt", "r", stdin);
  freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
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
