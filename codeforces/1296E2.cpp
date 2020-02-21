/*  https://codeforces.com/problemset/problem/1296/E2
 * Greedy + bitmask
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
 
void solve(int ncase) {
  int n;
  string s;
  cin >> n >> s;
  vector<int> v(26);
  vector<int> d(n);
  for(int i = s.size() - 1; i >= 0; i--) {
    int maxe = 0;
    for(int j = s[i] - 'a' - 1; j>= 0; j--) {
      maxe |= v[j];
    }
    for(int k = 0; k < 26; k++) {
      if ((1<<k) & maxe) continue;
      d[i] = k + 1;
      v[s[i] - 'a'] = (maxe | (1<<k));
      break;
    }
  }
  printf("%d\n", *max_element(d.begin(), d.end()));
  for(int i = 0; i < n; i++) printf("%d ", d[i]);
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
