/**
* Without the constraints of picking all, we cannot greedily choose the choice.
* We need to DP to calculate the optimal.
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
const int mod = 1000000007;
//const int mod = 998244353;
const int inf = 0x3fffffff;
//const int N = 2 * 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
 
struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
 
bool cmp_diff(const PII &p1, const PII &p2) {
  if (p1.first + p1.second == p2.first + p2.second) return p1.first < p2.first;
  return p1.first + p1.second > p2.first + p2.second;
}
 
void solve(int ncase) {
  int n, r;
  scanf("%d%d", &n, &r);
  vector<PII> pos, neg;
  for (int i = 0; i < n; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    b >= 0 ? pos.push_back(PII(a, b)) : neg.push_back(PII(a, b));
  }
  sort(pos.begin(), pos.end());
  sort(neg.begin(), neg.end(), cmp_diff);
  int ans = 0;
  for (auto &p : pos) {
    if (r < p.first) {
      continue;
    }
    r += p.second;
    ans++;
  }
  int nr = r;
  vector<int> dp(nr + 1, -1);
  dp[nr] = 0;
  for (auto &p : neg) {
    vector<int> ndp(nr + 1, -1);
    ndp = dp;
    for (int i = 0; i < nr + 1; i++) {
      if (dp[i] == -1 || i + p.second < 0 || i < p.first) continue;
      int j = i + p.second;
      if (ndp[j] == -1 || ndp[j] < dp[i] + 1) {
        ndp[j] = dp[i] + 1;
      }
    }
    dp = ndp;
    //for (int x : dp) cout << x << " ";
    //cout << endl;
  }
 
  printf("%d\n", *max_element(dp.begin(), dp.end()) + ans);
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
  auto start_time = clock();
#endif
  solve_all_cases();
  //test();
#ifdef _zzz_
  cout << (clock() - start_time) * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
#endif
}
