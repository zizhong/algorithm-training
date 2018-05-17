#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <deque>
#include <set>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <unordered_map>
#include <cassert>
#endif
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
const int mod = 1000000007;
const int inf = 0x3fffffff;

bool cmp(const PII& p1, const PII& p2) {
  return p1.first - p1.second > p2.first - p2.second;
}

void solve(int ncase) {
  int n, a, b;
  scanf("%d%d%d", &n, &a, &b);
  vector<PII> vp(n);
  ll sum1 = 0;
  for(int i = 0; i < n; i++) {
    scanf("%d%d", &vp[i].first, &vp[i].second);
    sum1 += vp[i].second;
  }
  if (b == 0) {
    cout << sum1 << endl;
    return;
  }
  sort(vp.begin(), vp.end(), cmp);
  vector<ll> sum(n);
  for(int i = 0; i < n; i++) {
    sum[i] = max(0, vp[i].first - vp[i].second);
    if (i) sum[i] += sum[i-1];
  }

  b = min(b, n);
  if (a == 0) {
    cout << sum1 + sum[b-1] << endl;
    return;
  }
  ll ans = sum[b-1] + sum1;
  for(int i = 0; i < n; i++) {
    // if apply all a to vp[i]
    ll d = vp[i].first * 1LL * (1<<a) - vp[i].second;
    if (d < 0) continue;
    if (i < b) {
      d += sum1 + sum[b-1] - max(0, vp[i].first - vp[i].second);
    } else {
      d += sum1 + (b - 2 >= 0 ? sum[b-2] : 0);
    }
    ans = max(d, ans);
  }
  cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    //cout << std::fixed;
    //cout << setprecision(9);
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    //precalc();
    int T = 1;
    //scanf("%d", &T);
    //cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
