/**
* 1. operation A(S, a) -> a,S1,a,S2, .. Sn, a; operation B(S, a) -> SaS
* 2. A('', abc) -> A('a', 'bc') -> A('bab', 'c') -> 'cbcacbc'
     B('', cba) -> B('c', 'ba') -> B('cbc', 'a') -> 'cbcacbc'
     so, A('', S1) == B('', S1_reverse)
  3. Consider a DFA with the vertex being every prefixes, and edges pointing to the first following char Ci.
     Every sub sequence is a path from the start p.
     The number of sub sequence is the number of path from the start.
     Given the number of sub sequences To get the number of sub sequences for S + T, let A[i][j] be the path starting with i and ending with j. The path of M(S + T) = M(S) * M(T).
  4. A good reference of application of matrix. http://www.matrix67.com/blog/archives/276
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

struct Matrix {
  Matrix(int n = 27) {
    this->n = n;
    mat.assign(n, vector<ll>(n, 0));
    identity();
  }
  void clear() {
    mat.assign(n, vector<ll>(n, 0));
  }
  void identity() {
    for (int i = 0; i < n; i++) mat[i][i] = 1;
  }
  void signal_char(int c) {
    for (int i = 0; i < n; i++) mat[i][c] = 1;
  }
  Matrix operator+(const Matrix &rhs) const {
    Matrix ret;
    ret.clear();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        ret.mat[i][j] = (mat[i][j] + rhs.mat[i][j]) % mod;
      }
    }
    return ret;
  }
  Matrix operator*(const Matrix &rhs) const {
    Matrix ret;
    ret.clear();

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          ret.mat[i][j] = (mat[i][k] * rhs.mat[k][j] + ret.mat[i][j]) % mod;
        }
      }
    }
    return ret;
  }
  vector<vector<ll>> mat;
  int n;
};
int n;
char s[2048];
void solve(int ncase) {
  scanf("%d%s", &n, s);
  Matrix m;
  vector<Matrix> char_m(26);
  for (int i = 0; i < 26; i++) char_m[i].signal_char(i);
  for (int i = n - 1; i >= 0; i--) {
    m = m * char_m[s[i] - 'a'] * m;
  }
  ll ans = 0;
  for (int i = 0; i < 26; i++) {
    ans = (ans + m.mat[26][i]) % mod;
  }
  printf("%lld\n", ans);
}
void solve_all_cases() {
  int T = 1;
  //scanf("%d", &T);
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
  //freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
  auto start_time = clock();
#endif
  solve_all_cases();
//  test();
#ifdef _zzz_
  cout << (clock() - start_time) * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
#endif
}
