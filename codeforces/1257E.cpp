/*
Given 3 arrays with 1..N randomly in them. Rearrange as less as possible to get elements in array [i] > elements in array[i-1].

Consider an assignment that first A numbers in array 0, first B number in array 1 and the remaining N - A - B in array 2.
FirstIn[i][j] means how many 1...j in array[i], the ans can be expressed as,

FirstIn[1][A] + FirstIn[2][A]
+ FirstIn[0][B] - FirstIn[0][A] + FirstIn[2][B] - FirstIn[2][A]
+ sz[0] - FirstIn[0][B] + sz[1] - FirstIn[1][B]

Enumberate B, The fixed part is  FirstIn[0][B] + FirstIn[2][B] + sz[0] - FirstIn[0][B] + sz[1] - FirstIn[1][B];
The part related to A is FirstIn[1][A] - FirstIn[0][A]. We can minimize the second part to get the optimal answer.

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
const int N = 1e6 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

void solve(int ncase) {
  vector<int> sz(3);
  scanf("%d%d%d", &sz[0], &sz[1], &sz[2]);
  int N = sz[0] + sz[1] + sz[2];
  vector<vector<int>> num(3, vector<int>());
  for(int i = 0; i < 3; i++) {
    num[i].assign(sz[i], 0);
    for(int j = 0; j < sz[i]; j++) {
      scanf("%d", &num[i][j]);
    }
    sort(num[i].begin(), num[i].end());
  }
  // firstIn[0][i] : how many numbers are in 1..i and in array 0.
  vector<vector<int>> firstIn(3, vector<int>(N + 1));
  vector<int> idx(3);
  int num_idx = 1;
  while(num_idx <= N) {
    int j = 0;
    while(j < 3 && (idx[j] >= sz[j] || num[j][idx[j]] != num_idx)) j++;
    firstIn[0][num_idx] = firstIn[0][num_idx - 1];
    firstIn[1][num_idx] = firstIn[1][num_idx - 1];
    firstIn[2][num_idx] = firstIn[2][num_idx - 1];
    firstIn[j][num_idx]++;
    idx[j]++;
    num_idx++;
  }
  int ans = N;
  int var_b = 0;
  for(int b = 0; b <= N; b++) {
    int fixed_b = firstIn[0][b] + firstIn[2][b] + sz[0] - firstIn[0][b] + sz[1] - firstIn[1][b];
    var_b = min(var_b, firstIn[1][b] - firstIn[0][b]);
    ans = min(fixed_b + var_b, ans);
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
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
