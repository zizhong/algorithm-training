/**
*   there are four cases 
*      1. previous DOWN, current RIGHT
*      2. previous DOWN, current DOWN
*      3. previous RIGHT, current RIGHT
*      4. previous RIGHT, current DOWN  
*   
*      2 & 3 could be calculated with range sum.
*      1 & 4 could be calculated with DP.
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
const int N = 2048;
char maze[N][N];
int rock_col[N][N];
int rock_row[N][N];
int dp[N][N];
int go_down[N][N];
int go_right[N][N];
int n, m;

inline void add_mod(int &x, int v) {
  x = x + v;
  if (x < mod) x += mod;
  if (x >= mod) x -= mod;
}

void solve(int ncase) {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%s", maze[i]);
  }
  if (n == 1 && m == 1) {
    cout << 1 << endl;
    return;
  }
  memset(rock_col, 0, sizeof(rock_col));
  memset(rock_row, 0, sizeof(rock_row));
  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      rock_row[i][j] = (j + 1 < m ? rock_row[i][j + 1] : 0) + (maze[i][j] == 'R');
      rock_col[i][j] = (i + 1 < n ? rock_col[i + 1][j] : 0) + (maze[i][j] == 'R');
    }
  }

  go_right[1][1] = 1;
  go_right[1][2] = -1;
  go_down[1][1] = 1;
  go_down[2][1] = -1;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      add_mod(go_right[i][j], go_right[i][j - 1]);
      add_mod(go_down[i][j], go_down[i - 1][j]);
      int right_rock = rock_row[i - 1][j];
      int below_rock = rock_col[i][j - 1];
      if (j <= m - right_rock + 1) {
        add_mod(go_right[i][j + 1], go_down[i][j]);
        add_mod(go_right[i][m - right_rock + 1], -go_down[i][j]);
      }
      if (i <= n - below_rock + 1) {
        add_mod(go_down[i + 1][j], go_right[i][j]);
        add_mod(go_down[n - below_rock + 1][j], -go_right[i][j]);
      }

      //cout << i << " " << j << ", right = " << go_right[i][j] << ", down = " << go_down[i][j] << endl;
    }
  }
  add_mod(go_down[n][m], go_right[n][m]);
  cout << go_down[n][m] << endl;
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
