/*
*  Build a graph, BFS from "leaf" / source nodes to all other nodes. 
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
const int N = 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

int n;
int d[N * 2];
int f[N * 2];
bool leaf(int x) {
  return (x - d[x] >= 0 && (d[x - d[x]] % 2 != d[x] % 2)) ||
      (x + d[x] < n && (d[x + d[x]] % 2 != d[x] % 2));
}
void solve(int ncase) {
  scanf("%d", &n);
  vector<vector<int>> from(n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &d[i]);
    f[i] = -1;
  }
  for(int i = 0; i < n; i++) {
    if (i - d[i] >= 0 && d[i] % 2 == d[i - d[i]] % 2) {
      from[i-d[i]].push_back(i);
    }
    if (i + d[i] < n && d[i] % 2 == d[i + d[i]] % 2) {
      from[i+d[i]].push_back(i);
    }
  }
  queue<int> q;
  for(int i = 0; i < n; i++) {
    if (leaf(i)) {
      f[i] = 1;
      q.push(i);
    }
  }
  while(!q.empty()) {
    auto head = q.front();
    q.pop();
    for(auto c : from[head]) {
      if (f[c] != -1) continue;
      f[c] = f[head] + 1;
      q.push(c);
    }
  }
  for(int i = 0; i < n; i++) {
    printf("%d ", f[i]);
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
