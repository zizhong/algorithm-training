/***
* To check two given array a, b, if b can be obtain by sorting arbitrary times of arbitrary subarrays.
* 
/

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

template<typename C>
struct reverse_wrapper {

  C &c_;
  reverse_wrapper(C &c) : c_(c) {}

  typename C::reverse_iterator begin() { return c_.rbegin(); }
  typename C::reverse_iterator end() { return c_.rend(); }
};

template<typename C>
reverse_wrapper<C> r_wrap(C &c) {
  return reverse_wrapper<C>(c);
}

const int N = 3 * 1e5;
int seg[4 * N + 100];
void init(int rt, int l, int r) {
  seg[rt] = inf;
  if (l == r) return;
  int mid = (l + r) / 2;
  init(rt * 2, l, mid);
  init(rt * 2 + 1, mid + 1, r);
}

void update(int rt, int l, int r, int x, int v) {
  if (x < l || r < x) return;
  if (l == r) {
    seg[rt] = v;
    return;
  }
  int mid = (l + r) / 2;
  if (x <= mid) update(rt * 2, l, mid, x, v);
  else update(rt * 2 + 1, mid + 1, r, x, v);
  seg[rt] = min(seg[rt * 2], seg[rt * 2 + 1]);
  //printf("update %d [%d %d] [%d %d] %d\n", rt, l, r, x, v, seg[rt]);
}

int query(int rt, int l, int r, int L, int R) {
  //printf("query %d [%d %d] [%d %d] %d\n", rt, l, r, L, R, seg[rt]);
  if (R < l || r < L) return inf;
  if (L <= l && r <= R) return seg[rt];
  int mid = (l + r) / 2;
  return min(query(rt * 2, l, mid, L, R),
             query(rt * 2 + 1, mid + 1, r, L, R));
}

void solve(int ncase) {
  int n;
  scanf("%d", &n);

  map<int, vector<int>> m1;
  vector<int> b(n);
  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    m1[x].push_back(i);
  }

  for (int i = 0; i < n; i++) {
    scanf("%d", &b[i]);
  }

  map<int, int> int_idx;
  int idx = 1;
  for (auto &p: m1) {
    int_idx[p.first] = idx++;
  }
  int K = idx - 1;
  init(1, 1, K);
  map<int, int> m1_idx;
  for (auto p : m1) {
    update(1, 1, K, int_idx[p.first], p.second[0]);
    m1_idx[p.first] = 0;
  }
  for (int i = 0; i < n; i++) {
    if (int_idx.find(b[i]) == int_idx.end()) {
      puts("NO");
      return;
    }
    int k = int_idx[b[i]];
    if (m1_idx[b[i]] == m1[b[i]].size()) {
      puts("NO");
      return;
    }
    int pos = m1[b[i]][m1_idx[b[i]]];
    //cout << i << " " << b[i] << " " << k << " " << query(1, 1, K, 1, k - 1) << " " << pos << endl;
    if (query(1, 1, K, 1, k - 1) < pos) {
      puts("NO");
      return;
    }
    m1_idx[b[i]]++;
    update(1, 1, K, k, (m1_idx[b[i]] == m1[b[i]].size() ? inf : m1[b[i]][m1_idx[b[i]]]));
  }
  puts("YES");
}

void solve_all_cases() {
  int T = 1;
  scanf("%d", &T);
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
