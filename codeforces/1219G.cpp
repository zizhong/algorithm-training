/**
* 1000000 ** 1.5 = 31622776. costs ~ 100ms
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

ll max_n(const vector<ll> &arr, int n) {
  vector<ll> tmp(n + 1);
  for (ll x : arr) {
    tmp[n] = x;
    for (int i = n; i > 0; i--) {
      if (tmp[i] > tmp[i - 1]) {
        swap(tmp[i], tmp[i - 1]);
      } else {
        break;
      }
    }
  }
  ll ans = 0;
  for (int i = 0; i < n; i++) ans += tmp[i];
  return ans;
}

ll max_1_row_3_col(const vector<vector<int>> &num) {
  int n = num.size();
  int m = num[0].size();
  vector<ll> row_sum(n);
  vector<ll> col_sum(m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      row_sum[i] += num[i][j];
      col_sum[j] += num[i][j];
    }
  }
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ll tmp = row_sum[i];
    for (int j = 0; j < m; j++) col_sum[j] -= num[i][j];
    ans = max(ans, row_sum[i] + max_n(col_sum, 3));
    for (int j = 0; j < m; j++) col_sum[j] += num[i][j];
  }
  return ans;
}

ll max_2_row_2_col(const vector<vector<int>> &num) {
  int n = num.size();
  int m = num[0].size();
  vector<ll> row_sum(n);
  vector<ll> col_sum(m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      row_sum[i] += num[i][j];
      col_sum[j] += num[i][j];
    }
  }
  ll ans = 0;
  for (int r1 = 0; r1 < n; r1++) {
    for (int r2 = r1 + 1; r2 < n; r2++) {
      for (int j = 0; j < m; j++) col_sum[j] -= (num[r1][j] + num[r2][j]);
      ans = max(ans, row_sum[r1] + row_sum[r2] + max_n(col_sum, 2));
      for (int j = 0; j < m; j++) col_sum[j] += (num[r1][j] + num[r2][j]);
    }
  }
  return ans;
}

void solve(int ncase) {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<vector<int>> num(n, vector<int>(m));
  vector<vector<int>> num_v(m, vector<int>(n));
  ll sum = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &num[i][j]);
      sum += num[i][j];
      num_v[j][i] = num[i][j];
    }
  }
  if (n < 5 || m < 5) {
    printf("%lld\n", sum);
    return;
  }
  vector<ll> row_sum(n);
  vector<ll> col_sum(m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      row_sum[i] += num[i][j];
      col_sum[j] += num[i][j];
    }
  }
  ll ans1 = max(max_n(row_sum, 4), max_n(col_sum, 4));
  ll ans2 = max(max_1_row_3_col(num), max_1_row_3_col(num_v));
  ll ans3 = max_2_row_2_col(num.size() < num_v.size() ? num : num_v);
  printf("%lld\n", max(ans1, max(ans2, ans3)));
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
