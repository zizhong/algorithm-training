/*
  nCr math
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
//#include "utils/haha.h"
//#include "utils/max_flow.h"
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<string, int> PSI;
typedef pair<int, PII> PIP;
typedef long long ll;
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
const int N = 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

int c[20][20];

void precalc() {
  for(int i = 1; i < 20; i++) {
    c[i][0] = c[i][i] = 1;
    for(int j = 1; j < i; j++) {
      c[i][j] = c[i-1][j] + c[i-1][j-1];
    }
  }
}

ll calc(const vector<int>& a) {
  ll ans = 1;
  for(int i = a.size() - 1; i >= 0; i--) {
    int j = i;
    while(j >= 0 && a[j] == a[i]) j--;
    int k = i - j;
    int slot = min(a.size() - a[i] + 1, a.size()) - (a.size() - i - 1);
    ans *= c[slot][k];
    i = j + 1;
  }
  return ans;
}
void solve(int ncase) {
  ll n;
  scanf("%I64d", &n);
  vector<int> a;
  for(int i = 2; n > 0; i++) {
    a.push_back(n % i);
    n /= i;
  }
  sort(a.begin(), a.end());

  ll ans = calc(a);
  if (a[0] == 0) {
    reverse(a.begin(), a.end());
    a.pop_back();
    reverse(a.begin(), a.end());
    ans -= calc(a);
  }
  printf("%I64d\n", ans-1);


}

int main() {
  //ios::sync_with_stdio(false);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //freopen("out.txt", "w", stdout);
#endif
  precalc();
  int T = 1;
  scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
