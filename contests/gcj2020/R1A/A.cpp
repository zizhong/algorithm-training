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
const int mod = 1000000007;
//const int mod = 998244353;
const int inf = 0x3fffffff;
//const int N = 2 * 1e5 + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

vector<string> v;
int n;
void get_start(const string &str, string &s, string &t) {
  bool met_star = false;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == '*') met_star = true;
    if (met_star) t.push_back(str[i]);
    else s.push_back(str[i]);
  }
}

void get_end(const string &str, string &s, string &t) {
  bool met_star = false;
  for (int i = str.size() - 1; i >= 0; i--) {
    if (str[i] == '*') met_star = true;
    if (met_star) s.push_back(str[i]);
    else t.push_back(str[i]);
  }
}

string check(vector<string> &vs) {
  sort(vs.begin(), vs.end());
  string max_s;
  for (auto &s : vs) {
    if (s.size() > max_s.size()) max_s = s;
  }
  for (int i = 0; i < max_s.size(); i++) {
    for (int j = 0; j < vs.size(); j++) {
      if (i < vs[j].size() && vs[j][i] != max_s[i]) return "*";
    }
  }
  return max_s;
}

string check_start() {
  vector<string> start;
  for (int i = 0; i < v.size(); i++) {
    string s, t;
    get_start(v[i], s, t);
    start.push_back(s);
    v[i] = t;
  }
  return check(start);
}

string check_end() {
  vector<string> end;
  for (int i = 0; i < v.size(); i++) {
    string s, t;
    get_end(v[i], s, t);
    reverse(s.begin(), s.end());
    end.push_back(t);
    v[i] = s;
  }
  string z = check(end);
  reverse(z.begin(), z.end());
  return z;
}

string check_mid() {
  string ret;
  for (auto &s : v) {
    for (auto c : s) {
      if (c == '*') continue;
      ret.push_back(c);
    }
  }
  return ret;
}

void solve(int ncase) {
  cin >> n;
  v.assign(n, string());
  for (int i = 0; i < n; i++) {
    cin >> v[i];
  }
  string s = check_start();
  string t = s == "*" ? "*" : check_end();
  string ret = t == "*" ? "*" : s + check_mid() + t;
  cout << "Case #" << ncase << ": " << ret << endl;
}

void solve_all_cases() {
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
