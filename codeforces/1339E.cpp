/**
* Brute force, seeking rules.
* Fractal
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
const int mod = 998244353;

//const int N = 1e6 + 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
string convert(int x, int w) {
  string ret;
  while (x > 0) {
    ret.push_back(x % w + '0');
    x /= w;
  }
  reverse(ret.begin(), ret.end());
  return ret;
}
void simple_solve(int ncase) {
  int N = 256 * 4;
  vector<int> a;
  vector<int> z(N + 1);
  for (int i = 1;; i++) {
    while (i < N && z[i]) i++;
    z[i] = 1;
    if (i >= N) break;
    int j = i + 1;
    while (j < N) {
      if (z[j]) {
        j++;
        continue;
      }
      if (z[i ^ j]) {
        j++;
        continue;
      }
      break;
    }
    if (j >= N) break;
    if ((i ^ j) >= N) break;
    z[j] = 1;
    z[i ^ j] = 1;
    //printf("%s %s %s\n", convert(i, 4).c_str(), convert(j, 4).c_str(), convert((i ^ j), 4).c_str());
    printf("%d %d %d\n", i, j, (i ^ j));
    a.push_back(i);
    a.push_back(j);
    a.push_back(i ^ j);
  }

}
int col[3][4] = {
    {0, 1, 2, 3},
    {0, 2, 3, 1},
    {0, 3, 1, 2}
};
ll calc(ll idx, int c, ll total) {
  if (total == 4) {
    return col[c][idx];
  }
  return col[c][idx / (total / 4)] * (total / 4) + calc(idx % (total / 4), c, total / 4);
}
void solve(int ncase) {
  ll n;
  cin >> n;
  if (n < 4) {
    cout << n << endl;
    return;
  }
  n--;
  ll T = 1;
  ll v = 0;
  while (n >= T * 3) {
    n -= T * 3;
    T *= 4;
    v++;
  }
  int c = n % 3;
  cout << T * (c + 1) + calc((n - c) / 3, c, T) << endl;

}

void solve_all_cases() {

  //simple_solve(1);
  int T = 1;
  //scanf("%d", &T);
  cin >> T;
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
