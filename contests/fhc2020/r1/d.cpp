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
const int mod = 1e9 + 7;
//const int N = 1e6 + 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

const int N = 1000000 + 10;
string s;
int n, K;
int edge[N];
void gen_edge() {
  ll a, b, c;
  cin >> a >> b >> c;
  for (int i = K + 2; i <= n; i++) {
    edge[i] = (a * edge[i - 2] + b * edge[i - 1] + c) % (i - 1) + 1;
  }
}
int is_covid(int idx) { return s[idx - 1] == '#'; }
vector<vector<int>> t1;

vector<int> group;
int group_idx;
void dfs_group(int u) {
  group[u] = group_idx;
  for (auto v : t1[u]) {
    if (is_covid(v) || group[v]) continue;
    dfs_group(v);
  }
}

vector<vector<int>> tree;
vector<int> safe_size;
int tn;
void new_tree() {
  tn = group_idx;
  tree.assign(tn + 1, vector<int>());
  safe_size.assign(tn + 1, 0);
  for (int i = 1; i <= n; i++) {
    if (is_covid(i)) continue;
    safe_size[group[i]]++;
  }
  set<PII> edge_set;
  for (int i = 1; i <= n; i++) {
    for (auto v : t1[i]) {
      if (group[i] == group[v]) continue;
      edge_set.emplace(group[i], group[v]);
    }
  }
  for (auto p : edge_set) {
    tree[p.first].push_back(p.second);
  }
}

vector<ll> ans_in_group;
vector<int> vst;
// return subtree size
int dfs_ans_in_group(int u, int pre) {
  int ret = 1;
  vst[u] = 1;
  vector<int> v_sz;
  for (auto v : t1[u]) {
    if (group[v] == group[u] && !vst[v]) {
      int sz = dfs_ans_in_group(v, u);
      ret += sz;
      v_sz.push_back(sz);
    }
  }
  for (auto x : v_sz) {
    ans_in_group[group[u]] += x * 1LL * (safe_size[group[u]] - x);
  }
  return ret;
}

struct State {
  int tree_size = 0;
  map<int, int> max_safe;
};
vector<State> vs;

void dfs_state(int u, int pre) {
  State &st = vs[u];
  st.tree_size = safe_size[u] ? safe_size[u] : 1;
  if (safe_size[u]) st.max_safe[safe_size[u]] = 1;
  for (auto v : tree[u]) {
    if (v == pre) continue;
    dfs_state(v, u);
    st.tree_size += vs[v].tree_size;
    for (auto p : vs[v].max_safe) {
      st.max_safe[p.first] += p.second;
    }
    while (st.max_safe.size() > 2) {
      st.max_safe.erase(st.max_safe.begin());
    }
  }
}

struct DPState {
  ll f = 0;
  ll cnt = 0;
};
vector<DPState> dp;

void change_state(int u, int v, int flag) {
  vs[u].tree_size += vs[v].tree_size * flag;
  for (auto p : vs[v].max_safe) {
    if (flag > 0) {
      vs[u].max_safe[p.first] += p.second;
    } else {
      if (vs[u].max_safe.count(p.first)) {
        vs[u].max_safe[p.first] -= p.second;
        if (vs[u].max_safe[p.first] == 0) vs[u].max_safe.erase(p.first);
      }
    }
  }
}

void disconnect(int u, int v) {
  change_state(u, v, -1);
}
void connect(int u, int v) {
  change_state(u, v, 1);
}

void update(DPState &dp_state, ll f, ll cnt) {
  if (dp_state.f == f) dp_state.cnt += cnt;
  else if (dp_state.f < f) {
    dp_state.f = f;
    dp_state.cnt = cnt;
  }
}
void dfs_dp(int u, int pre) {
  for (auto v : tree[u]) {
    if (v == pre) continue;
    disconnect(u, v);
    if (vs[u].max_safe.empty() || vs[v].max_safe.empty()) {
      update(dp[u], 0, vs[u].tree_size * 1LL * vs[v].tree_size);
    } else {
      auto it = vs[u].max_safe.rbegin();
      auto it2 = vs[v].max_safe.rbegin();
      update(dp[u], it->first * 1LL * it2->first, it->first * 1LL * it->second * 1LL * it2->first * 1LL * it2->second);
    }
    connect(u, v);
  }
  for (auto v : tree[u]) {
    if (v == pre) continue;
    disconnect(u, v);
    connect(v, u);
    dfs_dp(v, u);
    disconnect(v, u);
    connect(u, v);
  }
}

void solve(int ncase) {
  cin >> n >> K;
  cin >> s;
  for (int i = 2; i <= K + 1; i++) {
    cin >> edge[i];
  }
  gen_edge();
  t1.assign(n + 1, vector<int>());
  for (int i = 2; i <= n; i++) {
    t1[i].push_back(edge[i]);
    t1[edge[i]].push_back(i);
  }

  group.assign(n + 1, 0);
  group_idx = 0;
  for (int i = 1; i <= n; i++) {
    if (is_covid(i) || group[i] > 0) continue;
    group_idx++;
    dfs_group(i);
  }

  int ngroup_idx = group_idx;
  for (int i = 1; i <= n; i++) {
    if (is_covid(i)) group[i] = ++group_idx;
  }
  new_tree();
  ans_in_group.assign(group_idx + 1, 0);
  vst.assign(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    if (group[i] && !vst[i]) {
      dfs_ans_in_group(i, -1);
    }
  }
  vs.assign(tn + 1, State());
  dfs_state(1, -1);
  /* for (int i = 1; i <= tn; i++) {
     debug(i);
     for (auto p : vs[i].max_safe) debug(p.first, p.second);
     debug(vs[i].tree_size);
   }*/
  dp.assign(tn + 1, DPState());
  dfs_dp(1, -1);
  ll base = 0;
  for (auto x : safe_size) {
    if (x > 1) base += x * 1LL * (x - 1) / 2;
  }
  cout << "Case #" << ncase << ": ";
  if (ngroup_idx == 1) {
    ll way = ans_in_group[1];
    //debug(way);
    for (auto &dps : dp) {
      way += dps.cnt;
    }
    cout << base << " " << way << endl;
    return;
  }
  DPState dp_max;
  for (int i = 1; i <= tn; i++) {
    auto &dps = dp[i];
    //debug(i, dps.f, dps.cnt);
    if (dp_max.f == dps.f) dp_max.cnt += dps.cnt;
    else if (dp_max.f < dps.f) {
      dp_max = dps;
    }
  }
  cout << base + dp_max.f << " " << dp_max.cnt << endl;
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
  cout << setprecision(6);
#ifdef _zzz_
  //ios_base::sync_with_stdio(true);
  freopen("C:\\Users\\grain\\Desktop\\quarantine_input.txt", "r", stdin);
  auto x = freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
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