/**
https://blog.sengxian.com/algorithms/networkflow-variants
For a bipartite,
1. |Max Match| + |Min Edge Cover| == |V|
   In the max match, there are 2 * |Max Match| vertices are covered. So, there are |V| - 2 * |Max Match| not covered.
   After the max match, we need to add |V| - 2 * |Max Match| edges to cover all the vertices. (A edge can only cover 1 vertex,
   otherwise, the max match is not a max match). So, |Min Edge Cover| == |V| -  2 * |Max Match| + |Max Match| = |V| - |Max Match|
   -- (why based on max matching?)
2. |Max Independent Set| + |Min Vertex Cover| == |V|
   They are Complement for each other.

3. Kőnig's theorem: the maximum matching problem == the minimum vertex cover problem in bipartite graphs
  augmenting path

4. In a DAG, a minimum path cover can be solved by splitting the node u to u_in, u_out, with u->v as u_in->v_out, and then find
  the |Max Match|. Each original node is a path. A match is a merge between two different paths. So,
  |minimum path cover in a DAG| = |V in the DAG| - |Max Match in the splitted biparitite from the DAG|
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

struct Bipartite {
  Bipartite(int n1_, int n2_) {
    n1 = n1_;
    n2 = n2_;
    n = n1 + n2;
    g.assign(n, vector<int>());
    match.assign(n, -1);
  }
  void addedge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
  }
  int max_match() {
    int ret = 0;
    for(int i = 0; i < n1; i++) {
      vst.assign(n, 0);
      if (dfs(i)) ret++;
    }
    return ret;
  }
 private:
  int n1, n2, n;
  vector<vector<int>> g;
  vector<int> vst;
  vector<int> match;
  bool dfs(int u) {
    for(auto v : g[u]) {
      if (vst[v]) continue;
      vst[v] = 1;
      if (match[v] == -1 || dfs(match[v])) {
        match[v] = u;
        match[u] = v;
        return true;
      }
    }
    return false;
  }
};

void solve(int ncase) {
  int n, m, r, c;
  cin >> n >> m >> r >> c;
  vector<string> g(n);
  for(int i = 0; i < n; i++) {
    cin >> g[i];
  }
  vector<vector<int>> num(n, vector<int>(m, -1));
  int total = 0;
  for(int i = 0; i < n; i++) {
    for(int j  = 0; j < m; j++) {
      if (g[i][j] != 'x') {
        num[i][j] = total++;
      }
    }
  }
  Bipartite bg(total, total);
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if (g[i][j] != 'x') {
        set<PII> p;
        p.insert(PII(i + r, j + c));
        p.insert(PII(i + r, j - c));
        p.insert(PII(i + c, j + r));
        p.insert(PII(i + c, j - r));
        for(auto pp : p) {
          if (pp.first >= n || pp.second < 0 || pp.second >= m ||
              g[pp.first][pp.second] == 'x') {
            continue;
          }
          // add edge
          bg.addedge(num[i][j], num[pp.first][pp.second] + total);
        }
      }
    }
  }
  cout << total - bg.max_match() << endl;
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
 //  cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
