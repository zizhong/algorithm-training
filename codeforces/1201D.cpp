/*
* Define the states. It is intuitive to assume that only the two ends matters.
* A non end state can be transformed from the end state with potential extra cost. So, we only need to focus on the end state.
**/

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
 
ll calc_col(int col[], vector<int> &b_before, vector<int> &b_after) {
  ll first = -1;
  if (b_before[col[0]] != -1) {
    first = abs(col[0] - b_before[col[0]]) + abs(col[1] - b_before[col[0]]);
  }
  if (b_after[col[0]] != -1) {
    ll tmp = abs(col[0] - b_after[col[0]]) + abs(col[1] - b_after[col[0]]);
    if (first == -1 || first > tmp) first = tmp;
  }
  return first + abs(col[1] - col[2]);
}
 
void solve(int ncase) {
  int n, m, k, q;
  scanf("%d%d%d%d", &n, &m, &k, &q);
  vector<PII> z(k);
  for (int i = 0; i < k; i++) {
    scanf("%d%d", &z[i].first, &z[i].second);
  }
  sort(z.begin(), z.end());
  vector<int> b(q);
  vector<int> is_b(m + 1);
  for (int i = 0; i < q; i++) {
    scanf("%d", &b[i]);
    is_b[b[i]] = 1;
  }
 
  vector<int> b_before(m + 1, -1), b_after(m + 1, -1);
  int last_b = -1;
  for (int i = 1; i <= m; i++) {
    if (is_b[i]) last_b = i;
    b_before[i] = last_b;
  }
  last_b = -1;
  for (int i = m; i >= 1; i--) {
    if (is_b[i]) last_b = i;
    b_after[i] = last_b;
  }
  int pre_i = 1;
  vector<PIL> pos;
  pos.emplace_back(1, 0);
  for (int i = 0; i < k; i++) {
    int j = i;
    while (j < k && z[j].first == z[i].first) j++;
    int min_c = z[i].second;
    int max_c = z[j - 1].second;
    vector<PIL> npos;
    if (1 == z[i].first) {
      npos.emplace_back(max_c, max_c - 1);
    } else {
      ll i_delta = z[i].first - pre_i;
      pre_i = z[i].first;
      ll max_cost = -1;
      ll min_cost = -1;
      for (auto &p : pos) {
        int col[3] = {p.first, min_c, max_c};
        ll tmp = calc_col(col, b_before, b_after) + i_delta + p.second;
        if (max_cost == -1 || max_cost > tmp) max_cost = tmp;
        swap(col[1], col[2]);
        tmp = calc_col(col, b_before, b_after) + i_delta + p.second;
        if (min_cost == -1 || min_cost > tmp) min_cost = tmp;
      }
      if (i == j - 1) {
        npos.emplace_back(min_c, min_cost);
      } else {
        npos.emplace_back(min_c, min_cost);
        npos.emplace_back(max_c, max_cost);
      }
    }
    pos = npos;
    i = j - 1;
  }
  ll ret = pos[0].second;
  if (pos.size() > 1) {
    ret = min(ret, pos[1].second);
  }
  printf("%lld\n", ret);
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
