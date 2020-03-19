/**
   The problem is that
   Given N voters, with a price pi and an integer mi (if >= mi voted, the voter will also vote.), calculate the minumum price needed to have all the voters vote.
   For a certain mi0, if sum of the mi < mi0 groups is not enough, we need to pay for the cheapest x people with mi >= mi0.
   
   The tricky/brilliant part is to iterate mi from the largest to the smallest, so the choice later doesn't make the choice now invalid.
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
const int mod = 1000000007;
const int inf = 0x3fffffff;
const int N = 1e5  + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

void solve(int ncase) {
  int n;
  scanf("%d", &n);
  vector<PII> a(n);
  for(int i = 0; i < n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
  }
  sort(a.begin(), a.end());
  int cnt = 0;
  min_heap<int> z;
  ll ans = 0;
  for(int i = n - 1; i >= 0; i--) {
    int j = i;
    while(j >= 0 && a[j].first == a[i].first) {
      z.push(a[j].second);
      j--;
    }
    if (j + 1 + cnt < a[i].first) {
      int k = a[i].first - (j + 1 + cnt);
      cnt += k;
      while(k --) {
        ans += z.top();
        z.pop();
      }
    }
    i = j + 1;
  }
  cout << ans << endl;
}
int main() {
  //ios::sync_with_stdio(false);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
#endif
  int T = 1;
  scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
