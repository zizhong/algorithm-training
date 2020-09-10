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

// from https://codeforces.com/contest/1398/submission/89946268
// FFT library : multiply two polynomials in O(NlogN)

constexpr int P = 998244353;
std::vector<int> rev, roots{0, 1};
int power(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % P)
    if (b & 1)
      res = 1ll * res * a % P;
  return res;
}

// DFT: change a polynomial from coefficient form to point value form
void dft(std::vector<int> &a) {
  int n = a.size();
  if (int(rev.size()) != n) {
    int k = __builtin_ctz(n) - 1;
    rev.resize(n);
    for (int i = 0; i < n; ++i)
      rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
  }
  for (int i = 0; i < n; ++i)
    if (rev[i] < i)
      std::swap(a[i], a[rev[i]]);
  if (int(roots.size()) < n) {
    int k = __builtin_ctz(roots.size());
    roots.resize(n);
    while ((1 << k) < n) {
      int e = power(3, (P - 1) >> (k + 1));
      for (int i = 1 << (k - 1); i < (1 << k); ++i) {
        roots[2 * i] = roots[i];
        roots[2 * i + 1] = 1ll * roots[i] * e % P;
      }
      ++k;
    }
  }
  for (int k = 1; k < n; k *= 2) {
    for (int i = 0; i < n; i += 2 * k) {
      for (int j = 0; j < k; ++j) {
        int u = a[i + j];
        int v = 1ll * a[i + j + k] * roots[k + j] % P;
        int x = u + v;
        if (x >= P)
          x -= P;
        a[i + j] = x;
        x = u - v;
        if (x < 0)
          x += P;
        a[i + j + k] = x;
      }
    }
  }
}

// IDFT: change a polynomial back to coefficient form from point value form
void idft(std::vector<int> &a) {
  int n = a.size();
  std::reverse(a.begin() + 1, a.end());
  dft(a);
  int inv = power(n, P - 2);
  for (int i = 0; i < n; ++i)
    a[i] = 1ll * a[i] * inv % P;
}

struct Poly {
  std::vector<int> a;
  Poly() {}
  Poly(int a0) {
    if (a0)
      a = {a0};
  }
  Poly(const std::vector<int> &a1) : a(a1) {
    while (!a.empty() && !a.back())
      a.pop_back();
  }
  int size() const {
    return a.size();
  }
  int operator[](int idx) const {
    if (idx < 0 || idx >= size())
      return 0;
    return a[idx];
  }
  // multiply x^k = inserting k 0 to the beginning of the the coefficient form
  Poly mulxk(int k) const {
    auto b = a;
    b.insert(b.begin(), k, 0);
    return Poly(b);
  }
  // module x^k = removing any coefficient after x^k
  Poly modxk(int k) const {
    k = std::min(k, size());
    return Poly(std::vector<int>(a.begin(), a.begin() + k));
  }
  // divided by x^k = removing first k coefficients
  Poly divxk(int k) const {
    if (size() <= k)
      return Poly();
    return Poly(std::vector<int>(a.begin() + k, a.end()));
  }

  friend Poly operator+(const Poly a, const Poly &b) {
    std::vector<int> res(std::max(a.size(), b.size()));
    for (int i = 0; i < int(res.size()); ++i) {
      res[i] = a[i] + b[i];
      if (res[i] >= P)
        res[i] -= P;
    }
    return Poly(res);
  }

  friend Poly operator-(const Poly a, const Poly &b) {
    std::vector<int> res(std::max(a.size(), b.size()));
    for (int i = 0; i < int(res.size()); ++i) {
      res[i] = a[i] - b[i];
      if (res[i] < 0)
        res[i] += P;
    }
    return Poly(res);
  }

  friend Poly operator*(Poly a, Poly b) {
    int sz = 1, tot = a.size() + b.size() - 1;
    while (sz < tot)
      sz *= 2;
    a.a.resize(sz);
    b.a.resize(sz);
    dft(a.a);
    dft(b.a);
    for (int i = 0; i < sz; ++i)
      a.a[i] = 1ll * a[i] * b[i] % P;
    idft(a.a);
    return Poly(a.a);
  }
  Poly &operator+=(Poly b) {
    return (*this) = (*this) + b;
  }
  Poly &operator-=(Poly b) {
    return (*this) = (*this) - b;
  }
  Poly &operator*=(Poly b) {
    return (*this) = (*this) * b;
  }
  Poly deriv() const {
    if (a.empty())
      return Poly();
    std::vector<int> res(size() - 1);
    for (int i = 0; i < size() - 1; ++i)
      res[i] = 1ll * (i + 1) * a[i + 1] % P;
    return Poly(res);
  }
  Poly integr() const {
    if (a.empty())
      return Poly();
    std::vector<int> res(size() + 1);
    for (int i = 0; i < size(); ++i)
      res[i + 1] = 1ll * a[i] * power(i + 1, P - 2) % P;
    return Poly(res);
  }
  Poly inv(int m) const {
    Poly x(power(a[0], P - 2));
    int k = 1;
    while (k < m) {
      k *= 2;
      x = (x * (2 - modxk(k) * x)).modxk(k);
    }
    return x.modxk(m);
  }
  Poly log(int m) const {
    return (deriv() * inv(m)).integr().modxk(m);
  }
  Poly exp(int m) const {
    Poly x(1);
    int k = 1;
    while (k < m) {
      k *= 2;
      x = (x * (1 - x.log(k) + modxk(k))).modxk(k);
    }
    return x.modxk(m);
  }
  Poly mulT(Poly b) const {
    if (b.size() == 0)
      return Poly();
    int n = b.size();
    std::reverse(b.a.begin(), b.a.end());
    return ((*this) * b).divxk(n - 1);
  }
  std::vector<int> eval(std::vector<int> x) const {
    if (size() == 0)
      return std::vector<int>(x.size(), 0);
    const int n = std::max(int(x.size()), size());
    std::vector<Poly> q(4 * n);
    std::vector<int> ans(x.size());
    x.resize(n);
    std::function<void(int, int, int)> build = [&](int p, int l, int r) {
      if (r - l == 1) {
        q[p] = std::vector<int>{1, (P - x[l]) % P};
      } else {
        int m = (l + r) / 2;
        build(2 * p, l, m);
        build(2 * p + 1, m, r);
        q[p] = q[2 * p] * q[2 * p + 1];
      }
    };
    build(1, 0, n);
    std::function<void(int, int, int, const Poly &)> work = [&](int p, int l, int r, const Poly &num) {
      if (r - l == 1) {
        if (l < int(ans.size()))
          ans[l] = num[0];
      } else {
        int m = (l + r) / 2;
        work(2 * p, l, m, num.mulT(q[2 * p + 1]).modxk(m - l));
        work(2 * p + 1, m, r, num.mulT(q[2 * p]).modxk(r - m));
      }
    };
    work(1, 0, n, mulT(q[1].inv(n)));
    return ans;
  }
};

void solve(int ncase) {
  int n, x, y;
  cin >> n >> x >> y;
  vector<int> a(x + 1);
  vector<int> b(x + 1);
  for (int i = 0; i <= n; i++) {
    int z;
    cin >> z;
    a[z] = 1;
    b[x - z] = 1;
  }
  auto f = Poly(a) * Poly(b);
  const int N = 5e5 + 10;
  vector<int> dp(N, -1);
  for (int i = x + 1; i < f.a.size(); i++) {
    if (f.a[i]) {
      dp[i - x + y] = (i - x + y) * 2;
    }
  }
  for (int i = 1; i < N; i++) {
    if (dp[i] >= 0) {
      for (int j = i + i; j < N; j += i) {
        dp[j] = max(dp[j], dp[i]);
      }
    }
  }
  int q;
  cin >> q;
  while (q--) {
    int l;
    cin >> l;
    cout << dp[l / 2] << " \n"[q > 0 ? 0 : 1];
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
  cout << std::fixed;
  cout << setprecision(9);
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
  //cout << (clock() - start_time) * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
#endif
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/
