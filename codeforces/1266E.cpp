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

void solve(int ncase) {
  int n;
  scanf("%d", &n);
  vector<int> a(n + 1);
  ll ans = 0;
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    ans += a[i];
  }
  int q;
  scanf("%d", &q);
  map<PII, int> z;
  while(q--) {
    int s, t, u;
    scanf("%d%d%d", &s, &t, &u);
    auto it = z.find(PII(s, t));
    if (it != z.end()) {
      // remove it->second
      int pre = max(0, a[it->second]);
      a[it->second]++;
      ans += max(0, a[it->second]) - pre;
      z.erase(it);
    }
    if (u == 0) {
      printf("%I64d\n", ans);
      continue;
    }
    z[PII(s, t)] = u;
    // add u
    int pre = max(0, a[u]);
    a[u]--;
    ans += max(0, a[u]) - pre;
    printf("%I64d\n", ans);
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
