/*
* Consider two antennas, after the left one covered the essitentials, there is a gap that can be covered by the left antenna or the right antenna. If the gap is covered by the right one, the right bound of covered area will be larger.
So, given a left bound, and an antenna, the right bound can be calculated.
We can solve the question by dp,
  f[i][j] := the right bound of covered area is `i`, and the last used antenna is `j`. For each antenna after `j`,
  after apply the new antenna, if there is no gap, update the right limit;
  If there is a gap, cover it with the new antenna.
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
const int N = 1e6  + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
int n, m;
void solve(int ncase) {
  scanf("%d%d", &m, &n);
  vector<vector<int>> f(n + 1, vector<int>(m + 1, -1));
  f[0][0] = 0;
  vector<PII> t(m);
  for(int i = 0; i < m; i++) {
    scanf("%d%d", &t[i].first, &t[i].second);
  }
  sort(t.begin(), t.end());
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if (f[i][j] == -1) continue;
      for(int k = j + 1; k <= m; k++) {
        if (t[k - 1].first <= i ) {
          int right = max(t[k-1].first + t[k-1].second, i);
          if (right > n) right = n;
          if (f[right][k] < 0 || f[right][k] > f[i][j]) {
            f[right][k] = f[i][j];
          }
          continue;
        }
        int newr = t[k-1].second;
        int cost = 0;
        if (newr < t[k-1].first - (i + 1)) {
          cost = t[k-1].first - (i + 1) - t[k-1].second;
          newr = t[k-1].first - (i + 1);
        }
        int right = t[k-1].first + newr;
        if (right > n) right = n;
        if (f[right][k] < 0 || f[right][k] > cost + f[i][j]) {
          f[right][k] = cost + f[i][j];
        }
      }
    }
  }
  int ans = n;
  for(int i = 1; i <= n; i++) {
    for(int j = 0; j <= m; j++) {
      if (f[i][j] == -1) continue;
      //cout << i << " " << j << " " << f[i][j] << endl;
      ans = min(ans, f[i][j] + n - i);
    }
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
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
