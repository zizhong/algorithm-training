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
const int N = 100010;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

vector<vector<int>> tree;
vector<PII> seg;

int dfs(int r, int pre, int left, int rleft) {
    int c = tree[r].size() - (pre > 0);
    seg[r] = PII(rleft, left + c + 1);
    int new_left = left + c + 1;
    int new_rleft = left + c;
    for(auto u : tree[r]) {
      if (u == pre) continue;
      new_left = dfs(u, r, new_left, new_rleft--);
    }
    return new_left;
}
void solve(int ncase) {
  int n;
  scanf("%d", &n);
  seg.assign(n + 1, PII(0,0));
  tree.assign(n + 1, vector<int>());
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  dfs(1, -1, 1, 1);
  for(int i = 1; i <= n; i++) {
    printf("%d %d\n", seg[i].first, seg[i].second);
  }
}

int main() {
  //ios::sync_with_stdio(false);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //freopen("out.txt", "w", stdout);
#endif
  //precalc();
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
