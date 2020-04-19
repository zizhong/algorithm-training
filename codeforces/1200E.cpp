/// KMP

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
//const int mod = 998244353;
const int inf = 0x3fffffff;
const int N = 1e6 + 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

void calc_kmp_next(const char *s, int len, vector<int> &next) {
  next.assign(len, -1);
  int j = -1;
  for (int i = 1; i < len; i++) {
    while (j >= 0 && s[i] != s[j + 1]) j = next[j];
    if (s[i] == s[j + 1]) j++;
    next[i] = j;
  }
}

char s[N];

void solve(int ncase) {
  int n;
  scanf("%d", &n);
  getchar();
  gets(s);
  vector<char *> vs(n);
  vector<int> len(n);
  int idx = 0;
  vs[idx++] = s;
  for (int i = 0; s[i]; i++) {
    if (s[i] == ' ') {
      s[i] = 0;
      if (idx == n) continue;
      vs[idx++] = s + i + 1;
    } else {
      len[idx - 1]++;
    }
  }

  string ret;
  ret.reserve(N);
  for (int i = 0; i < len[0]; i++) ret.push_back(vs[0][i]);
  for (int i = 1; i < n; i++) {
    vector<int> kmp_next(len[i]);
    calc_kmp_next(vs[i], len[i], kmp_next);
    int start = 0;
    if (ret.size() > len[i]) start = ret.size() - len[i];
    int j = -1;
    for (int k = start; k < ret.size(); k++) {
      char c = ret[k];
      while (j >= 0 && vs[i][j + 1] != c) j = kmp_next[j];
      if (vs[i][j + 1] == c) j++;
    }
    for (int k = j + 1; k < len[i]; k++) ret.push_back(vs[i][k]);
  }
  printf("%s\n", ret.c_str());
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
