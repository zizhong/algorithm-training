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

const int N = 4 * 100000 + 10;
const int M = 20;

int a[N];
int f[N][M + 1];
int n;

ll calc_op(const vector<vector<int>> &pos, int idx, int left) {
  ll ret = 0;
  for (auto p : pos[idx]) {
    for (int i = 1; i <= M; i++) {
      if ((left & (1 << (i - 1))) == 0 || i == idx) continue;
      ret += f[p][i];
    }
  }
  return ret;
}

ll calc_op_cnt(const vector<vector<ll>> &cnt, int idx, int left) {
  ll ret = 0;
  for (int i = 0; i < M; i++) {
    if (i == idx || (left & (1 << i)) == 0) continue;
    ret += cnt[idx][i];
  }
  return ret;
}
void solve(int ncase) {
  scanf("%d", &n);
  vector<vector<int>> pos(M + 1, vector<int>());
  vector<int> exist(M + 1, 0);
  vector<vector<ll>> cnt(M + 1, vector<ll>(M + 1));
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    exist[a[i]] = 1;
    for (int j = 1; j <= M; j++) {
      f[i][j] = f[i - 1][j];
    }
    f[i][a[i]]++;
    pos[a[i]].push_back(i);
  }
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
      if (exist[i + 1] == 0 || exist[j + 1] == 0) continue;
      if (i == j) continue;
      cnt[i][j] = calc_op(pos, i + 1, ((1 << i) | (1 << j)));
    }
  }
  vector<ll> dp(1 << M, 0);
  for (int k = 1; k < (1 << M); k++) {
    int bit_cnt = __builtin_popcount(k);
    if (k < 2) {
      dp[k] = 0;
      continue;
    }
    int z = k;
    for (int i = 0; i < M; i++) {
      if ((z & (1 << i)) == 0) continue;
      if (exist[i + 1] == 0) {
        z ^= (1 << i);
      }
    }
    if (z != k) {
      dp[k] = dp[z];
      continue;
    }
    dp[k] = -1;
    for (int i = 0; i < M; i++) {
      if ((z & (1 << i)) == 0) continue;
      ll op = calc_op_cnt(cnt, i, z);
      if (dp[k] == -1 || dp[k] > op + dp[z ^ (1 << i)]) {
        dp[k] = op + dp[z ^ (1 << i)];
      }
    }
  }
  printf("%lld\n", dp[(1 << M) - 1]);
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
