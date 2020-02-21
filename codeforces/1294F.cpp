/*
*  https://codeforces.com/contest/1294/problem/F
*  choose v1, v2, v3 in a tree to get a max possible union of |v1..v2, v1..v3, v2..v3|.
*  After some analysis, the answer is max path + second max half path. (By Contradiction)
*  using DP can calculate the anwser for each subtree where the max_path goes through the root.
*  The answer for each substree is 1st max half path + second max half path + max(third max half path, second max from subtrees).
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
 
int ans;
vector<int> ans_leaf;
vector<vector<int>> tree;
 
struct State{
  int max_path = -1;
  int max_path_leaf = -1;
  int second_path = -1;
  int second_path_leaf = -1;
};
 
State dp(int r, int pre) {
  State ret;
  int max_second = 0;
  int max_second_leaf = 0;
  bool leaf = true;
  vector<PII> max_path;
  for(auto ch : tree[r]) {
    if (ch == pre) continue;
    leaf = false;
    State ch_ret = dp(ch, r);
    //cout << r << " " << ch << " " << ch_ret.max_path << " " << ch_ret.max_path_leaf << " "<< ch_ret.second_path << " " << ch_ret.second_path_leaf << endl;
    max_path.push_back(PII(ch_ret.max_path, ch_ret.max_path_leaf));
    int idx = max_path.size() - 1;
    while (idx - 1 >= 0 && max_path[idx-1] < max_path[idx]) {
      swap(max_path[idx], max_path[idx - 1]);
      idx--;
    }
    if (max_path.size() > 3) max_path.pop_back();
    if (ch_ret.second_path > max_second) {
      max_second = ch_ret.second_path;
      max_second_leaf = ch_ret.second_path_leaf;
    }
  }
  if (leaf) {
    ret.max_path = 0;
    ret.max_path_leaf = r;
    return ret;
  }
  int tmp = 0;
  vector<int> vleaf;
  for(int i = 0; i < 2 && i < max_path.size(); i++) {
    tmp += max_path[i].first + 1;
    vleaf.push_back(max_path[i].second);
  }
  if (max_path.size() < 2) vleaf.push_back(r);
  if (2 < max_path.size() && max_path[2].first + 1 > max_second) {
    max_second = max_path[2].first + 1;
    max_second_leaf = max_path[2].second;
  }
  if (tmp + max_second > ans) {
    ans = tmp + max_second;
    ans_leaf = vleaf;
    ans_leaf.push_back(max_second_leaf);
  }
  if (1 < max_path.size() && max_path[1].first + 1> max_second) {
    max_second = max_path[1].first + 1;
    max_second_leaf = max_path[1].second;
  }
  ret.max_path = max_path[0].first + 1;
  ret.max_path_leaf = max_path[0].second;
  ret.second_path = max_second;
  ret.second_path_leaf = max_second_leaf;
  return ret;
}
 
void solve(int ncase) {
  int n;
  scanf("%d", &n);
  tree.assign(n + 1, vector<int>());
  for(int i = 0; i < n-1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  dp(1, -1);
  if (ans_leaf[2] == 0) {
    for(int i = 1; i <= n; i++) {
      if (ans_leaf[1] != i && ans_leaf[0] != i) {
        ans_leaf[2] = i;
        break;
      }
    }
  }
  cout << ans << endl << ans_leaf[0] << " " << ans_leaf[1] << " " << ans_leaf[2] << endl;
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
