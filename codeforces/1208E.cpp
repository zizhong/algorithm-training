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
//const int N = 2 * 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

int n, w;
const int N = 1000010;
int len[N];
vector<vector<int>> num;

ll seg[N * 4];

void update(int rt, int l, int r, int L, int R, int delta) {
  if (R < l || L > r) return;

  //if (rt == 1)printf("update %d (%d, %d), [%d, %d] %d\n", rt, l, r, L, R, delta);
  if (L <= l && r <= R) {
    seg[rt] += delta;
    return;
  }
  int m = (l + r) / 2;
  update(rt * 2, l, m, L, R, delta);
  update(rt * 2 + 1, m + 1, r, L, R, delta);
}

void query(int rt, int l, int r, int L, int R, ll &tmp) {
  if (R < l || L > r) return;
  //printf("query %d (%d, %d), [%d, %d] %lld\n", rt, l, r, L, R, seg[rt]);
  if (l == r) {
    tmp += seg[rt];
    return;
  }
  tmp += seg[rt];
  int m = (l + r) / 2;
  query(rt * 2, l, m, L, R, tmp);
  query(rt * 2 + 1, m + 1, r, L, R, tmp);
}

void solve(int ncase) {
  scanf("%d%d", &n, &w);
  num.assign(n, vector<int>());
  for (int i = 0; i < n; i++) {
    scanf("%d", &len[i]);
    num[i].assign(len[i] + 1, 0);
    for (int j = 1; j <= len[i]; j++) {
      scanf("%d", &num[i][j]);
    }
  }
  for (int r = 0; r < n; r++) {
    if (len[r] == w) {
      for (int i = 1; i <= len[r]; i++) {
        update(1, 1, w, i, i, num[r][i]);
      }
    } else {
      int empty_slots = w - len[r];
      vector<PIP> range(len[r]);
      for (int i = 1; i <= len[r]; i++) {
        range[i - 1] = PIP(num[r][i], PII(i, i + empty_slots));
      }
      range.push_back(PIP(0, PII(1, empty_slots)));
      range.push_back(PIP(0, PII(len[r] + 1, w)));
      sort(range.begin(), range.end(), greater<PIP>());
      set<PII> range_set;
      for (auto &p : range) {
        if (range_set.empty()) {
          update(1, 1, w, p.second.first, p.second.second, p.first);
          range_set.insert(p.second);
          continue;
        }
        auto it = range_set.lower_bound(p.second);
        bool has_before = false;
        bool has_after = false;
        PII range_before;
        PII range_after;
        if (it == range_set.end()) {
          has_before = true;
          it--;
          range_before = *it;
        } else if (it == range_set.begin()) {
          has_after = true;
          range_after = *it;
        } else {
          has_after = has_before = true;
          range_after = *it;
          it--;
          range_before = *it;
        }
        PII new_update_range = p.second;
        PII new_insert_range = p.second;
        // range_before, new_update_range
        if (has_before && range_before.second >= new_insert_range.first) {
          if (range_before.second >= new_insert_range.second) continue;
          new_insert_range = PII(range_before.first, max(range_before.second, new_insert_range.second));
          range_set.erase(range_before);
          new_update_range = PII(range_before.second + 1, new_update_range.second);
        }
        if (has_after && range_after.first <= new_insert_range.second) {
          if (range_after.first <= new_insert_range.first) continue;
          new_insert_range = PII(new_insert_range.first, max(range_after.second, new_insert_range.second));
          range_set.erase(range_after);
          new_update_range = PII(new_update_range.first, range_after.first - 1);
        }
        if (new_update_range.first <= new_update_range.second) {
          update(1, 1, w, new_update_range.first, new_update_range.second, p.first);
        }
        range_set.insert(new_insert_range);
      }
    }
  }

  for (int i = 1; i <= w; i++) {
    ll tmp = 0;
    query(1, 1, w, i, i, tmp);
    printf("%lld ", tmp);
  }
  puts("");
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
