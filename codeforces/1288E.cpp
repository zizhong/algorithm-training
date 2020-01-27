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


struct BIT {
  BIT(int n) {
    a.assign(n + 1, 0);
  }
  ll sum(int x) {
    ll ret = 0;
    while(x > 0) {
      ret += a[x];
      x -= low_bit(x);
    }
    return ret;
  }
  void add(int x, ll delta) {
    while(x < a.size()) {
      a[x] += delta;
      x += low_bit(x);
    }
  }
  vector<ll> a;
  static int low_bit(int x){return x&(-x);}
};

void solve(int ncase) {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> event(n + m + 1);

  for(int i = m; i >= 1; i--) {
    scanf("%d", &event[i]);
  }
  for(int i = m + 1; i <= m + n; i++) {
    event[i] = i - m;
  }

  vector<int> min_pos(n + 1), max_pos(n + 1), pos(n + 1);
  for(int i = 1; i <= n; i++) {
    min_pos[i] = i;
  }
  for(int i = 1; i <= m; i++) {
    min_pos[event[i]] = 1;
  }

  BIT bit(n + m);
  for(int i = 1; i <= m + n; i++) {
    int d = event[i];
    if (pos[d] <= 0) {
      max_pos[d] = max(max_pos[d] * 1LL, bit.sum(n + m) + 1);
    } else {
      max_pos[d] = max(max_pos[d] * 1LL, bit.sum(n + m) - bit.sum(pos[d]) + 1);
      bit.add(pos[d], -1);
    }
    pos[d] = i;
    bit.add(pos[d], 1);
  }
  for(int i = 1; i <= n; i++) {
    printf("%d %d\n", min_pos[i], max_pos[i]);
  }
}

int main() {
  //ios::sync_with_stdio(false);
  //cout << std::fixed;
  //cout << setprecision(9);
#ifdef _zzz_
 //freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
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
