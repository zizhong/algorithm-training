#include <vector>
#include<cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <deque>
#include <set>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <unordered_map>
#include <cassert>
#endif
#include <ctime>
#include <queue>
#include <stack>
#include<iomanip>
#include <sstream>
#include <cmath>
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;

const int inf = 0x3f3f3f3f;

const int N = 128;
ll g[N][N];

int n, m, K;

const int M = 5010;
ll f[M][2];
int start[M], endp[M];
void solve(int ncase) {
    scanf("%d%d%d", &n, &m, &K);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
           if(i != j) g[i][j] = inf;
        }
    }
    for(int i = 0; i < m; i++) {
        int x, y, gas;
        scanf("%d%d%d", &x, &y, &gas);
        g[x][y] = g[y][x] = min(g[x][y], 1LL *gas);
    }
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
    for(int i = 1; i <= K; i++) {
        scanf("%d%d", &start[i], &endp[i]);
    }
    for(int i = 1; i <= K; i++) f[i][0] = f[i][1] = inf;
    // f[i][0] -> (si, i, 1)
    // f[i][1] -> (ei-1, i, 1)
    // empty -> (ei, i+1, 0)
    // full -> (si+1, i, 2)
    f[1][0] = g[1][start[1]];
    bool flag = true;
    int result = inf;
    for(int i = 1; i <= K; i++) {
        if (f[i][0] >= inf && f[i][1] >= inf) {
            flag = false;
            break;
        }
        ll full = inf, empty = inf;
        if (f[i][0] < inf) {
            // si -> si+1
            full = g[start[i]][start[i+1]] + f[i][0];
            // si -> ei
            empty = g[start[i]][endp[i]] + f[i][0];
        }
        if (f[i][1] < inf) {
            full = min(full, f[i][1] + g[endp[i-1]][start[i+1]]);
            empty = min(empty, g[endp[i-1]][endp[i]] + f[i][1]);
        }
        if (i == K) {
            result = empty;
        }
        f[i+1][1] = min(f[i+1][1], full + g[start[i+1]][endp[i]]);
        f[i+1][0] = min(f[i+1][0], empty + g[endp[i]][start[i+1]]);
    }
    if (flag == false || result == inf) result = -1;
    cout << "Case #" << ncase << ": " << result << endl;
}


int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    //cout << setprecision(16) << endl;
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    int T = 1;
    scanf("%d", &T);
    //cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
