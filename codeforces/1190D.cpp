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
template<class T>
void debugvv(vector<vector<T>> &vv) {
  for (auto &v : vv) {
    for (auto &i : v) {
      cout << i << " ";
    }
    cout << endl;
  }
}

int n;

const int N = 2 * 1e5 + 10;
int bit[N];

void update_bit(int x, int delta) {
  while (x < N) {
    bit[x] += delta;
    x += (x & -x);
  }
}

int query_bit(int x) {
  int ret = 0;
  while (x > 0) {
    ret += bit[x];
    x -= (x & -x);
  }
  return ret;
}

int x[N];
int y[N];
void solve(int ncase) {
  scanf("%d", &n);
  vector<PII> p(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &x[i], &y[i]);
    p[i] = PII(x[i], y[i]);
  }
  sort(x, x + n);
  sort(y, y + n);
  unordered_map<int, int> nx, ny;
  int idx_x = 1;
  for (int i = 0; i < n; i++) {
    if (i == 0 || x[i] != x[i - 1]) {
      nx[x[i]] = idx_x++;
    }
  }
  int idx_y = 1;
  for (int i = 0; i < n; i++) {
    if (i == 0 || y[i] != y[i - 1]) {
      ny[y[i]] = idx_y++;
    }
  }
  for (auto &i : p) {
    i = PII(nx[i.first], ny[i.second]);
  }
  sort(p.begin(), p.end());
  vector<vector<int>> v(idx_y);
  for (auto &i : p) {
    v[i.second].push_back(i.first);
  }
  ll ans = 0;
  for (int i = idx_y - 1; i >= 1; i--) {
    vector<int> pre_cnt(v[i].size());
    for (int j = 0; j < v[i].size(); j++) {
      pre_cnt[j] = query_bit(v[i][j] - 1);
      int c = query_bit(v[i][j]);
      if (c > pre_cnt[j]) continue;
      update_bit(v[i][j], 1);
    }
    int total = query_bit(idx_x);
    ans += total * 1LL * (total + 1) / 2;
    for (int j = 0; j < v[i].size(); j++) {
      int pre = pre_cnt[j];
      if (j > 0) {
        pre -= (pre_cnt[j - 1] + 1);
      }
      ans -= pre * 1LL * (pre + 1) / 2;
    }
    int pre = total - pre_cnt.back() - 1;
    ans -= pre * 1LL * (pre + 1) / 2;
  }
  printf("%lld\n", ans);
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
