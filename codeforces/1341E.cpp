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
//const int N = 1e6 + 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

template<typename C>
struct reverse_wrapper {

  C &c_;
  reverse_wrapper(C &c) : c_(c) {}

  typename C::reverse_iterator begin() { return c_.rbegin(); }
  typename C::reverse_iterator end() { return c_.rend(); }
};

template<typename C>
reverse_wrapper<C> r_wrap(C &c) {
  return reverse_wrapper<C>(c);
}
int f[10010][1001]; //
int n, m, g, r;
int d[10010];
queue<int> q;
void dfs(int idx, int t) {
  //printf("dfs(idx= %d, t= %d)= [%d]\n", idx, t, f[idx][t]);
  if (idx > 0) {
    int diff = d[idx] - d[idx - 1];
    if (t + diff <= g) {
      int nt = t + diff;
      if (nt == g) {
        nt = 0;
        diff += r;
      }
      if (f[idx - 1][nt] < 0 || f[idx - 1][nt] > f[idx][t] + diff) {
        f[idx - 1][nt] = f[idx][t] + diff;
        if (nt == 0) q.push(idx - 1);
        else dfs(idx - 1, nt);
      }
    }
  }
  if (idx < m - 1) {
    int diff = d[idx + 1] - d[idx];
    if (t + diff <= g) {
      int nt = t + diff;
      if (nt == g) {
        nt = 0;
        diff += r;
      }

      if (f[idx + 1][nt] < 0 || f[idx + 1][nt] > f[idx][t] + diff) {
        f[idx + 1][nt] = f[idx][t] + diff;
        if (nt == 0) q.push(idx + 1);
        else dfs(idx + 1, nt);
      }
    }
  }
}
void solve(int ncase) {
  memset(f, -1, sizeof(f));
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d", &d[i]);
  }
  sort(d, d + m);
  scanf("%d%d", &g, &r);
  f[0][0] = 0;
  q.push(0);
  while (!q.empty()) {
    int h = q.front();
    q.pop();
    dfs(h, 0);
  }
  int ans = -1;
  for (int i = 0; i < g; i++) {
    if (f[m - 1][i] < 0) continue;
    //cout << "f " << i << " " << f[m - 1][i] << endl;
    if (i == 0) f[m - 1][i] -= r;
    if (ans == -1 || ans > f[m - 1][i]) ans = f[m - 1][i];
  }
  printf("%d\n", ans);
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
