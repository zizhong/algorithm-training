/*
 *  Scanline + Set to figure out the opened segments with the right end less than L.
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
 
int n;
vector<PII> e;
vector<vector<int>> tree;
vector<bool> visited;
int num_e;
 
void dfs(int r, int pre) {
  if (visited[r]) return;
  visited[r] = true;
  for(auto x : tree[r]) {
    if (r == pre) continue;
    dfs(x, r);
  }
}
 
void solve(int ncase) {
  scanf("%d" ,&n);
  e.assign(n * 2, PII(0, 0));
  for(int i = 0; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    e[i] = PII(x, i);
    e[i + n] = PII(y, i);
  }
  vector<PII> sorted_e_by_start = e;
  sort(sorted_e_by_start.begin(), sorted_e_by_start.end());
  tree.assign(n, vector<int>());
  num_e = 0;
  set<PII> open_by_end;
  for(auto& ev : sorted_e_by_start) {
    if (num_e > n - 1) break;
    PII seg_end(e[ev.second + n].first, ev.second);
    if (open_by_end.find(seg_end) != open_by_end.end()) {
      open_by_end.erase(seg_end);
    } else {
      for(const auto& seg_end_i : open_by_end) {
        if (seg_end_i.first > seg_end.first) break;
        num_e++;
        if (num_e > n - 1) break;
        tree[seg_end_i.second].push_back(seg_end.second);
        tree[seg_end.second].push_back(seg_end_i.second);
      }
      open_by_end.insert(seg_end);
    }
  }
  if (num_e != n - 1) {
    cout << "NO" << endl;
    return;
  }
  visited.assign(n, false);
  dfs(0, -1);
  cout << (count(visited.begin(), visited.end(), true) == n ? "YES" : "NO") << endl;
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
