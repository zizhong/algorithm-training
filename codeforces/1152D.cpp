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
const ll mod = 1000000007;
const int inf = 0x3fffffff;

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator() (const pair<T1, T2>& p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

ll gcd(ll x, ll y) {return y > 0 ? gcd(y, x % y) : x;}

ll calc(int a, int b, int q) {
    ll x = a + q + 0LL;
    ll y = b + q + 0LL;
    return x * y / gcd(x, y);
}

const int N = 1024;

void addmod(int& x, const int a) {
    x += a;
    if (x >= mod) x -= mod;
}

void solve(int ncase) {
    int n;
    scanf("%d", &n);
    vector<vector<int>> f(N + N, vector<int>(N, 0));
    f[0][0] = 1;
    for(int i = 0; i <= 2 * n; i++) {
        for(int j = 0; j <= n; j++) {
            if (f[i][j] == 0) continue;
            int left = 2 * n - i;
            if (left - 1 >= j + 1) {
                addmod(f[i + 1][j + 1], f[i][j]);
            }
            if (j - 1 >= 0) {
                addmod(f[i + 1][j - 1], f[i][j]);
            }
        }
    }
	int ans[2] = {0};
    for(int i = 0; i < 2 * n; i++) {
        for(int j = 0; j <= n; j++) {
            if (f[i][j] == 0) continue;
            addmod(ans[i&1], f[i][j]);
        }
    }
    cout <<  ans[1] << endl;
}

int main() {
    //ios::sync_with_stdio(false);
    //cout << std::fixed;
    //cout << setprecision(9);
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    //precalc();
    int T = 1;
    //scanf("%d", &T);
    //cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
    return 0;
}
