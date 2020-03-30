/**
* C(n, k) % mod
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
const int inf = 0x3fffffff;
const int N = 2 * 1e5  + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }


struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator() (const pair<T1, T2>& p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

ll sumC(int n, int m, const vector<ll>& inv) {
  // C(n, 0) + C(n, 1) + .. + C(n, m) % mod;
  ll ret = 0;
  ll z = 1;
  for(int i = 0; i <= m; i++) {
    ret = (ret + z) % mod;
    z = z * (n - i) % mod * inv[i + 1] % mod;
  }
  return ret;
}

void solve(int ncase) {
  int n, k;
  cin >> n >> k;
  vector<int> h(n);
  for(int i = 0; i < n; i++) {
    cin >> h[i];
  }
  if (k == 1) {
    cout << 0 << endl;
    return;
  }
  int diff = 0;
  for(int i = 0; i < n; i++) {
    diff += (h[i] != h[(i + 1) % n] ? 1 : 0);
  }
  if (diff == 0) {
    cout << 0 << endl;
    return;
  }
  ll same = 1;
  for(int i = 0; i < n - diff; i++) {
    same = same * k % mod;
  }

  vector<ll> inv(n + 1);
  inv[1] = 1;
  for (int i = 2; i <= n; ++i) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
  if (k == 2) {
    cout << (same * 1LL *  sumC(diff, (diff + 1) / 2 - 1, inv)) % mod << endl;
    return;
  }
  vector<ll> pow_k(n + 1);
  pow_k[0] = 1;
  for(int i = 1; i <= n; i++) pow_k[i] = pow_k[i - 1] * (k - 2) % mod;
  ll ans = 0;
  ll c_diff_z = 1;
  for(int z = 0; z < diff; z++) {
    //cout << z << " " << pow_k[z] << " " << c_diff_z << ";  " << diff - z << " " << (diff - z + 1) / 2 - 1 << " " <<  sumC(diff - z, (diff - z + 1) / 2 - 1, inv) << endl;
    ans = (ans + (pow_k[z] * c_diff_z % mod * sumC(diff - z, (diff - z + 1) / 2 - 1, inv) % mod)) % mod;
    c_diff_z = c_diff_z * (diff - z) % mod * inv[z + 1] % mod;
  }
  cout << ans * same % mod << endl;
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
  //ios::sync_with_stdio(false);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
#endif
  solve_all_cases();
  //test();
}
