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
const int N = 2 * 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
 
struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
 
void solve(int ncase) {
  int n;
  string s1, s2;
  cin >> n >> s1 >> s2;
  puts("YES");
  if (s1[0] == s1[1] && s2[0] == s2[1]) {
    string s = "abc";
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 3; j++) putchar(s[j]);
    }
    puts("");
    return;
  }
  if (s1[0] == s1[1] || s2[0] == s2[1]) {
    if (s2[0] == s2[1]) swap(s1, s2);
    swap(s2[0], s2[1]);
    if (s1[0] == s2[0]) {
      // aa, ab
      int x = ((int) 'a' + 0 + 'b' + 'c' - s1[0] - s2[1]);
      for (int i = 0; i < n; i++) {
        putchar(s1[0]);
        putchar(x);
      }
      for (int i = 0; i < n; i++) {
        putchar(s2[1]);
      }
      puts("");
      return;
    } else if (s1[0] == s2[1]) {
      // aa, ba
      for (int i = 0; i < n; i++) {
        putchar(s2[0]);
      }
      int x = ((int) 'a' + 0 + 'b' + 'c' - s1[0] - s2[0]);
      for (int i = 0; i < n; i++) {
        putchar(s1[0]);
        putchar(x);
      }
      puts("");
    } else {
      // aa, bc
      for (int i = 0; i < n; i++) {
        putchar(s1[0]);
        putchar(s2[0]);
      }
      for (int i = 0; i < n; i++) {
        putchar(s2[1]);
      }
      puts("");
    }
    return;
  }
  if ((s1[0] == s2[0] && s1[1] == s2[1]) ||
      (s1[0] == s2[1] && s1[1] == s2[0])) {
    int x = ((int) 'a' + 0 + 'b' + 'c' - s1[0] - s1[1]);
    for (int i = 0; i < n; i++) {
      putchar(s1[0]);
    }
    for (int i = 0; i < n; i++) {
      putchar(x);
    }
    for (int i = 0; i < n; i++) {
      putchar(s1[1]);
    }
    puts("");
    return;
  }
  swap(s1[0], s1[1]);
  swap(s2[0], s2[1]);
  if (s1[0] == s2[0]) {
    for (int i = 0; i < n; i++) {
      putchar(s1[0]);
    }
    for (int i = 0; i < n; i++) {
      putchar(s1[1]);
    }
    for (int i = 0; i < n; i++) {
      putchar(s2[1]);
    }
    puts("");
    return;
  }
  if (s1[0] == s2[1]) {
    for (int i = 0; i < n; i++) {
      putchar(s2[0]);
    }
    for (int i = 0; i < n; i++) {
      putchar(s1[0]);
    }
    for (int i = 0; i < n; i++) {
      putchar(s1[1]);
    }
    puts("");
    return;
  }
  if (s1[1] == s2[0]) {
    for (int i = 0; i < n; i++) {
      putchar(s1[0]);
    }
    for (int i = 0; i < n; i++) {
      putchar(s1[1]);
    }
    for (int i = 0; i < n; i++) {
      putchar(s2[1]);
    }
    puts("");
    return;
  }
  for (int i = 0; i < n; i++) {
    putchar(s1[0]);
  }
  for (int i = 0; i < n; i++) {
    putchar(s2[0]);
  }
  for (int i = 0; i < n; i++) {
    putchar(s2[1]);
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
