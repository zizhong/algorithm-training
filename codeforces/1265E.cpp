/*
Given p1, p2, p3, .. pn, starting from left, you have pi chance to make forward by 1 step, 1-pi change to start from the beginning.
Cacluate how many days are needed as excepted value to finish.

e[i] means the expected days need to finish from i. The answer is e[1]. e[n+1] = 0
We can have e[i] = pi * (e[i+1] + 1) + (1-p[i]) * (e[1] + 1) = 1 + pi * e[i+1] + (1-pi) * e[i]

e[1] = 1 + p1 * e[2] + (1-p1) * e[1]
e[2] = 1 + p2 * e[3] + (1-p2) * e[1]
...
e[n] = 1 + pn * 0 + (1-pn) * e[1]

Using substitution, we can get
e[2] = e[1] - 1/p1
e[3] = e[1] - 1/(p1p2) - 1/p2
e[4] = e[1] - 1/(p1p2p3) - 1/(p2p3) - 1/p3
...
e[n+1] = e[1] - 1/ (p1p2...pn) - 1/(p2p3..pn) - ... - 1/ pn = 0

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
typedef pair<int, ll> PIL;
typedef pair<ll, ll> PLL;
typedef pair<double, double> PDD;
typedef pair<ll, PII> PLP;
#define CLS(x, v) (memset((x), (v), sizeof((x))))
const double pi = acos(-1);
template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class T>
using max_heap = priority_queue<T>;
//const int mod = 1000000007;
const int inf = 0x3fffffff;
const int N = 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
 
struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
const ll PMOD = 998244353LL;
 
 
ll qpow(long long a, ll b) {
  ll ans = 1;
  a = (a % PMOD + PMOD) % PMOD;
  for (; b; b >>= 1) {
    if (b & 1) ans = (a * ans) % PMOD;
    a = (a * a) % PMOD;
  }
  return ans;
}
 
ll inv(ll x) {
  return qpow(x, PMOD - 2);
}
void solve(int ncase) {
  int n;
  scanf("%d", &n);
  vector<ll> p(101);
  ll inv_100 = inv(100);
  for(int i = 1; i <= 100; i++) {
    p[i] = i * inv_100 % PMOD;
  }
  ll z = 1;
  ll zsum = 0;
  for(int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    zsum = (zsum + z) % PMOD;
    z = z * p[x] % PMOD;
  }
  cout << zsum * inv(z) % PMOD << endl;
}
 
int main() {
  //ios::sync_with_stdio(false);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //freopen("out.txt", "w", stdout);
#endif
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
