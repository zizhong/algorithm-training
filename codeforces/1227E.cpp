/*
* 1. bianry search to turn an optimzation question to a verification question.
* 2. Find the arson source using sum[i][j] to tell if a square filled with X
* 3. Verify the solution using BFS
* 4. 9 Retry. 
      First 3 times WA are due to incorrect approach of finding the arson source. Only checked the 8 directions but not the full sqaure region;
      Then the following 3 times TLE are due to using cin/cout+string, instead of scanf/printf+char*
      Then the following 1 time WA on case 54, are due to no verification of the answer. The original solution assumes the final T is controlled by the min(horizontal_X_line, vertical_X_line). but that's not true.
      For example,
7 5
..XXX
..XXX
..XXX
.XXX.
XXX..
XXX..
XXX..
    The answer from the original approach is 1 but the correct answer is 0. So, we need to verify our answers and using binary search to find potential answers.
    Then the following 1 time RE is due to 
      PII &head = q.front();
      q.pop();
      int x = head.first; // use after free
     The the following 1 time AC is due to my perseverance.
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
const int inf = 0x3fffffff;
const int N = 2 * 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

int n, m;
const int d[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
void calc_ng(vector<char *> &ng, const vector<char *> &g, int T, const vector<vector<int>> &sum) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ng[i][j] = '.';
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int zi = i - T * 2;
      int zj = j - T * 2;
      if (zi < 0 || zj < 0) continue;
      int s = sum[i][j] - (zi - 1 >= 0 ? sum[zi - 1][j] : 0) - (zj - 1 >= 0 ? sum[i][zj - 1] : 0)
          + (zi - 1 >= 0 && zj - 1 >= 0 ? sum[zi - 1][zj - 1] : 0);
      if (s == (2 * T + 1) * (2 * T + 1)) ng[i - T][j - T] = 'X';
    }
  }
}

bool verify_ng(vector<char *> &ng, const vector<char *> &g, int T) {
  queue<PII> q;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (ng[i][j] == 'X') q.push(PII(i, j));
    }
  }
  for (int t = 0; t < T; t++) {
    vector<PII> n_e;
    while (!q.empty()) {
      PII head = q.front();
      q.pop();
      for (int k = 0; k < 8; k++) {
        int nx = head.first + d[k][0];
        int ny = head.second + d[k][1];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) return false;
        if (ng[nx][ny] != '.') continue;
        ng[nx][ny] = 'X';
        if (g[nx][ny] == '.') return false;
        n_e.push_back(PII(nx, ny));
      }
    }
    for (auto &p : n_e) q.push(p);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (ng[i][j] != g[i][j]) return false;
    }
  }
  return true;
}

bool okay(int T, const vector<char *> &g, vector<char *> &ng, const vector<vector<int>> &sum) {
  calc_ng(ng, g, T, sum);
  return verify_ng(ng, g, T);
}

void solve(int ncase) {
  scanf("%d%d", &n, &m);
  vector<char *> g(n);
  for (int i = 0; i < n; i++) {
    g[i] = new char[m + 1];
  }
  for (int i = 0; i < n; i++) {
    scanf("%s", g[i]);
    g[i][m] = 0;
  }
  int ans = max(n, m);
  int T = (ans + 1) / 2 - 1;
  if (T == 0) {
    printf("%d\n", 0);
    for (int i = 0; i < n; i++) printf("%s\n", g[i]);
    return;
  }

  vector<vector<int>> col_sum(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      col_sum[i][j] = (j > 0 ? col_sum[i][j - 1] : 0) + (g[i][j] == 'X');
    }
  }
  vector<vector<int>> sum(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      sum[i][j] = (i > 0 ? sum[i - 1][j] : 0) + col_sum[i][j];
    }
  }

  vector<char *> ng(n);
  for (int i = 0; i < n; i++) {
    ng[i] = new char[m + 1];
    for (int j = 0; j < m; j++) {
      ng[i][j] = '.';
    }
    ng[i][m] = 0;
  }
  int l = 0, r = T + 1;
  while (l + 1 < r) {
    int mid = (l + r) / 2;
    if (okay(mid, g, ng, sum)) l = mid;
    else r = mid;
  }
  printf("%d\n", l);
  calc_ng(ng, g, l, sum);
  for (int i = 0; i < n; i++) printf("%s\n", ng[i]);
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
  freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
#endif
  solve_all_cases();
  //test();
}
