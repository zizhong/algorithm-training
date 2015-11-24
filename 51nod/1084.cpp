/*
desc:
    given d[N][N], firstly go through a path from upper-left to lower-right, 
    then go through a patch from lower-right to upper-left.
    paths need to be shortest.
    We get the scores that equals to sum of numbers in the cell of paths.
    calculate the max score we can get.
solu:
    dp. O(N^3)
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
const int N = 256;
int n, m;
int d[N][N];
int f[N + N][N][N];
void precalc() {
}
void solve(int ncase) {
    scanf("%d%d", &m, &n);
    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= m; j ++) {
            scanf("%d", &d[i][j]);
        }
    }
    f[1][1][1] = d[1][1];
    for(int k = 1; k <= n + m - 1; k ++) {
        for(int i1 = 0; i1 < n; i1 ++) {
            for(int i2 = 0; i2 <= i1; i2 ++) {
                if (!(1 <= k - i1 && k - i1 <= m
                    && 1 <= k - i2 && k - i2 <= m)) continue;
                int z[][2] = {{0,0}, {0,1}, {1,0}, {1,1}};
                for(int h = 0; h < 4; h ++) {
                    int nx1 = i1 + 1 + z[h][0];
                    int ny1 = k + 2 - nx1;
                    int nx2 = i2 + 1 + z[h][1];
                    int ny2 = k + 2 - nx2;
                    if (nx1 < nx2) {
                        swap(nx1, nx2);
                        swap(ny1, ny2);
                    }
                    if (1 <= nx1 && nx1 <= n &&
                        1 <= nx2 && nx2 <= n &&
                        1 <= ny1 && ny1 <= m &&
                        1 <= ny2 && ny2 <= m) {
                        if (nx1 == nx2) {
                            f[k + 1][nx1][nx2] = max(f[k + 1][nx1][nx2], f[k][i1 + 1][i2 + 1] + d[nx1][ny1]);
                        } else {
                            f[k + 1][nx1][nx2] = max(f[k + 1][nx1][nx2], f[k][i1 + 1][i2 + 1] + d[nx1][ny1] + d[nx2][ny2]);
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", f[n + m - 1][n][n]);
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
