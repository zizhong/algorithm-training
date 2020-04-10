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
 
const int N = 2048;
char g[N][N];
int n;
char m[N];
 
bool no_col() {
  string zero(n, '0');
  vector<int> row;
  for (int i = 0; i < n; i++) {
    string tmp(g[i], n);
    if (tmp == zero) {
 
    } else if (tmp == m) {
      row.push_back(i);
    } else {
      return false;
    }
  }
  printf("%d\n", row.size());
  for (int i = 0; i < row.size(); i++) {
    printf("row %d\n", row[i]);
  }
  return true;
}
void solve(int ncase) {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%s", g[i]);
  }
 
  bool need = false;
  for (int i = 0; i < n; i++) {
    char s[N];
    scanf("%s", s);
    for (int j = 0; j < n; j++) {
      g[i][j] = (g[i][j] == s[j] ? '0' : '1');
      if (g[i][j]) need = true;
    }
  }
  scanf("%s", m);
  if (!need) {
    printf("0\n");
    return;
  }
  bool m_one = false;
  for (int i = 0; i < n; i++) {
    if (m[i] == '1') m_one = true;
  }
  if (!m_one) {
    printf("-1\n");
    return;
  }
  vector<int> row;
  string zero(n, '0');
  unordered_map<string, vector<int>> two;
  // no col
  if (no_col()) {
    return;
  }
  for (int i = 0; i < n; i++) {
    string tmp(g[i], n);
    if (m[i] == '0') {
      if (tmp == zero) continue;
      if (tmp == m) {
        row.push_back(i);
        continue;
      }
      printf("-1\n");
      return;
    }
    two[tmp].push_back(i);
  }
  vector<pair<string, vector<int>>> v_s;
  for (auto p : two) {
    v_s.push_back(p);
  }
  vector<int> col;
  if (v_s.size() == 1) {
 
    for (int i = 0; i < n; i++) {
      if ((v_s[0].first)[i] == '1') {
        col.push_back(i);
      }
    }
  } else if (v_s.size() == 2) {
    string z(n, '0');
    for (int i = 0; i < n; i++) {
      if ((v_s[0].first)[i] == (v_s[1].first)[i]) {
        z[i] = '0';
      } else {
        z[i] = '1';
      }
    }
    if (z != m) {
      printf("-1\n");
      return;
    }
    for (int i = 0; i < n; i++) {
      if ((v_s[0].first)[i] == '1') {
        col.push_back(i);
      }
    }
    for (auto r : v_s[1].second) {
      row.push_back(r);
    }
  } else if (v_s.size() > 2) {
    printf("-1\n");
    return;
  }
  printf("%d\n", row.size() + col.size());
  for (auto r : row) {
    printf("row %d\n", r);
  }
  for (auto c : col) {
    printf("col %d\n", c);
  }
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
