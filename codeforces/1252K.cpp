/*
  1. lazy tag means the children is too lazy to change. A children's state kept in the father node.
  2. Try to understand the a variable. Instead of blindly trying to debug, question yourself about what the code does in a high level. What's the intention about the variable and functions.
  3. Debug can help to avoid denial. Question can lead to insights. Insights can lead to success.
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

char str[N];
int n, q;
struct SegNode {
  int ch;
  int mat[2][2];
  void init(char c) {
    ch = 0;
    mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 1;
    if (c == 'A') {
      mat[0][1] = 0;
    } else {
      mat[1][0] = 0;
    }
  }
  void i() {
    mat[0][0] = mat[1][1] = 1;
    mat[0][1] = mat[1][0] = 0;
  }

  void change() {
    swap(mat[0][0], mat[1][1]);
    swap(mat[0][1], mat[1][0]);
  }

  void debug() {
    cout << mat[0][0] << " " << mat[0][1] << endl;
    cout << mat[1][0] << " " << mat[1][1] << endl;
  }
};

SegNode seg[N * 4];

void mul(int mat1[2][2], int mat2[2][2], int mat[2][2]) {
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      mat[i][j] = 0;
      for(int k = 0; k < 2; k ++) {
        mat[i][j] = (mat[i][j] + 0LL + mat1[i][k] * 1LL * mat2[k][j] % mod) % mod;
      }
    }
  }
}

void push_down(int l, int r, int rt) {
  if (seg[rt].ch == 0) return;
  if (l != r) {
    seg[rt * 2].ch ^= 1;
    seg[rt * 2 + 1].ch ^= 1;
    seg[rt * 2].change();
    seg[rt * 2 + 1].change();
  }
  seg[rt].ch = 0;
}

void push_up(int l, int r, int rt) {
  mul(seg[rt * 2].mat, seg[rt * 2 + 1].mat, seg[rt].mat);
}

void init(int l, int r, int rt) {
  if (l == r) {
    seg[rt].init(str[l]);
    return;
  }
  int m = (l + r) / 2;
  init(l, m, rt * 2);
  init(m + 1, r, rt * 2  + 1);
  push_up(l, r, rt);
}

void query(int l, int r, int rt, int L, int R, SegNode& z) {
  if (r < L || R < l) return;
  if (L <= l && r <= R) {
    int mat[2][2];
    mul(z.mat, seg[rt].mat, mat);
    memcpy(z.mat, mat, sizeof(mat));
    return;
  }
  push_down(l, r, rt);
  int m = (l + r) / 2;
  query(l, m, rt * 2, L, R, z);
  query(m + 1, r, rt * 2  + 1, L, R, z);
  push_up(l, r, rt);
}

void update(int l, int r, int rt, int L, int R) {
  if (r < L || R < l) return;
  if (l == r) {
    seg[rt].change();
    return;
  }
  if (L <= l && r <= R) {
    seg[rt].ch ^= 1;
    seg[rt].change();
    return;
  }

  push_down(l, r, rt);
  int m = (l + r) / 2;
  update(l, m, rt * 2, L, R);
  update(m + 1, r, rt * 2  + 1, L, R);
  push_up(l, r, rt);
}

PII calc(const SegNode& z, ll a, ll b) {
  return PII (
      (a * z.mat[0][0] % mod + b * z.mat[1][0] % mod) % mod,
      (a * z.mat[0][1] % mod + b * z.mat[1][1] % mod) % mod
      );
}

void solve(int ncase) {
  scanf("%d%d", &n, &q);
  scanf("%s", str+1);
  init(1, n, 1);
  while(q--) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int l, r;
      scanf("%d%d", &l, &r);
      update(1, n, 1, l, r);

    } else {
      int l, r, a, b;
      scanf("%d%d%d%d", &l, &r, &a, &b);
      SegNode z;
      z.i();
      query(1, n, 1, l, r, z);
      PII p = calc(z, a, b);
      printf("%d %d\n", p.first, p.second);
    }
  }
}
int main() {
  //ios::sync_with_stdio(false);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  freopen("C:\\Users\\grain\\Desktop\\out.txt", "w", stdout);
#endif
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
