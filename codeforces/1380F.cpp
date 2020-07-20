/**
* 1. Segment Tree. The most important part is how to merge two parts.
* 2. When merged, edges cases need to be carefully handled.
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
#include <bitset>
#include <complex>
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

template<class TH>
void _dbg(const char *sdbg, TH h) { cerr << sdbg << '=' << h << endl; }
template<class TH, class... TA>
void _dbg(const char *sdbg, TH h, TA... a) {
  while (*sdbg != ',')cerr << *sdbg++;
  cerr << '=' << h << ',';
  _dbg(sdbg + 1, a...);
}

template<class T>
ostream &operator<<(ostream &os, vector<T> V) {
  os << "[";
  for (auto vv : V) os << vv << ",";
  return os << "]";
}
template<class L, class R>
ostream &operator<<(ostream &os, pair<L, R> P) {
  return os << "(" << P.first << "," << P.second << ")";
}

#ifdef _zzz_
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class T>
using max_heap = priority_queue<T>;
//const int mod = 1000000007;
const int mod = 998244353;

//const int N = 1e6 + 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
const int N = 5 * 100010;

int way[20];
int n, m;
char str[N];
struct Seg {
  // l, r
  int cnt;
  // l, r - 1
  int cnt_a;
  // l + 1, r
  int cnt_b;
  // l + 1, r - 1
  int cnt_c;
  Seg() {
    cnt = 0;
    cnt_a = cnt_b = cnt_c = 1;
  }
};

Seg seg[N * 4];
int mul(int a, int b) {
  return a * 1LL * b % mod;
}
int add(int a, int b) {
  int ret = a + b;
  if (ret >= mod) ret -= mod;
  return ret;
}
void push_up(int rt, int l, int r) {
  auto &cur = seg[rt];
  const auto &left = seg[rt * 2];
  const auto &right = seg[rt * 2 + 1];
  int mid = (l + r) / 2;
  int merge_num = (str[mid] - '0') * 10 + (str[mid + 1] - '0');
  int merge_cnt = ((merge_num < 10 || merge_num > 18) ? 0 : way[merge_num]);
  int length = r - l + 1;
  int left_length = mid - l + 1;
  int right_length = length - left_length;
  // cnt = left.cnt * right.cnt + merge_cnt * left.cnt_a * right.cnt_b
  cur.cnt = mul(left.cnt, right.cnt);
  if (merge_cnt) {
    cur.cnt = add(cur.cnt, mul(merge_cnt, mul(left.cnt_a, right.cnt_b)));
  }
  // cnt_a = left.cnt * right.cnt_a + merge_cnt * left.cnt_a * right.cnt_c
  cur.cnt_a = mul(left.cnt, right.cnt_a);
  if (merge_cnt && right_length > 1) {
    cur.cnt_a = add(cur.cnt_a, mul(merge_cnt, mul(left.cnt_a, right.cnt_c)));
  }
  // cnt_b = left.cnt_b * right.cnt + merge_cnt * left.cnt_c * right.cnt_b
  cur.cnt_b = mul(left.cnt_b, right.cnt);
  if (merge_cnt && left_length > 1) {
    cur.cnt_b = add(cur.cnt_b, mul(merge_cnt, mul(left.cnt_c, right.cnt_b)));
  }
  // cnt_c = left.cnt_b * right.cnt_a + merge_cnt * left.cnt_c * right.cnt_c
  cur.cnt_c = mul(left.cnt_b, right.cnt_a);
  if (merge_cnt && left_length > 1 && right_length > 1) {
    cur.cnt_c = add(cur.cnt_c, mul(merge_cnt, mul(left.cnt_c, right.cnt_c)));
  }
}

void init(int rt, int l, int r) {
  if (l == r) {
    seg[rt].cnt = way[str[l] - '0'];
    return;
  }
  int mid = (l + r) / 2;
  init(rt * 2, l, mid);
  init(rt * 2 + 1, mid + 1, r);
  push_up(rt, l, r);
}

void update(int rt, int l, int r, int idx) {
  if (l > idx || r < idx) return;
  if (l == r) {
    seg[rt].cnt = way[str[l] - '0'];
    return;
  }
  int mid = (l + r) / 2;
  update(rt * 2, l, mid, idx);
  update(rt * 2 + 1, mid + 1, r, idx);
  push_up(rt, l, r);
}

void solve(int ncase) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      way[i + j]++;
    }
  }
  scanf("%d%d%s", &n, &m, str + 1);

  init(1, 1, n);

  while (m--) {
    int idx, x;
    scanf("%d%d", &idx, &x);
    if (str[idx] == '0' + x) {
      printf("%d\n", seg[1].cnt);
      continue;
    }
    str[idx] = '0' + x;
    update(1, 1, n, idx);
    printf("%d\n", seg[1].cnt);
    //printf("[%s] %d\n", str + 1, seg[1].cnt);
  }
}

void solve_all_cases() {
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  //pre_calc();
  while (T--) {
    solve(++ncase);
  }
}

int main() {
  //ios_base::sync_with_stdio(0);
  //cin.tie(0);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  ios_base::sync_with_stdio(true);
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
  auto start_time = clock();
#endif
  solve_all_cases();
  //test();
#ifdef _zzz_
  cout << (clock() - start_time) * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
#endif
}
