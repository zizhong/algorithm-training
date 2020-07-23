/**
* Math.
* Find rules and formula
* Could use brute force to replace some math work.
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
bool is_power_of_2(int n) {
  return (n & (n - 1)) == 0;
}
 
bool can(int n, int k) {
  if (n % 2 == 0 || k > max(0, (n - 3) / 2)) {
    return false;
  }
  if (is_power_of_2(n + 1)) {
    if (k == 1) {
      return false;
    }
  } else {
    if (k == 0) {
      return false;
    }
  }
  return !(n == 9 && k == 2);
}
void solve(int ncase) {
  int n, k;
  scanf("%d%d", &n, &k);
  if (!can(n, k)) {
    puts("NO");
    return;
  }
  puts("YES");
  vector<int> p(n + 1);
  int idx = 1;
  int sub_root = 0;
  while (k > 1) {
    // left = 1
    if (can(n + 1 - idx - 2, k - 1)) {
      p[idx] = sub_root;
      p[idx + 1] = idx;
      sub_root = idx;
      idx += 2;
    } else {
      // left = 3
      p[idx] = sub_root;
      p[idx + 1] = idx;
      p[idx + 2] = p[idx + 3] = idx + 1;
      sub_root = idx;
      idx += 4;
    }
    k--;
  }
  int left = n + 1 - idx;
  if (left == 1) {
    p[idx] = sub_root;
  } else if (left == 3) {
    p[idx] = sub_root;
    p[idx + 1] = p[idx + 2] = idx;
  } else {
    int m = 0;
    while ((1 << m) < left) m++;
    m--;
    int left_sub = (1 << m) - 1;
    int right_sub = left - 1 - left_sub;
    if (k == 1 && left_sub > right_sub * 2) {
      m--;
      left_sub = (1 << m) - 1;
      right_sub = left - 1 - left_sub;
    }
    debug(left_sub, right_sub);
    p[idx] = sub_root;
    p[idx + 1] = idx;
    // [idx + 1, .. idx + left_sub] => left tree with root p as idx
    for (int i = 2; i <= left_sub; i++) {
      p[i + idx] = idx + i / 2;
    }
    //[idx + left_sub + 1, ..] => right tree with root p as idx;
    p[idx + left_sub + 1] = idx;
    for (int i = 2; idx + left_sub + i <= n; i++) {
      p[idx + left_sub + i] = idx + left_sub + i / 2;
    }
  }
  for (int i = 1; i <= n; i++) printf("%d%c", p[i], " \n"[i == n]);
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
  cout << (clock() - start_time) * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
#endif
}
