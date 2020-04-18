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
//const int mod = 1000000007;
const int mod = 998244353;
const int inf = 0x3fffffff;
const int N = 2 * 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

char s[N];
int d[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void update(ll &ans, int min_x_0, int max_x_0, int min_y_0, int max_y_0,
            int min_x_1, int max_x_1, int min_y_1, int max_y_1, int x, int y) {
  min_x_0 = min(x, min_x_0);
  max_x_0 = max(x, max_x_0);
  min_y_0 = min(y, min_y_0);
  max_y_0 = max(y, max_y_0);
  ans = min(ans,
            (max(max_x_1, max_x_0) -
                min(min_x_0, min_x_1) + 1) * 1LL *
                (max(max_y_1, max_y_0) -
                    min(min_y_0, min_y_1) + 1)
  );
//  printf("(%d %d) [%d %d] * [%d %d] = %d\n",
//         x, y,
//         min(min_x_0, min_x_1),
//         max(max_x_1, max_x_0),
//         min(min_y_0, min_y_1),
//         max(max_y_1, max_y_0), (max(max_x_1, max_x_0) -
//          min(min_x_0, min_x_1) + 1) *
//          (max(max_y_1, max_y_0) -
//              min(min_y_0, min_y_1) + 1));
}

void solve(int ncase) {
  scanf("%s", s + 1);
  int n = strlen(s + 1);
  vector<int> x0(n + 1);
  vector<int> x1(n + 1);
  vector<int> y0(n + 1);
  vector<int> y1(n + 1);
  vector<int> xx(n + 1);
  vector<int> yy(n + 1);
  map<char, int> d2i;
  d2i['W'] = 0;
  d2i['S'] = 1;
  d2i['A'] = 2;
  d2i['D'] = 3;
  int x = 0;
  int y = 0;
  for (int i = 1; i <= n; i++) {
    int di = d2i[s[i]];
    x += d[di][0];
    y += d[di][1];
//    printf("(%d %d)\n", x, y);
    xx[i] = x;
    yy[i] = y;
    x0[i] = min(x0[i - 1], x);
    x1[i] = max(x1[i - 1], x);
    y0[i] = min(y0[i - 1], y);
    y1[i] = max(y1[i - 1], y);
  }
  ll ans = (x1[n] - x0[n] + 1) * 1LL * (y1[n] - y0[n] + 1);
  //printf("%d\n", ans);
  int max_x = x, min_x = x, max_y = y, min_y = y;
  for (int i = n - 1; i >= 1; i--) {
//    printf("=============== %d [%d, %d] [%d, %d] [%d %d] [%d, %d]\n", i,
//           min_x, max_x, min_y, max_y, x0[i], x1[i], y0[i], y1[i]);
    update(ans, min_x - 1, max_x - 1, min_y, max_y, x0[i], x1[i], y0[i], y1[i], xx[i] - 1, yy[i]);
    update(ans, min_x + 1, max_x + 1, min_y, max_y, x0[i], x1[i], y0[i], y1[i], xx[i] + 1, yy[i]);
    update(ans, min_x, max_x, min_y - 1, max_y - 1, x0[i], x1[i], y0[i], y1[i], xx[i], yy[i] - 1);
    update(ans, min_x, max_x, min_y + 1, max_y + 1, x0[i], x1[i], y0[i], y1[i], xx[i], yy[i] + 1);
    max_x = max(max_x, xx[i]);
    max_y = max(max_y, yy[i]);
    min_x = min(min_x, xx[i]);
    min_y = min(min_y, yy[i]);
  }
  printf("%lld\n", ans);
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
  freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
  auto start_time = clock();
#endif
  solve_all_cases();
  //test();
#ifdef _zzz_
  cout << (clock() - start_time) * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
#endif
}
