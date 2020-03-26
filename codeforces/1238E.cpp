/*
* split the expression and merge the items with the same variables to reduce complexity.
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
const int mod = 1000000007;
const int inf = 0x3fffffff;
const int N = 2 * 1e5  + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

void solve(int ncase) {
  int n, m;
  cin >> n >> m;
  string s;
  cin >> s;
  vector<vector<int>> cnt(m + 1, vector<int>(m+1));
  for(int i = 1; i < n; i++) {
    int a = s[i-1] - 'a';
    int b = s[i] - 'a';
    if (a == b) continue;
    cnt[a][b]++;
    cnt[b][a]++;
  }
  vector<int> dp((1<<m), mod);
  dp[0] = 0;
  for(int z = 0; z < (1<<m) - 1; z++) {
    for(int x = 0; x < m; x++) {
      if ((1<<x)&z) continue;
      int pos_x = __builtin_popcount(z);
      int ndp = dp[z];
      for(int y = 0; y < m; y++) {
        if ((1<<y)&z) ndp += pos_x * cnt[x][y];
        else ndp -= pos_x * cnt[x][y];
      }
      dp[z|(1<<x)] = min(dp[z|(1<<x)], ndp);
    }
  }
  cout << dp[(1<<m)-1] << endl;
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
