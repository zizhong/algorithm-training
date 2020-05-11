/**
* https://cometoj.com/contest/15/problem/I?problem_id=221
* Disjoint Set with tags.
* Tags is good to be delta. For each node, the sum on the path to root is the real value.
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
int n, m;
const int N = 2 * 1e5 + 10;
int pre[N];
int war[N];
int home[N];

void merge(int a, int b) {
  war[a]++;
  war[b]++;
  home[b]++;
  war[a] -= war[b];
  home[a] -= home[b];
  pre[a] = b;
}

PIP query(int x) {
  if (pre[x] < 0) {
    return PIP(war[x], PII(home[x], x));
  }
  PIP p = query(pre[x]);

  int r = p.second.second;
  war[x] += p.first;
  home[x] += p.second.first;
  war[x] -= war[r];
  home[x] -= home[r];
  pre[x] = r;
  return PIP(war[x] + war[r], PII(home[x] + home[r], p.second.second));
}

ll qpow(int x, int n) {
  ll tmp = x;
  ll ret = 1;
  while (n) {
    if (n & 1) {
      ret = (ret * tmp) % mod;
    }
    n /= 2;
    tmp = (tmp * tmp) % mod;
  }
  return ret;
}

int calc(int one, int two) {
  debug(one, two);
  ll ret = qpow(3, n - one - two);
  return qpow(2, two) * ret % mod;
}

void solve(int ncase) {
  scanf("%d%d", &n, &m);
  CLS(pre, -1);
  for (int i = 0; i < m; i++) {
    int t, x, y;
    scanf("%d", &t);
    if (t == 1) {
      scanf("%d%d", &x, &y);
      merge(y, x);
    } else {
      scanf("%d", &x);
      PIP p = query(x);
      printf("%d\n", calc(p.first - p.second.first, p.second.first));
    }
  }
}
void solve_all_cases() {
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
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
