/*
Binary search.
Enumberate the lower_bound and upper bound, which is inside the original array.
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


int n;
ll k;
bool ok(const vector<ll>&a, const vector<ll>& sum, int diff) {
  int max_i = 0;
  int min_i = 0;
  for(min_i = 0; min_i < n; min_i++) {
    while(max_i < n && a[max_i] <= a[min_i] + diff) {
      max_i++;
    }
    ll cost = 0;
    if (min_i - 1 >= 0) {
      cost += min_i * 1LL * a[min_i] - sum[min_i - 1];
    }
    if (max_i < n) {
      cost += -(a[min_i] + diff) * 1LL * (n - max_i) + (sum[n - 1] - (max_i - 1 >= 0 ? sum[max_i - 1] : 0));
    }
    if (cost <= k) return true;
  }
  max_i = n - 1;
  min_i = n - 1;
  for(max_i = n - 1; max_i >= 0; max_i --) {
    while(min_i >= 0 && a[min_i] >= a[max_i] - diff) min_i--;
    ll cost = 0;
    if (min_i >= 0) {
      cost += (min_i + 1) * 1LL * (a[max_i] - diff) - sum[min_i];
    }
    if (max_i < n - 1) {
      cost += -(a[max_i]) * 1LL * (n - max_i - 1) + (sum[n - 1] - sum[max_i]);
    }
    if (cost <= k) return true;
  }
  return false;
}

void solve(int ncase) {
  cin >> n >> k;
  vector<ll> a(n);
  vector<ll> sum(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a.begin(), a.end());
  for(int i = 0; i < n; i++) {
    if (i == 0) sum[i] = a[i];
    else sum[i] = a[i] + sum[i-1];
  }
  int l = 0, r = 1e9 + 1;
  int ans = -1;
  if (ok(a, sum, l)) {
    ans = l;
  } else {
    while(l + 1 < r) {
      int mid = (l + r + 0LL) / 2;
      //cout << l << " " << r << endl;
      if (ok(a, sum, mid)) r = mid;
      else l = mid;
    }
    ans = r;
  }
  cout << ans << endl;
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
