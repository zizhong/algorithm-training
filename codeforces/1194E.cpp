/**
* 1. with range increases, we need to deal with insertion and removal. but with range decrease, we only need to deal with insertion.
* 2. first right than left can save some initialization
* 3. cautionous with boundaries
* 4. segtree 1300ms bit 130ms
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
#include <iomanip>
#include <sstream>
#include <cmath>
#include <fstream>
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
//const int mod = 998244353;
const int inf = 0x3fffffff;
//const int N = 1e6 + 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
template<class T>
void debugvv(vector<vector<T>> &vv) {
  for (auto &v : vv) {
    for (auto &i : v) {
      cout << i << " ";
    }
    cout << endl;
  }
}

int n;
const int N = 10010, B = 5002;
int seg[(N + 10) << 2];

void init(int rt, int l, int r) {
  seg[rt] = 0;
  if (l == r) return;
  int m = (l + r) / 2;
  init(rt * 2, l, m);
  init(rt * 2 + 1, m + 1, r);
}

void update(int rt, int l, int r, int idx, int delta) {
  if (idx < l || idx > r) return;
  seg[rt] += delta;
  if (l == r) return;
  int m = (l + r) / 2;
  update(rt * 2, l, m, idx, delta);
  update(rt * 2 + 1, m + 1, r, idx, delta);
}

int query(int rt, int l, int r, int L, int R) {
  if (R < l || r < L) return 0;
  if (L <= l && r <= R) return seg[rt];
  int m = (l + r) / 2;
  return query(rt * 2, l, m, L, R) +
      query(rt * 2 + 1, m + 1, r, L, R);
}

int bit[N];

void update_bit(int x, int delta) {
  while (x < N) {
    bit[x] += delta;
    x += (x & -x);
  }
}

int query_bit(int x) {
  int ret = 0;
  while (x > 0) {
    ret += bit[x];
    x -= (x & -x);
  }
  return ret;
}

void solve(int ncase) {
  scanf("%d", &n);
  vector<PIP> v;
  vector<PIP> h;
  for (int i = 0; i < n; i++) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    x1 += B;
    y1 += B;
    x2 += B;
    y2 += B;
    if (x1 == x2) {
      if (y1 > y2) swap(y1, y2);
      v.emplace_back(PIP(x1, PII(y1, y2)));
    } else {
      if (x1 > x2) swap(x1, x2);
      h.emplace_back(x1, PII(x2, y1));
    }
  }
  sort(v.begin(), v.end());
  sort(h.begin(), h.end());
  ll ans = 0;
  for (size_t i = 0; i < v.size(); i++) {
    //init(1, 1, N);
    memset(bit, 0, sizeof(bit));
    int xr = v[i].first;
    int yr1 = v[i].second.first;
    int yr2 = v[i].second.second;
    for (int j = 0, k = 0; j < i; j++) {
      while (k < h.size() && h[k].first <= v[j].first) {
        if (h[k].second.first < xr ||
            h[k].second.second < yr1 ||
            h[k].second.second > yr2) {
          k++;
          continue;
        }
        update_bit(h[k].second.second, 1);
        //update(1, 1, N, h[k].second.second, 1);
        k++;
      }
      //int cnt = query(1, 1, N, v[j].second.first, v[j].second.second);
      int cnt = query_bit(v[j].second.second) - query_bit(v[j].second.first - 1);
      ans += 1LL * cnt * (cnt - 1) / 2;
    }
  }
  printf("%lld\n", ans);
}

void solve_all_cases() {
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}

int main() {
  //ios::sync_with_stdio(false);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
  auto start_time = clock();
#endif
  solve_all_cases();
  //test();
#ifdef _zzz_
  cout << (clock() - start_time) * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
#endif
}
