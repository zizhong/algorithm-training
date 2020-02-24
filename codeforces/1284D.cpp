/*
 *  Given N rectangles with side paralleling with x-axis and y-axis.
 *  Find if there is a case that two rectangles overlap on projecting on x(y)-axis but not y(x)-axis.
 *  scanline + multiset. multiset to tell if an intervel intersect all intervels.
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
template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class T>
using max_heap = priority_queue<T>;
const int mod = 1000000007;
const int inf = 0x3fffffff;
const int N = 100010;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
 
struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
 
int x_1[N], x_2[N], y_1[N], y_2[N];
int n;
 
bool findInconsistent(int l[], int r[], int b[], int u[]) {
  vector<PII> e(2 * n);
  for(int i = 1; i <= n; i++) {
    e[i-1] = PII(l[i-1], i);
    e[n + i-1] = PII(r[i-1] + 1, -i);
  }
  sort(e.begin(), e.end());
  multiset<int> up;
  multiset<int> bottom;
  for(auto &ev : e) {
    if (ev.second < 0) {
      up.erase(up.find(u[-ev.second - 1]));
      bottom.erase(bottom.find(b[-ev.second - 1]));
      continue;
    }
    if ((!up.empty() && *up.begin() < b[ev.second - 1]) ||
        (!bottom.empty() && *bottom.rbegin() > u[ev.second - 1])) {
      return true;
    }
    up.insert(u[ev.second - 1]);
    bottom.insert(b[ev.second - 1]);
  }
  return false;
}
void solve(int ncase) {
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%d%d%d%d", &x_1[i], &x_2[i], &y_1[i], &y_2[i]);
  }
  printf("%s\n", (findInconsistent(x_1, x_2, y_1, y_2) ||
      findInconsistent(y_1, y_2, x_1, x_2)) ? "NO" : "YES");
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
