/**
* mex[0] all path doesn't have 0. which is all in the subtree of children of 0.
* mex[1] = tot - mex[0] - mex[2...]
* ...
* mex[i] = tot - mex[0...i-1] - mex[i+1...]
*  mex[0...i-1] is already calculated.
*  mex[i+1...] is for the current chain, number of nodes on one end * number of nodes on the other end.
* 
* Node 0 is special when we maintain the chain, since it's the ancestor of all others. 
* (Especially, we need to exclude the case where lca(1, 2) != 0.
* 
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
#include <complex>

#define __builtin_sprintf
//#include <bits/extc++.h>
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
const double pi = std::acos(-1.0);
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

template<class K, class V>
ostream &operator<<(ostream &os, unordered_map<K, V> m) {
  os << "[";
  for (auto p : m) os << "(" << p.first << ", " << p.second << "), ";
  return os << "]";
}
template<class K, class V>
ostream &operator<<(ostream &os, map<K, V> m) {
  os << "[";
  for (auto p : m) os << "(" << p.first << ", " << p.second << "), ";
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

struct Fraction {
  // a/b
  ll a, b;

  Fraction() : a(0), b(1) {};

  Fraction(int a_, int b_) : a(a_), b(b_) {
    if (a == 0) {
      b = 1;
      return;
    }
    if (b == 0) {
      a = 1;
      return;
    }
    if (b < 0) {
      b = -b;
      a = -a;
    }
    ll d = gcd(a, b);
    a /= d;
    b /= d;
  };

  bool operator<(const Fraction &rhs) const {
    return a * rhs.b < rhs.a * b;
  }

  bool operator==(const Fraction &rhs) const {
    return a == rhs.a && b == rhs.b;
  }

  void dd() {
    //debug(a, b);
  }
};

void update(ll &v, ll nv) {
  if (v < 0 || nv >= 0 && v > nv) v = nv;
}

void update_max(int &v, int nv) {
  v = max(v, nv);
}

void pre_calc() {

}

struct Point {
  int x, y;
  void init() {
    cin >> x >> y;
  }
};

const int N = 200043;
const int L = 20;

vector<int> g[N];
int p[N];
int up[N][L];
int tin[N];
int tout[N];
int T = 0;
int n;

int cnt[N];

void dfs(int u, int fa) {
  tin[u] = T++;
  p[u] = fa;
  up[u][0] = fa;
  cnt[u]++;
  for (int i = 1; i < L; i++)
    up[u][i] = up[up[u][i - 1]][i - 1];
  for (auto v : g[u]) {
    if (v == fa) continue;
    dfs(v, u);
    cnt[u] += cnt[v];
  }
  tout[u] = T++;
}
// if x is ancestor of y
bool is_ancestor(int x, int y) {
  return tin[x] <= tin[y] && tout[x] >= tout[y];
}

int lca(int x, int y) {
  if (is_ancestor(x, y))
    return x;
  for (int i = L - 1; i >= 0; i--)
    if (!is_ancestor(up[x][i], y))
      x = up[x][i];
  return p[x];
}

void solve(int ncase) {
  cin >> n;
  for (int i = 0; i < n; i++) {
    g[i].clear();
    cnt[i] = 0;
  }
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  T = 0;
  dfs(0, 0);
  vector<ll> mex(n + 1);
  ll tot = n * 1LL * (n - 1) / 2;
  for (auto v : g[0]) {
    if (v == p[0]) continue;
    mex[0] += cnt[v] * 1LL * (cnt[v] - 1) / 2;

  }
  vector<int> chain(1, 0);
  vector<ll> ed(1, n);
  for (int i = 1; i <= n; i++) {
    tot -= mex[i - 1];
    if (i == n) {
      mex[i] = tot;
      break;
    }
    // calculate mex[i+]

    // case 1: 0
    // case 2: 0 ch
    // case 3: ch1 ch2
    if (chain.size() == 1) {
      for (auto v : g[0]) {
        if (v == p[0]) continue;
        if (is_ancestor(v, 1)) {
          ed[0] -= cnt[v];
          break;
        }
      }
      chain.push_back(1);
      ed.push_back(cnt[1]);
      ll mex_more = ed[0] * ed[1];
      mex[i] = tot - mex_more;
      continue;
    }
    bool in_chain = false;
    for (int j = chain.size() - 1; j >= 0; j--) {
      ll a = lca(i, chain[j]);
      if (a == chain[j]) {
        chain[j] = i;
        ed[j] = cnt[i];
        in_chain = true;
        break;
      }
      if (a == i) {
        in_chain = true;
        break;
      }
      if (chain[0] == 0 && j == 1 && a != 0) {
        break;
      }
    }
    if (!in_chain) {
      mex[i] = tot;
      tot = 0;
      break;
    }
    mex[i] = tot - ed[0] * ed[1];
  }
  for (int i = 0; i <= n; i++) {
    cout << mex[i] << " \n"[i == n];
  }
}

void solve_all_cases() {
  int T = 1;
  // scanf("%d", &T);
  cin >> T;
  //debug(T);
  //T = ri();
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
  freopen("C:\\Users\\grain\\CLionProjects\\Contest\\input\\in.txt", "r", stdin);
  //freopen("C:\\Users\\grain\\Desktop\\weak_typing_chapter_1_input.txt", "r", stdin);
  auto x = freopen("C:\\Users\\grain\\CLionProjects\\Contest\\output\\out.txt", "w", stdout);
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
