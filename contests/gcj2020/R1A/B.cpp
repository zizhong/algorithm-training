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
const int N = 512;
vector<vector<ll>> p;
void solve(int ncase) {
  p.assign(N, vector<ll>(N, 0));
  for (int i = 1; i <= 500; i++) {
    for (int j = 1; j < i; j++) {
      p[i][j] = p[i - 1][j - 1] + p[i][j];
    }
  }
  int n;
  cin >> n;
  int left_step = 40;
  cout << "Case #" << ncase << ":" << endl;
  if (n <= left_step) {
    for (int i = 1; i <= n; i++) {
      cout << i << " " << 1 << endl;
    }

    return;
  } else {
    n -= left_step;
    int r = 1, c = 1;
    int d = 1;
    for (int i = 1; n > 0; i++) {
      if (n & 1) {
        if (d > 0) {
          for (int j = 1; j <= r; j++) {
            cout << r << " " << j << endl;
          }
        } else {
          for (int j = r; j >= 1; j--) {
            cout << r << " " << j << endl;
          }
        }
        d = -d;
      } else {
        cout << r << " " << (d > 0 ? 1 : r) << endl;
        left_step--;
      }
      n >>= 1;
      r++;
    }
    for (int i = 0; i < left_step; i++) {
      cout << r + i << " " << (d > 0 ? 1 : r + i) << endl;
    }
  }

}

void solve_all_cases() {
  int T = 1;
  //scanf("%d", &T);
  cin >> T;
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
