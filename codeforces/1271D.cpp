/*
https://codeforces.com/contest/1271/problem/D

Description

Initially, you have K warriors and you need to conquer N castles one by one. For castle i (1<=i<=N) has three properties,
1. A[i]: the number of warriors need to attack A[i]
2. B[i]: after you conquer the castle, you can increase you warrior number by B[i]
3. C[i]: the value of castle.
To conquer a castle, you need leave one of your warriors there after you attacked it.
After conquer a castle, you can also send one warrior through a backward portal to a already attacked castle to conquer it.
The question is to maximize the value of all conquered castles.

Analysis

For each castle i, we can calculate the extra warrior we have before attacking it, as more[i]. 
The more array is a non descreaing array, since we have more and more extra warriors in the process.

Consider one warrior you got from castle i, if it's required to conquer castle i + k, we can not use it to conquer any castle [i,i+k), but can conquer castle[i+k, n].

Let's say, more[] = {0, 0, 1, 1, 3, 3, 3}. It means at the end we have 3 warriors W1, W2 and W3.
W2 and W3 can conquer the castle [4,n], and W1 can conquer [2, n].
So, the algorithm is that We can iterate more[] from back to the front, if the value is changed by $delta, we can choose the top $delta castles by value.


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

int n, m, k;
const int MAX_N = 5010;
int a[MAX_N], b[MAX_N], c[MAX_N];
vector<vector<int>> portal;

void solve(int ncase) {
  scanf("%d%d%d", &n, &m, &k);
  bool valid = true;
  portal.assign(n + 2, vector<int>());
  vector<int> more(n + 2);
  int pre = k;
  for(int i = 1; i<= n; i++) {
    scanf("%d%d%d", &a[i], &b[i], &c[i]);
    if (valid) {
      if (pre < a[i]) valid = false;
      more[i] = pre - a[i];
      pre = pre + b[i];
    }
  }
  more[n+1] = pre;
  for(int i = 0; i < m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    portal[x].push_back(y);
  }
  if (!valid) {
    cout << -1 << endl;
    return;
  }

  vector<int> occupy(n + 2);
  for(int i = n - 1; i >= 1; i--) {
    more[i] = min(more[i+1], more[i]);
  }
  set<PII> o;
  for(int i = n; i >= 0; i--) {
    if (!occupy[i]) o.insert(PII(c[i], i));
    for(auto left : portal[i]) {
      if (!occupy[left]) o.insert(PII(c[left], left));
    }
    if (more[i+1] - more[i] > 0) {
      int delta = more[i+1] - more[i];
      while(delta > 0 && o.size() > 0) {
        auto it = o.end();
        --it;
        occupy[it->second] = 1;
        o.erase(it);
        delta--;
      }
    }
  }
  ll ans = 0;
  for(int i = 1; i <= n; i++) {
    if (occupy[i]) ans += c[i];
  }
  cout << ans << endl;
}

int main() {
  //ios::sync_with_stdio(false);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //freopen("out.txt", "w", stdout);
#endif
  //precalc();
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
