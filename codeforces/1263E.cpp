/*
  using stack to maintain the max depth of a brackets.
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
string str;
char op[N];

stack<int> left_open;
stack<int> right_close;
stack<int> max_left_open;
stack<int> max_right_close;
int left_negative;
int right_negative;
int idx = 1;
int stack_top(const stack<int>& st) {
  if (st.empty()) return 0;
  return st.top();
}
void output() {
  if (left_negative == 0 && right_negative == 0 && stack_top(left_open) == stack_top(right_close)) {
    printf("%d ", max(stack_top(max_left_open), stack_top(max_right_close)));
    return;
  }
  printf("-1 ");
}

void push_to_left(char c) {
  int t = stack_top(left_open);
  if (c == 'a') {
    left_open.push(t < 0 ? 0 : t);
    max_left_open.push(stack_top(max_left_open));
    return;
  }
  if (c == '(') {
    if (t < 0) t = 0;
    left_open.push(t + 1);
    max_left_open.push(max(stack_top(max_left_open), t + 1));
    return;
  }
  left_open.push(t - 1);
  max_left_open.push(stack_top(max_left_open));
  if (t - 1 < 0) left_negative++;
}
void pop_from_left(char c) {
  int t = stack_top(left_open);
  left_open.pop();
  max_left_open.pop();
  if (t < 0) left_negative--;
}
void push_to_right(char c) {
  int t = stack_top(right_close);
  if (c == 'a') {
    right_close.push(t < 0 ? 0 : t);
    max_right_close.push(stack_top(max_right_close));
    return;
  }
  if (c == ')') {
    if (t < 0) t = 0;
    right_close.push(t + 1);
    max_right_close.push(max(stack_top(max_right_close), t + 1));
    return;
  }
  right_close.push(t - 1);
  max_right_close.push(stack_top(max_right_close));
  if (t - 1 < 0) right_negative++;
}
void pop_from_right(char c) {
  int t = stack_top(right_close);
  right_close.pop();
  max_right_close.pop();
  if (t < 0) right_negative--;
}

void left_to_right() {
  pop_from_left(str[idx-1]);
  push_to_right(str[idx-1]);
}
void right_to_left() {
  pop_from_right(str[idx]);
  push_to_left(str[idx]);
}

void update(char n, char o) {
  if (n == o) return;
  pop_from_right(o);
  push_to_right(n);
}

void solve(int ncase) {
  int n;
  scanf("%d%s", &n, &op);
  str.assign(1 + n , 'a');
  for(int i = 0; i < n; i++) right_close.push(0), max_right_close.push(0);
  for(int i = 0; i < n; i++) {
    if (op[i] == 'L') {
      if (left_open.empty()) {
        output();
        continue;
      }
      left_to_right();
      idx--;
      output();
      continue;
    }
    if (op[i] == 'R') {
      right_to_left();
      idx++;
      output();
      continue;
    }
    if (op[i] >= 'a' && op[i] <= 'z') {
      op[i] = 'a';
    }
    update(op[i], str[idx]);
    str[idx] = op[i];
    output();
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
