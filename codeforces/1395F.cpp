// Trinary search
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
int n;
vector<PII> v;
int max_x, max_y;
int calc(int x1, int y1, int x2, int y2) {
  int dx = x1 - x2;
  int dy = y1 - y2;
  if (dx > 0 && dy < 0 || dx < 0 && dy > 0) {
    return abs(dx - dy);
  }
  return max(abs(dx), abs(dy));
}

int max_dist(int x, int y) {
  int ans = 0;
  for (auto p : v) {
    ans = max(ans, calc(p.first, p.second, x, y));
  }
  return ans;
}
PII min_dist(int y) {
  int xl = (y == 0 ? 1 : 0), xr = max_x;
  while (xl + 2 < xr) {
    int mid1 = (2 * xl + xr) / 3;
    int mid2 = (xl + 2 * xr) / 3;
    if (max_dist(mid1, y) < max_dist(mid2, y)) xr = mid2;
    else xl = mid1;
  }
  int ans1 = 5 * 100000 + 10;
  int x;
  for (int i = xl; i <= xr; i++) {
    int tmp = max_dist(i, y);
    if (tmp < ans1) {
      ans1 = tmp;
      x = i;
    }
  }
  return {ans1, x};
}
void solve(int ncase) {
  cin >> n;
  v.resize(n);
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    int a[2] = {0};
    for (auto c : s) {
      a[c == 'B']++;
    }
    v[i] = {a[0], a[1]};
    max_x = max(max_x, a[0]);
    max_y = max(max_y, a[1]);
  }
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  int yl = 0, yr = max_y;
  while (yl + 2 < yr) {
    int mid1 = (2 * yl + yr) / 3;
    int mid2 = (yl + 2 * yr) / 3;
    if (min_dist(mid1).first < min_dist(mid2).first) yr = mid2;
    else yl = mid1;
  }
  int ans1 = 5 * 100000 + 10;
  PII p;
  for (int y = yl; y <= yr; y++) {
    PII tmp = min_dist(y);
    if (tmp.first < ans1) {
      ans1 = tmp.first;
      p = PII(tmp.second, y);
    }
  }
  string ret(p.first + p.second, 'B');
  for (int i = 0; i < p.first; i++) ret[i] = 'N';

  cout << ans1 << endl << ret << endl;
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
  cout << setprecision(6);
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
