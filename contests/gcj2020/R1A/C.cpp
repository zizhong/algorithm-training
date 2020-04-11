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

bool okay_to_e(const vector<vector<int>> &s,
               vector<vector<vector<int>>> &d,
               const vector<vector<int>> &to_e,
               int i,
               int j) {
  if (to_e[i][j]) return false;
  int sum = 0;
  int cnt = 0;
  if (d[i][j][0] != -1) {
    cnt++;
    sum += s[d[i][j][0]][j];
  }
  if (d[i][j][1] != -1) {
    cnt++;
    sum += s[d[i][j][1]][j];
  }
  if (d[i][j][2] != -1) {
    cnt++;
    sum += s[i][d[i][j][2]];
  }
  if (d[i][j][3] != -1) {
    cnt++;
    sum += s[i][d[i][j][3]];
  }
  if (cnt == 0) return false;
  return s[i][j] * cnt < sum;
}

void solve(int ncase) {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> s(n, vector<int>(m));
  vector<vector<int>> to_e(n, vector<int>(m));
  vector<vector<vector<int>>> d(n, vector<vector<int>>(m, vector<int>(4, -1)));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> s[i][j];
      // up, down, left, right
      d[i][j][0] = (i - 1 >= 0 ? i - 1 : -1);
      d[i][j][1] = (i + 1 < n ? i + 1 : -1);
      d[i][j][2] = (j - 1 >= 0 ? j - 1 : -1);
      d[i][j][3] = (j + 1 < m ? j + 1 : -1);
    }
  }
  vector<PII> e;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (okay_to_e(s, d, to_e, i, j)) {
        e.push_back(PII(i, j));
        to_e[i][j] = 1;
      }
    }
  }
  ll ans = 0;
  ll round = 1;
  while (!e.empty()) {
    ll tmp = 0;
    for (auto p : e) {
      tmp += round * s[p.first][p.second];
      s[p.first][p.second] = 0;
    }
    vector<PII> ne;
    for (auto p : e) {
      for (int k = 0; k < 4; k++) {
        int i = p.first;
        int j = p.second;
        int ni = i, nj = j;
        if (d[i][j][k] == -1) continue;
        if (k < 2) ni = d[i][j][k];
        else nj = d[i][j][k];
        if (s[ni][nj] == 0) continue;
        if (to_e[ni][nj]) continue;
        // update the d for ni, nj
        for (int h = 0; h < 4; h++) {
          while (d[ni][nj][h] != -1) {
            if (h < 2 && s[d[ni][nj][h]][nj] == 0) {
              d[ni][nj][h] = d[d[ni][nj][h]][nj][h];
            } else if (h >= 2 && s[ni][d[ni][nj][h]] == 0) {
              d[ni][nj][h] = d[ni][d[ni][nj][h]][h];
            } else {
              break;
            }
          }
          if (okay_to_e(s, d, to_e, ni, nj)) {
            ne.push_back(PII(ni, nj));
            to_e[ni][nj] = 1;
          }
        }
      }
    }
    e = ne;
    ans += tmp;
    round++;
  }
  ll last = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      last += s[i][j];
    }
  }
  cout << "Case #" << ncase << ": " << ans + round * last << endl;
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
