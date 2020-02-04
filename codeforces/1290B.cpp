/**
Problem link: https://codeforces.com/contest/1290/problem/B

First and the more important part of the problem is to see if a string has at least one irreducible anagram.

Approving this question step by step,

If string length == 1, itself is an ireducible anagram.
If unique character count == 1 && string length > 1, there will be all reducible anagrams.
If unique character count == 2,
  aab has baa as an ireducible anagram.
  aba doesn't have any ireducible anagram.
If s has doesn't have any ireducible anagram, all of its anagrams are reducible, which means from the start to some point,
the matched substrings are anagrams.
Let's model this by some mathematics language.
Consider a string of unique character count == 2 as a point in a 2-D plane. (x,y)
The string represent a path from (0, 0) to (x, y).
If two paths have intersections, two anagrams are reducible.
So, the problem is now, given a path from (0, 0) to (x, y), check if there is another path doesn't intersect the given path.
Or, if we remove the orginal path, check if it's accessiable from (0, 0) to (x, y).
From (0, 0), there are only (0, 1) and (1, 0) to go. If the original path goes (0, 1), the new path needs to go (1, 0).
The similar rule applies for the (x, y).
If it's not accessiable, there needs to be a "wall" in the middle of the path. If the wall is vertical,
the first and last step are horizontal. vice versa.
That means if it's not accessible, the first and last step need to be same. so, the string needs to have the first charactor ==
last charactor.
If the begin and end are not the same, we can easily draw a path not intersacting with the original.

If unique character count > 2, the question is to check if a path can block another path in a multiple demonsion case, which
we can easily tell it's not possible. We need a wall but the given path is a string.

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
const int mod = 1000000007;
const int inf = 0x3fffffff;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

const int N = 2 * 100010;
char s[N];
int pre[N][26];
void solve(int ncase) {
  scanf("%s", s);
  int n = strlen(s);
  for(int i = 0; i < n; i++) {
    pre[i][s[i] - 'a'] = 1;
    if (i > 0) {
      for(int j = 0; j < 26; j++) {
        pre[i][j] += pre[i - 1][j];
      }
    }
  }
  int q;
  scanf("%d", &q);
  while(q--) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--;
    y--;
    if (x == y) {
      printf("Yes\n");
      continue;
    }
    int diff[26] = {0};
    int cnt_c = 0;
    for(int i = 0; i < 26; i++) {
      diff[i] = pre[y][i] - (x - 1 >= 0 ? pre[x - 1][i] : 0);
      cnt_c += (diff[i] > 0);
    }
    if (cnt_c == 1) {
      printf("No\n");
      continue;
    }
    if (cnt_c == 2 && s[x] == s[y]) {
      printf("No\n");
      continue;
    }
    printf("Yes\n");
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
  //precalc();
  int T = 1;
  //scanf("%d", &T);
  // cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
