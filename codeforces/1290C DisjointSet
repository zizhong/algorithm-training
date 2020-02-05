/*
https://codeforces.com/contest/1290/problem/C
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
typedef pair<ll, ll> PLL;
typedef pair<double, double> PDD;
typedef pair<ll, PII> PLP;
#define CLS(x, v) (memset((x), (v), sizeof((x))))
const double pi = acos(-1);
const int mod = 1000000007;
const int inf = 0x3fffffff;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
const int N = 3 * 100000 + 10;

int n, k;
char str[N];
vector<vector<int>> tree;
struct DisjointSet{
  DisjointSet(int sz) {
    this->sz = sz;
    f.assign(sz, -1);
  }
  virtual ~DisjointSet() {}
  int root(int x) {
    if (f[x] < 0) {
      return x;
    }
    return f[x] = root(f[x]);
  }

  virtual void join(int x, int y) {
    int rx = root(x);
    int ry = root(y);
    if (rx == ry) return;
    int total = f[rx] + f[ry];
    if (f[rx] < f[ry]) {
      f[ry] = rx;
      f[rx] = total;
    } else {
      f[rx] = ry;
      f[ry] = total;
    }
  }
 private:
  int sz;
  vector<int> f;
};

struct DisjointSetWithClick : public DisjointSet {
  // 0 ... k - 1 represents the reality that i is not clicked
  // k ... 2*k - 1 represents the reality that i - k is clicked
  DisjointSetWithClick() : DisjointSet(2 * k) {
    click.assign(2 * k , 0);
    for(int i = k; i < 2 * k; i++) {
      click[i] = 1;
    }
    ans = 0;
    status.assign(2 * k, -1);
  }

  void join(int x, int y) override {
    int rx = root(x);
    int ry = root(y);
    if (rx == ry) return;
    DisjointSet::join(x, y);
    int new_rx = root(x);
    if (new_rx == rx) {
      click[rx] += click[ry];
    } else {
      click[ry] += click[rx];
    }
  }
  void addEdge(int u, int v) {
    int not_u = not_x(u);
    int not_v = not_x(v);
    int pre_r_u = root(u);
    int pre_r_v = root(v);
    if (pre_r_u == pre_r_v) return;
    // all new
    if (status[pre_r_u] == -1 && status[pre_r_v] == -1) {
      join(u, v);
      join(not_u, not_v);
      int root_u = root(u);
      int root_not_u = root(not_u);
      status[root_u] = status[root_not_u] = 2;
      ans += min(click[root_u], click[root_not_u]);
      return;
    }
    // one new
    if (status[pre_r_u] == -1 || status[pre_r_v] == -1) {
      int new_x = (status[pre_r_u] == -1 ? u : v);
      int old_x = u + v - new_x;
      if (status[root(old_x)] == 2) {
        int pre_c = min(click[root(old_x)], click[root(not_x(old_x))]);
        join(u, v);
        join(not_u, not_v);
        status[root(u)] = status[root(not_u)] = 2;
        ans += min(click[root(u)], click[root(not_u)]) - pre_c;
      } else if (status[root(old_x)] == 1) {
        int pre_c = click[root(old_x)];
        join(u, v);
        join(not_u, not_v);
        status[root(new_x)] = 1;
        status[root(not_x(new_x))] = 0;
        ans += click[root(new_x)] - pre_c;
      } else {
        int pre_c = click[root(not_x(old_x))];
        join(u, v);
        join(not_u, not_v);
        status[root(new_x)] = 0;
        status[root(not_x(new_x))] = 1;
        ans += click[root(not_x(new_x))] - pre_c;
      }
      return;
    }
    // no new
    if (status[pre_r_u] == 2 && status[pre_r_v] == 2) {
      int pre_c = min(click[pre_r_u], click[not_x(pre_r_u)]) + min(click[pre_r_v], click[not_x(pre_r_v)]);
      join(u, v);
      join(not_u, not_v);
      status[root(u)] = status[root(not_u)] = 2;
      ans += min(click[root(u)], click[root(not_u)]) - pre_c;
      return;
    }
    if (status[pre_r_u] != 2 && status[pre_r_v] != 2) {
      return;
    }
    int nd_x = (status[pre_r_u] == 2 ? u : v);
    int d_x = u + v - nd_x;
    int pre_c = status[root(d_x)] == 1 ? click[root(d_x)] : click[root(not_x(d_x))];
    pre_c += min(click[root(nd_x)], click[root(not_x(nd_x))]);
    int nc = 0;
    if (status[root(d_x)] == 1) {
      join(nd_x, d_x);
      join(not_x(nd_x), not_x(d_x));
      status[root(nd_x)] = 1;
      status[root(not_x(nd_x))] = 0;
      nc = click[root(nd_x)];
    } else {
      join(nd_x, d_x);
      join(not_x(nd_x), not_x(d_x));
      status[root(not_x(nd_x))] = 1;
      status[root(nd_x)] = 0;
      nc = click[root(not_x(nd_x))];
    }
    ans += nc - pre_c;
  }

  void addPoint(int key) {
    // add key to entry_point
    int root_key = root(key);
    int not_key = not_x(key);
    int root_not_key = root(not_key);
    int pre_c = 0;

    if (status[root_key] == 1) {
      return;
    }
    if (status[root_key] == 2) {
      pre_c += min(click[root_key], click[root_not_key]);
    }
    status[root_key] = 1;
    status[root_not_key] = 0;
    ans += click[root_key] - pre_c;
    return;
  }
  void handle(int idx) {
    if (tree[idx].empty()) return;
    if (tree[idx].size() == 1) {
      int key = tree[idx][0];
      if (str[idx] == '0') {
        key += k;
      }
      addPoint(key);
      return;
    }

    if (tree[idx].size() == 2) {
      if (str[idx] == '1') {
        addEdge(tree[idx][0], tree[idx][1]);
      } else {
        addEdge(tree[idx][0] + k, tree[idx][1]);
      }
    }
  }
  int not_x(int x) {return (x + k) % (2 * k);}

  int ans;
 private:
  vector<int> click;
  vector<int> status;
};

void solve(int ncase) {
  scanf("%d%d%s", &n, &k, str);
  tree.assign(n, vector<int>());
  for(int i = 0; i < k; i++) {
    int t;
    scanf("%d", &t);
    while(t--) {
      int x;
      scanf("%d", &x);
      tree[x-1].push_back(i);
    }
  }

  DisjointSetWithClick djs;
  for(int i = 0; i < n; i++) {
    djs.handle(i);
    printf("%d\n", djs.ans);
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
  // cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
