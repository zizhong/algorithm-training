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

//const int N = 1e6 + 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
int n, k;
const int N = 512;
ll f[2][N];

void update(ll &f1, ll f2) {
  if (f1 < 0 || f1 < f2) f1 = f2;
}
void solve(int ncase) {
  scanf("%d%d", &n, &k);
  CLS(f, -1);
  ll sum_x = 0, sum_y = 0;
  f[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    int x, y;
    int cur = i & 1;
    int pre = cur ^1;
    CLS(f[cur], -1);
    scanf("%d%d", &x, &y);
    for (int j = 0; j < k; j++) {
      if (f[pre][j] < 0) continue;
      int pre_left_x = j;
      int pre_left_y = sum_x + sum_y - f[pre][j] * 1LL * k - pre_left_x;
      int cur_left_x = pre_left_x + x;
      int cur_left_y = pre_left_y + y;
      update(f[cur][cur_left_x % k], f[pre][j] + cur_left_x / k + cur_left_y / k);
      for (int used_x = 0; used_x < k && used_x <= x; used_x++) {
        int used_y = k - used_x;
        if (used_y > y) continue;
        update(f[cur][(cur_left_x - used_x) % k],
               f[pre][j] + (cur_left_x - used_x) / k + (cur_left_y - used_y) / k + 1);
      }
    }
    sum_x += x;
    sum_y += y;
  }
  printf("%lld\n", *max_element(f[n & 1], f[n & 1] + k));
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
