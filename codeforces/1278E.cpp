/*
 * Given a tree with 2 * n nodes. Split nodes into n pairs, to maximize / minimize Sigma(length of path between a pair).
 * Consider an edge E in the tree, which connects two parts, A and B.
 * If there are at least one pair of nodes completely falls into one pair for each part, we can reassign the nodes to let each pair
 *   goes through edge E, and the cost will be at least increase by 2 * E.cost. So, for each edge, in the optimal solution, it contributes
 *   E.cost * min(|A|, |B|).
 * In the minizied optimal solution, an edge E cannot be added more than 1 time. Otherwise, we can reassign the nodes to connect inside
 *   the part to decrease 2 times * E.cost. We can repeat this operation, so in the final solution, the edge E contributes E.cost * (|A| % 2).
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

struct Edge {
  int b, t;
  Edge(int b_, int t_): b(b_), t(t_) {}
};
int n;
vector<vector<Edge>> tree;
ll min_ans, max_ans;

int dfs(int r, int pre) {
  int num = 1;
  for(auto& e : tree[r]) {
    if (e.b == pre) continue;
    int c = dfs(e.b, r);
    if (c % 2 == 1) {
      min_ans += e.t;
    }
    max_ans += min(c, 2 * n - c) * 1LL * e.t;
    num += c;
  }
  return num;
}

void solve(int ncase) {
  scanf("%d", &n);
  tree.assign(n * 2 + 1, vector<Edge>());
  for(int i = 0; i < 2 * n - 1; i++) {
    int a, b, t;
    scanf("%d%d%d", &a, &b, &t);
    tree[a].push_back(Edge(b, t));
    tree[b].push_back(Edge(a, t));
  }
  min_ans = 0;
  max_ans = 0;
  dfs(1, -1);
  cout << min_ans << " " << max_ans << endl;
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
  scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
