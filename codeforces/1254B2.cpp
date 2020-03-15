/*
Factorization.
Only a few of factors an integer can be factorized to.
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
const int inf = 0x3fffffff;
const int N = 1e6  + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

ll sum;
vector<int> num;
ll calc_p(int s, int e, vector<int>& left) {
  ll forward = 0;
  ll backward = 0;
  ll total = 0;
  for(int i = e; i >= s; i--) {
    backward = backward + total;
    total += left[i];
  }
  ll btotal = total;
  total = 0;
  ll ans = -1;
  for(int i = s; i <= e; i++) {
    if (ans < 0 || ans > forward + backward) {
      ans = forward + backward;
    }
    btotal -= left[i];
    backward -= btotal;
    total += left[i];
    forward = forward + total;
  }
  //cout << s << " " << e << " " << ans << endl;
  return ans;
}
ll aans = -1;
ll calc(ll p) {

  vector<int> left = num;
  for(auto &x : left) x = x % p;
  int s = -1;
  ll total = 0;
  ll ans = 0;
  for(int i = 0; i < left.size(); i++) {
    total += left[i];
    if (total > 0 && s < 0) s = i;
    if (total >= p) {
      left[i] = left[i] - (total - p);
      ans += calc_p(s, i, left);
      if (aans > 0 && ans > aans) return ans;
      left[i] = total - p;
      if (left[i] > 0) {
        total = left[i];
        s = i;
      } else {
        s = -1;
        total = 0;
      }
    }
  }
  //cout << "p = " << p << " " << ans << endl;
  return ans;
}
void solve(int ncase) {
  int n;
  scanf("%d", &n);
  num.assign(n, 0);
  ll sum = 0;
  for(int i = 0; i < n; i++) {
    scanf("%d", &num[i]);
    sum += num[i];
  }
  if (sum == 1) {
    cout << -1 << endl;
    return;
  }

  vector<int> is_prime(N, 1);
  is_prime[1] = 0;
  vector<int> pl;
  for(int i = 2; i < N; i++) {
    if (is_prime[i]) {
      for(int j = i + i; j < N; j += i) {
        is_prime[j] = false;
      }
      pl.push_back(i);
    }
  }
  vector<ll> sum_p;
  ll x = sum;
  for(auto p : pl) {
    if (x == 1) break;
    if (x % p == 0) {
      sum_p.push_back(p);
      while(x % p == 0) x /= p;
    }
  }
  if (x > 1) sum_p.push_back(x);
  for(auto p : sum_p) {
    ll tmp = calc(p);
    if (aans < 0 || aans > tmp) aans = tmp;
  }
  cout << aans << endl;
}
int main() {
  //ios::sync_with_stdio(false);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //freopen("out.txt", "w", stdout);
#endif
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
