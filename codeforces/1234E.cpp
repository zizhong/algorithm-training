/*
* 1. Discussion on different cases. 
* 2. Sweepline
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
const int inf = 0x3fffffff;
const int N = 2 * 1e5  + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

void solve(int ncase) {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> a(m);
  for(int i = 0; i < m; i++) {
    scanf("%d", &a[i]);
  }
  vector<ll> base_val(n + 1);
  vector<ll> second_sum(n + 1);
  vector<ll> cnt(n + 1);
  vector<ll> small(n + 1);
  vector<PII> events;
  ll ans = 0;
  for(int i = 1; i < m; i++) {
    if (a[i-1] == a[i]) continue;
    second_sum[a[i-1]] += a[i];
    second_sum[a[i]] += a[i-1];
    int u = a[i-1];
    int v = a[i];
    if (u>v) swap(u, v);
    base_val[u] += v - u;
    base_val[v] += v - u;
    ans += v - u;
    small[v]++;
    cnt[u]++;
    cnt[v]++;
    events.push_back(PII(u, 1));
    events.push_back(PII(v, -1));
  }
  sort(events.begin(), events.end());
  int open = 0;
  int e = 0;
  for(int z = 1; z <= n; z++) {
    while(e < events.size() && (events[e].first < z || (events[e].first == z && events[e].second == -1))) {
      open += events[e].second;
      e++;
    }
    ll delta = -base_val[z] + second_sum[z] - cnt[z] - open + small[z];
    printf("%I64d ", ans + delta);
    while(e < events.size() && (events[e].first == z && events[e].second == 1)) {
      open += events[e].second;
      e++;
    }
  }
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
#endif
  solve_all_cases();
  //test();
}
