/*
* binary search
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
#include<iomanip>
#include <sstream>
#include <cmath>
//#include "utils/haha.h"
//#include "utils/max_flow.h"
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<string, int> PSI;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;
typedef pair<double, double> PDD;
typedef pair<ll, PII> PLP;
#define CLS(x, v) (memset((x), (v), sizeof((x))))
const double pi = acos(-1);
template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class T>
using max_heap = priority_queue<T>;
const int mod = 1000000007;
const int inf = 0x3fffffff;
const int N = 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

bool okay(ll x, ll n, ll k) {
  ll num = 0;
  ll base = x % 2 ? 1 : 2;
  while(x <= n) {
    // [x, x + base)
    num += min(x + base, n + 1) - x;
    if (num >= k) return true;
    x <<= 1;
    base <<= 1;
  }
  return num >= k;
}

ll search_odd(ll n, ll k) {
  ll l = 0, r = n / 2 + 1;
  if (!okay(2 * l + 1, n, k)) return -1;
  while(l + 1 < r) {
    ll m = (l + r) / 2;
    if (okay(m * 2 + 1, n, k)) l = m;
    else r = m;
  }
  return 2 * l + 1;
}

ll search_even(ll n, ll k) {
  ll l = 1, r = n / 2 + 1;
  if (!okay(2 * l, n, k)) return -1;
  while(l + 1 < r) {
    ll m = (l + r) / 2;
    if (okay(m * 2, n, k)) l = m;
    else r = m;
  }
  return 2 * l;
}

void solve(int ncase) {
  ll n, k;
  cin >> n >> k;
  cout << max(search_odd(n, k), search_even(n, k)) << endl;
}

int main() {
  //ios::sync_with_stdio(false);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //freopen("out.txt", "w", stdout);
#endif
  //precalc();
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
