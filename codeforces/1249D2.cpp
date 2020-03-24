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
  int n, k;
  scanf("%d%d", &n, &k);

  vector<vector<PII>> line(N);
  vector<int> drop(n + 1);
  for(int i = 0; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    line[x].emplace_back(y + 1, i + 1);
    line[y + 1].emplace_back(0, -(i + 1));
  }
  set<PII> right_end;
  for(int i = 1; i < N; i++) {
    for(auto& p : line[i]) {
      if (p.second < 0) {
        int idx = -p.second;
        if (drop[idx]) continue;
        right_end.erase(PII(i, idx));
      } else {
        int idx = p.second;
        right_end.insert(p);
      }
    }
    while(right_end.size() > k) {
      auto it = right_end.end();
      it--;
      drop[it->second] = 1;
      right_end.erase(it);
    }
  }
  int dropped = 0;
  for(int i = 1; i <= n; i++) {
    if (drop[i]) dropped++;
  }
  printf("%d\n", dropped);
  for(int i = 1; i <= n; i++) if (drop[i]) printf("%d ", i);
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
#endif
  solve_all_cases();
  //test();
}
