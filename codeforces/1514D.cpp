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

const unsigned int mod = 998244353;
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

const int d[][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

void update(int &v, int nv) {
  if (v < 0 || nv >= 0 && v > nv) v = nv;
}
void update_max(int &v, int nv) {
  v = max(v, nv);
}

void pre_calc() {
}

struct TreeNode {
  int l, r, sum;
};
struct PersistentSegmentTree {
  vector<TreeNode> v;
  vector<int> root;
  int cnt = 0;
  PersistentSegmentTree(int n) {
    v.assign(40 * n, TreeNode());
    root.assign(n + 1, 0);
  }
  void insert(int l, int r, int pre, int &now, int x) {
    now = ++cnt;
    v[now] = v[pre];
    v[now].sum++;
    if (l == r) return;
    int mid = (l + r) / 2;
    if (x <= mid) {
      insert(l, mid, v[pre].l, v[now].l, x);
    } else {
      insert(mid + 1, r, v[pre].r, v[now].r, x);
    }
  }
  int query(int l, int r, int pre, int now, int x) {
    //debug(l, r, v[v[now].l].sum, v[v[pre].l].sum, v[v[now].r].sum, v[v[pre].r].sum);
    if (l == r) {
      if (v[now].sum - v[pre].sum < x) return -1;
      return v[now].sum - v[pre].sum;
    }
    int mid = (l + r) / 2;
    int sumR = v[v[now].r].sum - v[v[pre].r].sum;
    int ret = -1;
    if (sumR >= x) {
      ret = query(mid + 1, r, v[pre].r, v[now].r, x);
    }
    if (ret == -1) {
      ret = query(l, mid, v[pre].l, v[now].l, x);
    }
    return ret;
  }
};

void solve(int ncase) {
  int n = ri(), m = ri();
  PersistentSegmentTree pst(n);
  for (int i = 0; i < n; i++) {
    int x = ri();
    pst.insert(1, n, pst.root[i], pst.root[i + 1], x);
  }
  while (m--) {
    int l = ri(), r = ri();
    int x = (r - l + 2) / 2;
    int ret = pst.query(1, n, pst.root[l - 1], pst.root[r], x);
    debug(ret);
    printf("%d\n", max(1, ret + ret - (r - l + 1)));
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
  ios_base::sync_with_stdio(1);
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
