/**
* factorize,
* with special remaining prime.
* N <= 1e15
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
  return os << "(" << P.st << "," << P.nd << ")";
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
//const int mod = 1000000007;
const int mod = 998244353;
 
//const int N = 1e6 + 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
 
struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
 
ll D;
const int N = 100000 + 10;
int not_p[N], pl[N], np;
int d_p[N], nd_p;
ll left_p;
 
const int M = 128;
ll fact[M], inv_fact[M];
 
ll qpow(ll a, int b) {
  ll ans = 1;
  a = (a % mod + mod) % mod;
  for (; b; b >>= 1) {
    if (b & 1) ans = (a * ans) % mod;
    a = (a * a) % mod;
  }
  return ans;
}
void pre_calc() {
  for (int i = 2; i < N; i++) {
    if (not_p[i]) continue;
    pl[np++] = i;
    for (int j = i + i; j < N; j += i) {
      not_p[j] = 1;
    }
  }
  scanf("%lld", &D);
  ll x = D;
  for (int i = 0; i < np && pl[i] <= x; i++) {
    if (x % pl[i] == 0) {
      d_p[nd_p++] = pl[i];
      while (x % pl[i] == 0) x /= pl[i];
    }
  }
  left_p = 1;
  if (x > 1) {
    ll sqrt_x = sqrt(x + 0.1);
 
    if (sqrt_x * sqrt_x == x) {
      pl[nd_p++] = sqrt_x;
    } else {
      left_p = x;
    }
  }
  debug(left_p);
  fact[1] = 1;
  for (int i = 2; i < M; i++) {
    fact[i] = fact[i - 1] * i % mod;
  }
  inv_fact[M - 1] = qpow(fact[M - 1], mod - 2);
  for (int i = M - 2; i > 0; i--) {
    inv_fact[i] = inv_fact[i + 1] * (i + 1) % mod;
  }
}
 
vector<int> factorize(ll x) {
  ll z = x;
  vector<int> ret(nd_p);
  for (int i = 0; i < nd_p; i++) {
    while (z % d_p[i] == 0) {
      ret[i]++;
      z /= d_p[i];
    }
  }
  if (z > 1) {
    if (z == left_p) {
      ret.push_back(1);
    } else {
      ll y1 = z;
      ll y = left_p / z;
      if (y1 > y) swap(y1, y);
      //debug(y1, y);
      d_p[nd_p++] = y1;
 
      d_p[nd_p++] = y;
      if (y1 == z) {
        ret.push_back(1);
        ret.push_back(0);
      } else {
        ret.push_back(0);
        ret.push_back(1);
      }
      left_p = 1;
    }
  } else if (left_p > 1) {
    ret.push_back(0);
  }
  return ret;
}
 
ll f(vector<int> &v1) {
  int total = 0;
  for (auto x :v1)
    total += x;
  if (total == 0) return 1;
  ll ans = fact[total];
  for (auto x : v1) {
    if (x == 0) continue;
    ans = ans * inv_fact[x] % mod;
  }
  return ans;
}
 
ll calc(vector<int> &v1, vector<int> &v2) {
  vector<int> base(v1.size());
  for (int i = 0; i < v1.size(); i++) {
    base[i] = min(v1[i], v2[i]);
  }
  vector<int> a(v1.size());
  vector<int> b(v2.size());
  for (int i = 0; i < v1.size(); i++) {
    a[i] = v1[i] - base[i];
    b[i] = v2[i] - base[i];
  }
  return f(a) * f(b) % mod;
}
 
void solve(int ncase) {
  int q;
  scanf("%d", &q);
  while (q--) {
    ll u, v;
    scanf("%lld%lld", &u, &v);
    if (u > v) swap(u, v);
    auto v1 = factorize(u);
    auto v2 = factorize(v);
    if (v2.size() != v1.size()) {
      v1 = factorize(u);
    }
    debug(u, v, v1, v2);
    printf("%lld\n", calc(v1, v2));
  }
}
void solve_all_cases() {
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  pre_calc();
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
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
  auto start_time = clock();
#endif
  solve_all_cases();
//  test();
#ifdef _zzz_
  cout << (clock() - start_time) * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
#endif
}
