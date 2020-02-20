/**
*   // Link: https://codeforces.com/contest/1304/problem/E
*   // LCA to answer the query of distance a pair of vertices in a tree.
*   // consider possible paths in a tree ... 
*   // initially model this question wrongly as in list. actually it's in tree.
*   // initially using a case based discussion, and cases exploded. Actually the cases can be summarized and abstracted to a few advanced case.
*   // instead of being too specific, too special, too simple, from a different angle, using advance term could result the final advanced cases.
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

const int MAXN = 100010;
int E[2 * MAXN];
int R[MAXN];
int L[2 * MAXN];
int d[2 * MAXN][18];
vector<int> tree[MAXN];
int tot, visited[MAXN];
void create_table() {
  for (int j = 0; (1 << j) <= tot; j++)
    for (int i = 0; i + (1 << j) <= tot; i++) {
      if (j == 0) d[i][j] = i;
      else {
        if (L[d[i][j - 1]] < L[d[i + (1 << (j - 1))][j - 1]])
          d[i][j] = d[i][j - 1];
        else
          d[i][j] = d[i + (1 << (j - 1))][j - 1];
      }
    }
}
void dfs(int u, int pre, int deep) {
  if (!visited[u]) {
    visited[u] = 1;
    R[u] = tot;
  }
  E[tot] = u;
  L[tot++] = deep;
  vector<int>::size_type ix, size = tree[u].size();
  for (ix = 0; ix != size; ix++) {
    if (tree[u][ix] == pre) continue;
    dfs(tree[u][ix], u, deep + 1);
    E[tot] = u;
    L[tot++] = deep;
  }
}
int rmq(int v1, int v2) {
  int k = 0;
  while ((1 << (k + 1)) < (v2 - v1 + 1))
    k++;
  if (L[d[v1][k]] < L[d[v2 - (1 << k) + 1][k]])
    return E[d[v1][k]];
  else
    return E[d[v2 - (1 << k) + 1][k]];
}
int lca(int v1, int v2) {
  if (R[v1] < R[v2])
    return rmq(R[v1], R[v2]);
  else
    return rmq(R[v2], R[v1]);
}

int dis(int v1, int v2) {
  return L[R[v1]] + L[R[v2]] - 2 * L[R[lca(v1, v2)]];
}

// if b + 2 * i + c * j == k
bool okay(int b, int c, int k) {
    if (k < b) return false;
    if ((k - b) % 2 == 0) return true;
    if (c % 2 == 0) return false;
    return (k - b >= c);
}

bool okay_path(int a, int x, int y, int b, int c, int k) {
  return okay(dis(a, x) + 1 + dis(y, b), c, k) ||
    okay(dis(a, x) + dis(x, y) + dis(y, b), c, k);
}

void solve(int ncase) {
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  dfs(1, -1, 0);
  create_table();
  int q;
  scanf("%d", &q);
  while(q--) {
    int x, y, a, b, k;
    scanf("%d%d%d%d%d", &x, &y, &a, &b, &k);

    int c = dis(x, y) + 1;
    if (okay(dis(a, b), 0, k) || okay_path(a, x, y, b, c, k) || okay_path(a, y, x, b, c, k)) {
      puts("YES");
    } else {
      puts("NO");
    }
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
