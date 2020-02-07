/**
1. considering about state transform from x to x + 1.
2. considering about the other end of the relationship.
3. Segment tree + lazy update
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
 
const int N = 2 * 100010;
int n;
int p[N], a[N], pos[N];
ll zero[N];
ll ans;
struct SegmentTree {
  SegmentTree(int total) {
    n = total;
    mins.assign(4 * total, 0);
    lazy.assign(4 * total, 0);
    init(1, n, 1);
  }
  void pushUp(int l, int r, int rt) {
    mins[rt] = min(mins[rt * 2], mins[rt * 2 + 1]);
  }
  void pushDown(int l, int r, int rt) {
    int lc = rt * 2;
    int rc = rt * 2 + 1;
    lazy[lc] += lazy[rt];
    lazy[rc] += lazy[rt];
    mins[lc] += lazy[rt];
    mins[rc] += lazy[rt];
    lazy[rt] = 0;
  }
  void init(int l, int r, int rt) {
    if (l == r) {
      mins[rt] = zero[l];
      return;
    }
    int m = (l + r) / 2;
    init(l, m, rt * 2);
    init(m + 1, r, rt * 2 + 1);
    pushUp(l, r, rt);
  }
  void update(int l, int r, int rt, int L, int R, int d) {
    if (L > R) return;
    if (l == r || L <= l && r <= R) {
      lazy[rt] += d;
      mins[rt] += d;
      return;
 
    }
    int m = (l + r) / 2;
    pushDown(l, r, rt);
    if (L <= m) update(l, m, rt * 2, L, R, d);
    if (m+1 <= R) update(m + 1, r, rt * 2 + 1, L, R, d);
    pushUp(l, r, rt);
  }
  ll query(int l, int r, int rt, int L, int R) {
    if (l == r || L <= l && r <= R) {
      return mins[rt];
    }
    pushDown(l, r, rt);
    int m = (l + r) / 2;
    ll z = 1e18;
    if (L <= m) {
      z = min(z, query(l, m, rt * 2, L, R));
    }
    if (m + 1 <= R) {
      z = min(z, query(m + 1, r, rt * 2 + 1, L, R));
    }
    pushUp(l, r, rt);
    return z;
  }
  int n;
  vector<ll> mins;
  vector<ll> lazy;
};
void solve(int ncase) {
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &p[i]);
    pos[p[i]] = i;
  }
  zero[0] = 0;
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    zero[i] = zero[i - 1] + a[i];
  }
  ans = min(a[1], a[n]);
  SegmentTree st(n);
 
  for(int i = 1; i < n; i++) {
 
    st.update(1, n-1, 1, 1, pos[i] - 1, a[pos[i]]);
    st.update(1, n-1, 1, pos[i], n, -a[pos[i]]);
    //cout << st.mins[1] << endl;
    ans = min(ans, st.mins[1]);
  }
  cout << ans << endl;
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
