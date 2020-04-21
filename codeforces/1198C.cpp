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
const int N = 1e6 + 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

void solve(int ncase) {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<PII> edge(m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &edge[i].first, &edge[i].second);
  }
  vector<int> removed(3 * n + 1);
  vector<int> match;
  int idx = 0;
  for (auto &e : edge) {
    idx++;
    if (removed[e.first] == 0 && removed[e.second] == 0) {
      removed[e.first] = 1;
      removed[e.second] = 1;
      match.push_back(idx);
      if (match.size() == n) break;
    }
  }
  if (match.size() == n) {
    puts("Matching");
    for (auto x : match) printf("%d ", x);
    puts("");
  } else {
    puts("IndSet");
    idx = 0;
    for (int i = 1; i <= 3 * n && idx < n; i++) {
      if (removed[i]) continue;
      printf("%d ", i);
      idx++;
    }
    puts("");
  }
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
