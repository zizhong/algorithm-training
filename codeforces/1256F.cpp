/*
  Given two strings with length N, and applies revese opertions to one substring with the same length for each given string.
  To find out if after several operations, two given strings can be equal.
  
  A reverse can be replaced with several swap. A swap is a reverse of length 2.
  Intuitively, we can consider only swaps instead of random reverse.
  If the swap numbers in string s and t, don't have same parity, the answer is NO. However, if a letter has duplicated, the parity can be changed arbitrarily.

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
const int N = 2 * 1e5  + 10;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};
int q;
char s[N];
char t[N];
int swap_cnt(char str[], int len) {
  int ans = 0;
  for(int i = 0; i < len; i++) {
    int min_j = i;
    for(int j = i; j < len; j++) {
      if (str[j] < str[min_j]) min_j = j;
    }
    while(min_j != i) {
      swap(str[min_j], str[min_j - 1]);
      min_j--;
      ans++;
    }
  }
  return ans;
}
void solve(int ncase) {
  scanf("%d", &q);
  while(q--) {
    int n;
    scanf("%d", &n);
    scanf("%s%s", s, t);
    vector<int> s_cnt(26);
    vector<int> t_cnt(26);
    for(int i = 0; i < n; i++) {
      s_cnt[s[i] - 'a']++;
      t_cnt[t[i] - 'a']++;
    }
    bool flag = false;
    bool dup_flag = false;
    for(int i = 0; i < 26; i++) {
      if (s_cnt[i] != t_cnt[i]) {
        flag = true;
        break;
      }
      if (s_cnt[i] > 1) dup_flag = true;
    }
    if (flag) {
      puts("NO");
      continue;
    }
    if (dup_flag) {
      puts("YES");
      continue;
    }
    puts((swap_cnt(s, n) % 2 == swap_cnt(t, n) % 2) ? "YES" : "NO");
  }
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
