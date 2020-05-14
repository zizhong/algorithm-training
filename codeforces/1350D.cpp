/**
* https://codeforces.com/contest/1350/problem/D
* description:
*    Given any array A, we can replace any segments with the median in the segments. The question can we convert all numbers in the whole array to a given number K.
* Analysis:
*   1. if K is not in the array A, return false.
*   2. Otherwise,
       #1. If two numbers adjacent are equal to K, return true.
       #2. If a number adjacent to K, larger than K, we can convert it to #1, return true.
       #3. The remaining cases are the number adjacent to K, are all smaller than K. If we can convert it to the #2, return true.
       #4. Converting #3 to #2 <==> there needs to at least two pair of numbers not least than K, the distance between them are less than 2.
     
*   in the contest, I missed the case that the number less than K can convert to number larger than K, which helps the goal.
* only focusing on converting number to K doesn't apply the full power of the given operation.
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

template<class TH>
void _dbg(const char *sdbg, TH h) { cerr << sdbg << '=' << h << endl; }
template<class TH, class... TA>
void _dbg(const char *sdbg, TH h, TA... a) {
  while (*sdbg != ',')cerr << *sdbg++;
  cerr << '=' << h << ',';
  _dbg(sdbg + 1, a...);
}

template<class T>
ostream &operator<<(ostream &os, vector<T> V) {
  os << "[";
  for (auto vv : V) os << vv << ",";
  return os << "]";
}
template<class L, class R>
ostream &operator<<(ostream &os, pair<L, R> P) {
  return os << "(" << P.st << "," << P.nd << ")";
}

#ifdef _zzz_
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif

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

const int N = 100000 + 10;
int n, k;
int a[N];
void solve(int ncase) {
  scanf("%d%d", &n, &k);
  vector<int> idx;
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    if (a[i] == k) a[i] = 0;
    else if (a[i] < k) a[i] = -1;
    else a[i] = 1;
    if (a[i] == 0) {
      idx.push_back(i);
    }
  }
  if (idx.empty()) {
    puts("no");
    return;
  }
  if (n == 1) {
    puts("yes");
    return;
  }
  for (int i = 0; i < n; i++) {
    int cnt = 0;
    for (int j = 0; j <= 2 && i + j < n; j++) {
      if (a[i + j] >= 0) cnt++;
    }
    if (cnt > 1) {
      puts("yes");
      return;
    }
  }
  puts("no");
  return;
}
void solve_all_cases() {
  int T = 1;
  scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  //pre_calc();
  while (T--) {
    solve(++ncase);
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  ios_base::sync_with_stdio(true);
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
  auto start_time = clock();
#endif
  solve_all_cases();
//  test();
#ifdef _zzz_
  cout << (clock() - start_time) * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
#endif
}
