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
#include <numeric>
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

//const int mod = 998244353;
const int mod = 1e9 + 7;
//const int N = 1e6 + 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
const int N = 2 * 100010;
int tp[N], d[N];
vector<int> vv;
struct SegNode {
  int nx, ny;
  ll sum;
  SegNode() {
    nx = 0;
    ny = 0;
    sum = 0;
  }
  SegNode merge(const SegNode &rhs) {
    SegNode ret;
    ret.nx = nx + rhs.nx;
    ret.ny = ny + rhs.ny;
    ret.sum = sum + rhs.sum;
    return ret;
  }
  void update(int pos, int delta, int tp) {
    if (tp == 0) nx += delta;
    else ny += delta;
    sum += delta * 1LL * vv[pos - 1];
  }
};
struct SegTree {
  vector<SegNode> v;
  SegTree(int n) {
    v.assign(n * 4 + 10, SegNode());
  }
  inline int lc(int idx) { return 2 * idx; }
  inline int rc(int idx) { return 2 * idx + 1; }
  void update(int idx, int l, int r, int pos, int delta, int tp) {
    if (pos < l || pos > r) return;
    if (l == r) {
      v[idx].update(pos, delta, tp);
      return;
    }
    int m = (l + r) / 2;
    update(lc(idx), l, m, pos, delta, tp);
    update(rc(idx), m + 1, r, pos, delta, tp);
    push_up(idx);
  }
  SegNode query_top_k(int idx, int l, int r, int k) {
    // debug(l, r, k, v[idx].nx, v[idx].ny, v[idx].sum);
    if (k <= 0) return SegNode();
    if (v[idx].nx + v[idx].ny == k) return v[idx];
    if (l == r) {
      SegNode ret = v[idx];
      int left = ret.nx + ret.ny - k;
      //debug(left);
      ret.sum -= left * 1LL * vv[l - 1];
      if (left <= ret.ny) {
        ret.ny -= left;
      } else {
        ret.nx -= left - ret.ny;
        ret.ny = 0;
      }
      return ret;
    }
    int m = (l + r) / 2;
    if (v[rc(idx)].nx + v[rc(idx)].ny >= k) {
      return query_top_k(rc(idx), m + 1, r, k);
    }
    SegNode ret = v[rc(idx)];
    ret = ret.merge(query_top_k(lc(idx), l, m, k - v[rc(idx)].nx - v[rc(idx)].ny));
    return ret;
  }
  void push_down(int idx) {
  }
  void push_up(int idx) {
    v[idx] = v[lc(idx)].merge(v[rc(idx)]);
  }
};

void solve(int ncase) {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> tp[i] >> d[i];
    vv.push_back(abs(d[i]));
  }
  sort(vv.begin(), vv.end());
  vv.erase(unique(vv.begin(), vv.end()), vv.end());
  map<int, int> v2pos;
  for (int i = 0; i < vv.size(); i++) {
    v2pos[vv[i]] = i + 1;
  }

  int nt = vv.size();
  SegTree seg_tree(nt);
  multiset<int> fire;
  int nx = 0, ny = 0;
  ll sum = 0;
  for (int i = 0; i < n; i++) {
    sum += d[i];
    int delta = d[i] > 0 ? 1 : -1;
    if (tp[i] == 0) {
      nx += delta;
      if (delta == 1) fire.insert(d[i]);
      else fire.erase(-d[i]);
    } else {
      ny += delta;
    }
    seg_tree.update(1, 1, nt, v2pos[abs(d[i])], delta, tp[i]);
    if (ny == 0) {
      cout << sum << endl;
      continue;
    }
    SegNode node = seg_tree.query_top_k(1, 1, nt, ny);
    ll d = 0;
    //debug(node.ny, node.sum);
    if (node.ny == ny) {
      if (!fire.empty()) d += *fire.rbegin();
      if (ny - 1 > 0) {
        node = seg_tree.query_top_k(1, 1, nt, ny - 1);
        d += node.sum;
      }
    } else {
      d = node.sum;
    }
    cout << sum + d << endl;
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
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << std::fixed;
  cout << setprecision(6);
#ifdef _zzz_
  //ios_base::sync_with_stdio(true);
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //auto x = freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
  //cerr << x << " " << errno << endl;
  auto start_time = clock();
#endif
  solve_all_cases();
  //test();
#ifdef _zzz_
  //cout << (clock() - start_time) * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
#endif
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/
