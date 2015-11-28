/*
desc:
    large matrices A * B = C?
solu:
    randomize / compress
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
#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#endif
#include <ctime>
#include <queue>
#include <stack>
#include<iomanip>
#include <sstream>
#include <cmath>
#include <list>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> PII;
typedef pair<int, double> PID;
typedef pair<string, int> PSI;
typedef pair<string, string> PSS;
typedef pair<PII, int> PIP;

void precalc() {}

const int N = 512;
int a[N][N], b[N][N], c[N][N];
int n;
void compress(int *x, int a[][N], int* y) {
    for(int j = 0; j < n; j ++) {
        for(int k = 0; k < n; k ++) {
            y[k] += x[j] * a[j][k];
        }
    }
}
bool check() {
    int x[N], y[N], z[N], w[N];
    for(int i = 0; i < n; i ++) {
        x[i] = 1;
        y[i] = 0;
        w[i] = 0;
    }
    compress(x, a, y);
    compress(y, b, z);
    compress(x, c, w);
    for(int i = 0; i < n; i ++) {
        if (z[i] != w[i]) return false;
    }
    return true;
}
void solve(int ncase) {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < n; j ++) {
            scanf("%d", &a[i][j]);
        }
    }
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < n; j ++) {
            scanf("%d", &b[i][j]);
        }
    }
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < n; j ++) {
            scanf("%d", &c[i][j]);
        }
    }
    int nr = 100 * 20;
    srand(time(NULL));
    bool flag = true;
    while(nr --) {
        int x = rand() % n;
        int y = rand() % n;
        int tmp = 0;
        for(int i = 0; i < n; i ++) {
            tmp += a[x][i] * b[i][y];    
        }
        if (tmp != c[x][y]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        flag = check();
    }
    puts(flag ? "YES" : "NO");
}
int main() {
    //ios::sync_with_stdio(false);
    //cout << std::fixed << setprecision(16);
    //init();
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
    //freopen("A-small-practice.in", "r", stdin);
    //freopen("A-large-practice.in", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    int T = 1;
    precalc();
    //cin >> T;
    //scanf("%d", &T);
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
