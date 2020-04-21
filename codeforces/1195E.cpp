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
const int N = 1e6 + 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
template<class T>
void debugvv(vector<vector<T>> &vv) {
  for (auto &v : vv) {
    for (auto &i : v) {
      cout << i << " ";
    }
    cout << endl;
  }
}

void solve(int ncase) {
  int n, m, a, b;
  scanf("%d%d%d%d", &n, &m, &a, &b);
  int g0, x, y, z;
  scanf("%d%d%d%d", &g0, &x, &y, &z);
  vector<vector<int>> g(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      g[i][j] = g0;
      g0 = (g0 * 1LL * x + y) % z;
    }
  }
  //debugvv(g);
  vector<PII> q(3010);
  int head = 0;
  int tail = 0;
  for (int c = 0; c < m; c++) {
    head = tail = 0;
    for (int r = n - 1; r >= 0; r--) {
      while (head < tail && q[tail - 1].first >= g[r][c]) {
        tail--;
      }
      q[tail++] = PII(g[r][c], r);
      while (q[head].second >= r + a) head++;
      g[r][c] = q[head].first;
    }
  }
  for (int r = 0; r < n; r++) {
    head = tail = 0;
    for (int c = m - 1; c >= 0; c--) {
      while (head < tail && q[tail - 1].first >= g[r][c]) {
        tail--;
      }
      q[tail++] = PII(g[r][c], c);
      while (q[head].second >= c + b) head++;
      g[r][c] = q[head].first;
    }
  }
  //debugvv(g);
  ll ans = 0;
  for (int i = 0; i < n - a + 1; i++) {
    for (int j = 0; j < m - b + 1; j++) {
      ans += g[i][j];
    }
  }
  printf("%lld\n", ans);
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
