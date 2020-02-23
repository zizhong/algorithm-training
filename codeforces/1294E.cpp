/*
*  Ad hoc
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
const int mod = 1000000007;
const int inf = 0x3fffffff;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
 
struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
 
vector<vector<int>> v;
void solve(int ncase) {
  int n, m;
  scanf("%d%d", &n, &m);
  v.assign(n, vector<int>(m, 0));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      scanf("%d", &v[i][j]);
    }
  }
  int ans = 0;
  for(int j = 0; j < m; j++) {
    vector<int> s(n);
    for(int i = 0; i < n; i++) {
      int x = v[i][j];
      x -= (j + 1);
      if (x % m) continue;
      x /= m;
      if (x < 0 || x > n - 1) continue;
      int idx = (i - x + n) % n;
      s[idx]++;
    }
    int z = n;
    for(int i = 0; i < n; i++) {
      z = min(z, i + (n - s[i]));
    }
    ans += z;
  }
  cout << ans << endl;
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
