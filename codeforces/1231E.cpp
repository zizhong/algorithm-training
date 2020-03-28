/**
*  Enumberate
*  bruteforce
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
#include<iomanip>
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
const int inf = 0x3fffffff;
const int N = 2 * 1e5  + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

void solve(int ncase) {
  int n;
  const int N = 128;
  char s[N];
  char t[N];
  scanf("%d%s%s", &n, s, t);
  vector<int> cnt1(26), cnt2(26);
  for(int i = 0; i < n; i++) cnt1[s[i]-'a']++, cnt2[t[i]-'a']++;
  for(int i = 0; i < 26; i++) {
    if (cnt1[i] != cnt2[i]) {
      printf("-1\n");
      return;
    }
  }
  int ans = n;
  for(int ss = 0; ss < n; ss++) {
    if (ss >= ans) break;
    int h = ss;
    for(int i = 0; i < n; i++) {
      if (h < n && s[i] == t[h]) h++;
    }
    ans = min(ans, n - (h - ss));
  }
  printf("%d\n", ans);
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
#endif
  solve_all_cases();
  //test();
}
