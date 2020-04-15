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
 
const int N = 4, M = 128;
int a[N][M];
int n, m;
int sum_array(int c, int k, int s = 0) {
  int ret = 0;
  for (int i = 0; i < n; i++) if (k & (1 << i))ret += a[(i + s) % n][c];
  return ret;
}
 
void solve(int ncase) {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &a[i][j]);
    }
  }
  int f[1 << N] = {0};
  for (int k = 0; k < (1 << n); k++) {
    f[k] = sum_array(0, k);
  }
  for (int c = 1; c < m; c++) {
    for (int pre_k = (1 << n) - 1; pre_k >= 0; pre_k--) {
      for (int s = 0; s < n; s++) {
        for (int k = 0; k < (1 << n); k++) {
          if (k & pre_k) continue;
          int tmp = sum_array(c, k, s);
          if (f[k | pre_k] < f[pre_k] + tmp) {
            f[k | pre_k] = f[pre_k] + tmp;
          }
        }
      }
    }
 
  }
 
  printf("%d\n", f[(1 << n) - 1]);
}
 
void solve_all_cases() {
  int T = 1;
  scanf("%d", &T);
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
