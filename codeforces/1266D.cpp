/*
* invariant -> the balance of each person
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
const int inf = 0x3fffffff;
const int N = 1e5 + 10;
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
  vector<vector<PIL>> tree(n + 1);
  vector<ll> bal(n + 1);
  for(int i = 0; i < m; i++) {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    bal[x] += z;
    bal[y] -= z;
  }
  vector<PLP> edge;
  for(int i = 1, j = 1; i <= n; i++) {
    if (bal[i] <= 0) continue;
    if (j > n) break;
    while(bal[i] > 0) {
      while (j <= n && bal[j] >= 0) {
        j++;
      }
      if (j > n) break;
      ll z = min(bal[i], -bal[j]);
      bal[i] -= z;
      bal[j] += z;
      edge.emplace_back(z, PII(i, j));
    }
  }
  printf("%d\n", edge.size());
  for(auto &p : edge) {
    printf("%d %d %I64d\n", p.second.first, p.second.second, p.first);
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
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
