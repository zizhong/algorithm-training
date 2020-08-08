/**
* double type Line Container
* min hull and max hull
* if endpoint is the same, need to consider it too.
* to bybass the d1 == d2, need to add eps add appropriate ends
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
const int N = 2 * int(1e5) + 10;

// from: https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/LineContainer.h\
//  at least c++14
// Line : y = k * x + m. p is the x coordination of the intersection with the next line in the container.
struct Line {
  mutable double k, m, p;
  bool operator<(const Line &o) const { return k < o.k; }
  bool operator<(double x) const { return p < x; }
};

// Add(k, m) : insert y = k * x + m to the container
// Query(x) : returns the maximum y at x.
// isect(x, y): calculate x.p and if x.p >= y.p, it means y can be removed.
// To query minimum, need to insert -k and -m, which is basically making symmetric by x axis.
struct LineContainer : multiset<Line, less<>> {
 private:
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  const double inf = 1 / .0;
  double div(double a, double b) { // floored division
    return a / b;
    //return a / b - ((a ^ b) < 0 && a % b);
  }
  bool isect(iterator x, iterator y) {
    if (y == end()) {
      x->p = inf;
      return false;
    }
    if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
    else x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
 public:
  void add(double k, double m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  double query(double x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};

int n;
struct Seg {
  int x1, x2, y;
  void init() {
    scanf("%d%d%d", &x1, &x2, &y);
  }
  bool operator<(const Seg &rhs) const {
    return y < rhs.y;
  }
};

double calc_k(double x1, double y1, double x2, double y2) {
  return (x1 - x2) / (y2 - y1);
}

void solve(int ncase) {
  int n;
  scanf("%d", &n);
  vector<Seg> vs(n);
  for (int i = 0; i < n; i++) {
    vs[i].init();
  }
  sort(vs.begin(), vs.end());
  vector<PDD> s;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (vs[i].y == vs[j].y) continue;
      double a = calc_k(vs[j].x1, vs[j].y, vs[i].x2, vs[i].y);
      double b = calc_k(vs[j].x2, vs[j].y, vs[i].x1, vs[i].y);
      if (a > b) swap(a, b);
      s.emplace_back(a, b);
    }
  }
  if (s.size() == 0) {
    double l = vs[0].x1;
    double r = vs[0].x2;
    for (auto &seg : vs) {
      l = min((double) seg.x1, l);
      r = max((double) seg.x2, r);
    }
    printf("%.15lf\n", r - l);
    return;
  }
  LineContainer max_hull, min_hull;
  for (int i = 0; i < n; i++) {
    max_hull.add(vs[i].y, vs[i].x2);
    //max_hull.add(vs[i].y, vs[i].x1);
    min_hull.add(-vs[i].y, -vs[i].x1);
    //min_hull.add(-vs[i].y, -vs[i].x2);
  }
  sort(s.begin(), s.end());
  vector<PDD> z;
  for (auto &p : s) {
    if (z.empty() || z.back().second < p.first + 1e-8) {
      z.push_back(p);
    } else {
      z.back().second = max(z.back().second, p.second);
    }
  }
  double ans = 1 / .0;
  for (auto &p : z) {
    //debug(p.first, max_hull.query(p.first), min_hull.query(p.first));
    //debug(p.second, max_hull.query(p.second), min_hull.query(p.second));
    ans = min(ans, max_hull.query(p.first) + min_hull.query(p.first));
    ans = min(ans, max_hull.query(p.second) + min_hull.query(p.second));
  }
  printf("%.15lf\n", ans);
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
  //ios_base::sync_with_stdio(0);
  //cin.tie(0);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  ios_base::sync_with_stdio(true);
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
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
