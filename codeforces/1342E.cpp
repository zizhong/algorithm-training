/**
* 1. calculate the Modular Inverse. 
* 1) for i % p
* 2) for [1...n] % mod
* 2. C(n, m) % p
* 3. Striling number of the second kind.
* 4. inv_fact[n] = inv_fact[n+1] * (n + 1);  (from 217ms->77ms)
*/

/* 1.
 * calculate inv[1...N]
 * if t = mod / i, k = mod % i;
 * => mod = t * i + k
 * => -t * i = k (% mod)
 * => -t * inv[k] = inv[i] (% mod)
 * => inv[i] = (mod - mod / i) * inv[mod % i] (% mod)
 *
 * 2. calculate inv(x) % p
 * x ^ p = p (% p)
 * x ^ (p - 1) = 1 (% p)
 * x * (x ^(p-2)) = 1 (% p)
 * inv[x] = (x ^(p - 2)) (%p)
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

/* 1.
 * calculate inv[1...N]
 * if t = mod / i, k = mod % i;
 * => mod = t * i + k
 * => -t * i = k (% mod)
 * => -t * inv[k] = inv[i] (% mod)
 * => inv[i] = (mod - mod / i) * inv[mod % i] (% mod)
 *
 * 2. calculate inv(x) % p
 * x ^ p = p (% p)
 * x ^ (p - 1) = 1 (% p)
 * x * (x ^(p-2)) = 1 (% p)
 * inv[x] = (x ^(p - 2)) (%p)
 */

const int N = 2 * (1e5) + 10;
int fact[N];
int inv_fact[N];
int power_n[N];

int power_mod(int a, int x) {
  int ret = 1;
  for (int i = 0; (1 << i) <= x; i++) {
    if (x & (1 << i)) {
      ret = ret * 1LL * a % mod;
    }
    a = a * 1LL * a % mod;
  }
  return ret;
}

int inv(int a) {
  return power_mod(a, mod - 2);
}

ll C(int n, int m) {
  return fact[n] * 1LL * inv_fact[n - m] % mod * inv_fact[m] % mod;
}

ll Strling(int n, int k) {
  // S(n, k) = 1/fact(k) * sigma_i(0...k, (-1)^i * C(k, i) * (k - i)^n)
  // => = inv(fact[k]) * sigma_i (0..k, flag * C(k, i) * power_n[k-i])
  ll ans = inv(fact[k]);
  for (int i = 1; i <= n; i++) {
    power_n[i] = power_mod(i, n);
  }
  int flag = 1;
  ll sum = 0;
  for (int i = 0; i < k; i++) {
    ll tmp = flag * 1LL * C(k, i) % mod * power_n[k - i] % mod;
    sum = (sum + tmp % mod + mod) % mod;
    flag *= -1;
  }
  ans = ans * sum % mod;
  return ans;
}

void solve(int ncase) {
  int n, k;
  cin >> n >> k;
  if (k >= n) {
    cout << 0 << endl;
    return;
  }
  fact[0] = 1;
  for (int i = 1; i <= n; i++) {
    fact[i] = fact[i - 1] * 1LL * i % mod;
  }
  inv_fact[n] = inv(fact[n]);
  for (int i = n - 1; i >= 0; i--) {
    inv_fact[i] = inv_fact[i + 1] * 1LL * (i + 1) % mod;
  }
  int ans = (k == 0 ? 1LL : 2LL) * Strling(n, n - k) % mod * fact[n] % mod * inv_fact[k] % mod;
  cout << ans << endl;
}

void solve_all_cases() {
  int T = 1;
  //scanf("%d", &T);
  // cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}

int main() {
  //ios::sync_with_stdio(false);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
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
