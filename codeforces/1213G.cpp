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
//const int mod = 998244353;
const int inf = 0x3fffffff;
const int N = 2 * 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
 
struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
 
int fa[N];
ll ans;
int ufs_find(int r) {
  return fa[r] < 0 ? r : (fa[r] = ufs_find(fa[r]));
}
 
ll cnt_path(int cnt) {
  return cnt * 1LL * (cnt - 1) / 2;
}
 
void ufs_union(int x, int y) {
  int rx = ufs_find(x);
  int ry = ufs_find(y);
  int cnt_x = -fa[rx];
  int cnt_y = -fa[ry];
  ans = ans + cnt_x * 1LL * cnt_y;
  if (cnt_x > cnt_y) {
    fa[ry] = rx;
    fa[rx] = -(cnt_x + cnt_y);
  } else {
    fa[rx] = ry;
    fa[ry] = -(cnt_x + cnt_y);
  }
}
 
void solve(int ncase) {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<vector<PII>> edge(N);
  for (int i = 0; i < n - 1; i++) {
    int a, b, w;
    scanf("%d%d%d", &a, &b, &w);
    edge[w].push_back(PII(a, b));
  }
 
  vector<int> q(m);
  for (int i = 0; i < m; i++) {
    scanf("%d", &q[i]);
  }
  memset(fa, -1, sizeof(fa));
  vector<ll> ret(N);
  for (int i = 1; i < N; i++) {
    ans = ret[i - 1];
    for (auto p : edge[i]) {
      ufs_union(p.first, p.second);
    }
    ret[i] = ans;
  }
  for (int i = 0; i < m; i++) {
    printf("%lld ", ret[q[i]]);
  }
  puts("");
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
