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
const int mod = (1e9) + 7;
typedef ModInt<mod> mod_int;
constexpr int INF = 0x3f3f3f3f;
constexpr int N = 1e5 + 100;

vector<int> v[N];

struct node {
  int type;
  int k, l, r, c, x;
} s[N];

ll kData[1050];

struct Splay {
  static const int maxn = 1e3 + 100;

#define lson(x) spl[x].ch[0]
#define rson(x) spl[x].ch[1]

  struct node {
    int ch[2], siz, fa, rev;
    ll add, sum, val;
  } spl[maxn];

  int tot = 0, st[maxn];

  bool ident(int x, int f) {
    return rson(f) == x;
  }

  void connect(int x, int f, int s) {
    spl[f].ch[s] = x;
    spl[x].fa = f;
  }

  void push_up(int x) {
    spl[x].siz = 1;
    spl[x].sum = spl[x].val;
    if (lson(x)) spl[x].siz += spl[lson(x)].siz, spl[x].sum += spl[lson(x)].sum;
    if (rson(x)) spl[x].siz += spl[rson(x)].siz, spl[x].sum += spl[rson(x)].sum;
  }

  void revtag(int x) {
    if (not x) return;
    swap(lson(x), rson(x));
    spl[x].rev ^= 1;
  }

  void addtag(int x, int val) {
    if (not x) return;
    spl[x].val += val, spl[x].sum += val * spl[x].siz, spl[x].add += val;
  }

  void push_down(int x) {
    if (spl[x].rev) {
      if (lson(x)) revtag(lson(x));
      if (rson(x)) revtag(rson(x));
      spl[x].rev = 0;
    }
    if (spl[x].add) {
      if (lson(x)) addtag(lson(x), spl[x].add);
      if (rson(x)) addtag(rson(x), spl[x].add);
      spl[x].add = 0;
    }
  }

  void rotate(int x) {
    int f = spl[x].fa, ff = spl[f].fa, k = ident(x, f);
    connect(spl[x].ch[k ^ 1], f, k);
    connect(x, ff, ident(f, ff));
    connect(f, x, k ^ 1);
    push_up(f), push_up(x);
  }

  void splaying(int x, int to) {
    int y = x, top = 0;
    // push_down on all the nodes to the root.
    st[++top] = y;
    while (spl[y].fa) st[++top] = spl[y].fa, y = spl[y].fa;
    while (top) push_down(st[top--]); // ***
    while (spl[x].fa != to) {
      int f = spl[x].fa, ff = spl[f].fa;
      if (ff == to) rotate(x);
      else if (ident(x, f) == ident(f, ff)) rotate(f), rotate(x);
      else rotate(x), rotate(x);
    }
    push_up(x);// ***
  }

  int build(int fa, int l, int r) {
    if (l > r) return 0;
    int mid = l + r >> 1;
    int now = ++tot;
    spl[now].val = kData[mid], spl[now].fa = fa, spl[now].rev = spl[now].add = 0;
    lson(now) = build(now, l, mid - 1);
    rson(now) = build(now, mid + 1, r);
    push_up(now);
    return now;
  }

  int arank(int x) {
    int now = spl[0].ch[1];
    while (true) {
      push_down(now); // *
      int sum = spl[lson(now)].siz + 1;
      if (x == sum) return now;
      if (sum > x) now = lson(now);
      else {
        x -= sum;
        now = rson(now);
      }
    }
  }

  int locate_range(int l, int r) {
    l = arank(l), r = arank(r + 2);
    splaying(l, 0);
    splaying(r, l);
    return lson(r);
  }
  void turn(int l, int r) {
    revtag(locate_range(l, r));
  }

  void add(int l, int r, ll val) {
    addtag(locate_range(l, r), val);
  }

  ll query(int l, int r) {
    return spl[locate_range(l, r)].sum;
  }

  void print(int node) {
    push_down(node);
    if (lson(node)) print(lson(node));
    if (node and spl[node].val != INF and spl[node].val != -INF) cout << spl[node].val << " ";
    if (rson(node)) print(rson(node));
  }

} tree[1050];

map<int, ll> ans;

int vis[N];

void dfs(int node, int fa) {
  int type = s[node].type;
  if (type == 1) {
    tree[s[node].k].turn(s[node].l, s[node].r);
  } else if (type == 2) {
    tree[s[node].k].add(s[node].l, s[node].r, s[node].c);
  } else if (type == 3) {
    ans[node] = tree[s[node].k].query(s[node].l, s[node].r);
  }

  for (auto to : v[node]) {
    if (to == fa) continue;
    dfs(to, node);
  }

  if (type == 1) {
    tree[s[node].k].turn(s[node].l, s[node].r);
  } else if (type == 2) {
    tree[s[node].k].add(s[node].l, s[node].r, -s[node].c);
  }
}

void solve(int ncase) {
  int n = ri(), m = ri(), q = ri();
  kData[1] = -INF, kData[m + 2] = INF;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      kData[j + 1] = rl();
    }
    tree[i].spl[0].ch[1] = tree[i].build(0, 1, m + 2);
  }

  for (int i = 1; i <= q; ++i) {
    int type = ri();
    if (type == 1 or type == 3) {
      s[i].k = ri(), s[i].l = ri(), s[i].r = ri();
    } else if (type == 2) {
      s[i].k = ri(), s[i].l = ri(), s[i].r = ri(), s[i].c = ri();
    } else if (type == 4) {
      s[i].x = ri();
    }

    s[i].type = type;

    if (type == 4) v[s[i].x].emplace_back(i), v[i].emplace_back(s[i].x);
    else if (i - 1 > 0) v[i].emplace_back(i - 1), v[i - 1].emplace_back(i);
  }

  dfs(1, 0);

  for (auto k : ans) {
    printf("%lld\n", k.second);
  }

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
  cout.tie(0);
  cout << std::fixed;
  cout << setprecision(2);
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
  cout << (clock() - start_time) * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
#endif
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/
