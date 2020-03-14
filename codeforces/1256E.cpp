/*
DP

1. sort
2. The first idea is in solve2, consider the last number can transfer the last segment to [1, 2, 0]. The D2 transfer is incompleted. 
The second idea is to consider 
[j, i] as the last team, so the dp[i] = dp[j] - num[j+1] + num[j]. For each i, find a j that minumizes dp[j] - num[j+1]. 
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
const int N = 2 * 1e5  + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

void solve2(int ncase) {
  int n;
  scanf("%d", &n);
  vector<PII> num(n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &num[i].first);
    num[i].second = i;
  }
  sort(num.begin(), num.end());
  vector<vector<int>> f(n + 1, vector<int>(3, inf));
  f[0][1] = num[0].first;
  for(int i = 1; i < n; i++) {
    if (f[i-1][0] < inf) {
      // -> 0
      f[i][0] = min(f[i][0], f[i-1][0] - num[i-1].first + num[i].first);
      // -> 1
      f[i][1] = min(f[i][1], f[i-1][0] + num[i].first);
    }
    if (f[i-1][1] < inf) {
      // ->2
      f[i][2] = min(f[i][2], f[i-1][1] - num[i-1].first + num[i].first - num[i-1].first);
    }
    if (f[i-1][2] < inf) {
      // ->0
      f[i][0] = min(f[i][0], f[i-1][2] - num[i-1].first + num[i].first);
    }
  }
  vector<int> team(n);
  int team_idx = 1;
  int idx = 0;
  for(int i = n - 1; i >= 0; i--) {
    team[num[i].second] = team_idx;
    if (i == 0) break;
    if (idx == 0) {
      // 0 -> ?
      if (f[i-1][0] < inf && f[i-1][0] - num[i-1].first == f[i][0] - num[i].first) {
        continue;
      }
      idx = 2;
      continue;
    }
    if (idx == 1) {
      idx = 0;
      team_idx++;
      continue;
    }
    if (idx == 2) {
      idx = 1;
    }
  }
  printf("%d %d\n", f[n - 1][0], team_idx);
  for(int i = 0; i < n; i++) {
    printf("%d ", team[i]);
  }
}
void solve(int ncase) {
  int n;
  scanf("%d", &n);
  vector<PII> num(n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &num[i].first);
    num[i].second = i;
  }
  sort(num.begin(), num.end());
  vector<int> f(n, inf);
  vector<int> pre(n, -1);
  int min_pre = -1;
  for(int i = 2; i < n; i++) {
    f[i] = num[i].first - num[0].first;
    if (i == 5) {
      min_pre = 2;
    } else if (i > 5) {
      if (f[min_pre] - num[min_pre + 1].first > f[i - 3] - num[i - 2].first) {
        min_pre = i - 3;
      }
    }
    if (min_pre > 0) {
      if (f[i] > num[i].first + f[min_pre] - num[min_pre + 1].first) {
        f[i] = num[i].first + f[min_pre] - num[min_pre + 1].first;
        pre[i] = min_pre;
      }
    }
  }
  vector<int> team(n);
  for(int i = n-1, team_idx = 1; i >= 0; i = pre[i]) {
    for(int j = pre[i] + 1; j <= i; j++) team[num[j].second] = team_idx;
    team_idx++;
  }
  printf("%d %d\n", f[n - 1], team[num[0].second]);
  for(int i = 0; i < n; i++) printf("%d ", team[i]);
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
