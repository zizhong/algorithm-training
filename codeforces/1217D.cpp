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
int n, m;
vector<vector<PII>> g;
vector<int> visited;
 
bool dfs(int r) {
  if (visited[r] == 2) return false;
  if (visited[r] == 1) return true;
  visited[r] = 1;
  for (auto u : g[r]) if (dfs(u.first)) return true;
  visited[r] = 2;
  return false;
}
void solve(int ncase) {
  scanf("%d%d", &n, &m);
  g.assign(n + 1, vector<PII>());
  for (int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(PII(v, i));
  }
  visited.assign(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    if (visited[i] == 0) {
      if (dfs(i)) {
        vector<int> c(m, -1);
        for (int i = 1; i <= n; i++) {
          for (auto p : g[i]) {
            if (c[p.second] != -1) continue;
            if (p.first > i) c[p.second] = 2;
            else c[p.second] = 1;
          }
        }
        printf("2\n");
        for (int i = 0; i < m; i++) printf("%d ", c[i]);
        puts("");
        return;
      }
    }
  }
  puts("1");
  for (int i = 1; i <= m; i++) printf("1 ");
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
