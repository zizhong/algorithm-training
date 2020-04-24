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

vector<vector<int>> tree;
int n;
tuple<ll, ll, ll> dfs(int u, int pre) {
  ll ret = 0;
  ll ch = 1;
  ll ans_sub = 0;
  vector<tuple<ll, ll, ll>> vp;
  for (auto v : tree[u]) {
    if (v == pre) continue;
    vp.push_back(dfs(v, u));
  }
  for (auto &t : vp) {
    ch += get<1>(t);
    ans_sub += get<2>(t);
  }
  for (auto &t : vp) {
    ret = max(ret, get<0>(t) + n - get<1>(t) + ans_sub - get<2>(t));
  }

  ans_sub += ch;
  if (vp.empty()) {
    ret = n;
    ans_sub = 1;
  }
  //cout << u << " " << ret << " " << ch << " " << ans_sub << endl;
  return tie(ret, ch, ans_sub);
}

void solve(int ncase) {
  scanf("%d", &n);
  tree.assign(n + 1, vector<int>());
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    tree[x].push_back(y);
    tree[y].push_back(x);
  }
  ll ans = 0;
  tie(ans, ignore, ignore) = dfs(1, -1);
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
