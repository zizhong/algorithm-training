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

struct Node {
  int start = -1;
  int length = 0;
  int left = -1;
  int right = -1;
  void clear() {
    start = -1;
    length = 0;
  }
  void init(int st) {
    start = st;
    length = 1;
  }
};
const int N = 5 * 100000 + 10;
char s[N];

int n;
ll in(int x) {
  x++;
  return (x - 1) * 1LL * x * (x + 1) / 6;
}

ll sum_a_to_b(int a, int b) {
  if (a > b) return 0;
  ll len = b - a + 1;
  return len * (a + b) / 2;
}

ll square_sum(int x) {
  return x * 1LL * (x + 1) * (2 * x + 1) / 6;
}

ll calc_trapezoid(int a, int b, int base) {
  debug(a, b, base);
  return sum_a_to_b(a, b) * base + sum_a_to_b(0, b - a) * a + square_sum(b - a);
}
void solve(int ncase) {
  scanf("%d%s", &n, s);
  vector<Node> vn;
  Node tmp;
  for (int i = 0; i < n; i++) {
    if (s[i] == '0') {
      if (tmp.length > 0) {
        vn.push_back(tmp);
        tmp.clear();
      }
      continue;
    }
    if (tmp.length > 0) {
      tmp.length++;
    } else {
      tmp.init(i);
    }
  }
  if (tmp.length) {
    vn.push_back(tmp);
  }
  stack<int> left_i;
  ll ret = 0;
  for (int i = 0; i < vn.size(); i++) {
    int pre = 0;
    while (!left_i.empty() && vn[left_i.top()].length <= vn[i].length) {
      if (pre < vn[left_i.top()].length - 1) {
        ret += calc_trapezoid(vn[i].start - (vn[left_i.top()].start + vn[left_i.top()].length - pre - 1),
                              vn[i].start - vn[left_i.top()].start - 1, pre + 1);
        pre = vn[left_i.top()].length - 1;
      }
      left_i.pop();
    }
    debug(i, ret);
    if (left_i.empty()) {
      vn[i].left = 0;
      ret += sum_a_to_b(pre + 1, vn[i].length) * vn[i].start;
    } else {
      vn[i].left = vn[left_i.top()].start + vn[left_i.top()].length - vn[i].length;
      ret += calc_trapezoid(vn[i].start - (vn[left_i.top()].start + vn[left_i.top()].length - pre - 1),
                            vn[i].start - (vn[left_i.top()].start + vn[left_i.top()].length - vn[i].length), pre + 1);
    }
    left_i.push(i);
    debug("left", i, ret);
  }
  stack<int> right_i;
  for (int i = vn.size() - 1; i >= 0; i--) {
    int pre = 0;
    while (!right_i.empty() && vn[right_i.top()].length < vn[i].length) {
      if (pre < vn[right_i.top()].length) {
        ret += calc_trapezoid(vn[right_i.top()].start + (pre + 1) - 1 - (vn[i].start + vn[i].length),
                              vn[right_i.top()].start + vn[right_i.top()].length - 1 - (vn[i].start + vn[i].length),
                              pre + 1);
        pre = vn[right_i.top()].length;
      }
      right_i.pop();
    }
    debug(i, ret);
    if (right_i.empty()) {
      vn[i].right = n - 1;
      ret += sum_a_to_b(pre + 1, vn[i].length) * (n - 1
          - (vn[i].start + vn[i].length - 1));
      //(n - 1 - (vn[i].start + vn[i].length - 1)) * 1LL * (vn[i].length - pre);
    } else {
      vn[i].right = vn[right_i.top()].start - 2 + vn[i].length;
      ret += calc_trapezoid(vn[right_i.top()].start + (pre + 1) - 1 - (vn[i].start + vn[i].length),
                            vn[right_i.top()].start + vn[i].length - 1 - (vn[i].start + vn[i].length),
                            pre + 1);
    }
    right_i.push(i);
    debug("right", i, ret);
  }
  for (auto &node : vn) {
    debug(node.length,
          node.start,
          node.left,
          node.right,
          in(node.length),
          node.length * 1LL * (node.start - node.left) * 1LL * (node.right - (node.start + node.length - 1)));
    ret += in(node.length)
        + node.length * 1LL * (node.start - node.left) * 1LL * (node.right - (node.start + node.length - 1));
  }
  printf("%I64d\n", ret);
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
