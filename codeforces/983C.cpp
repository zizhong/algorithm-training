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
const string imp = "IMPOSSIBLE";
const ll long_inf = 1LL<<60;
ll gcd(ll a, ll b) {return b ? gcd(b, a % b) : a; }

int sgn(int x) {return x == 0 ? 0 : (x > 0 ? 1 : -1);}

const int N = 715;
int f[2][9][N];

void update(int& a, int b) {
    if (a == -1 || a > b) a = b;
}

void solve(int ncase) {
    //cout << "Case #" << ncase << ": ";
    int n;
    scanf("%d", &n);
    memset(f, -1, sizeof(f));
    f[0][0][0] = 0;
    vector<PII> p(n + 1);
    for(int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        p[i] = PII(x, y);
    }
    vector<int> status;
    vector<int> s2idx(10000);
    for(int a = 0; a < 10; a++) {
        for(int b = a; b < 10; b++) {
            for(int c = b; c < 10; c++) {
                for(int d = c; d < 10; d++) {
                    status.push_back(a *1000 + b * 100 + c * 10 + d);
                    s2idx[status.back()] = status.size()-1;
                }
            }
        }
    }
    //cout << status.size() << endl;
    for(int i = 1; i <= n+1; i++) {
        int cur = (i&1);
        memset(f[cur], -1, sizeof(f[cur]));
        // unloading
        for(int k = N-1; k >= 0; k --) {
            int kk = status[k];
            int d[4] = {kk % 10, kk / 10 % 10, kk / 100 % 10, kk / 1000};
            for(int fl = 0; fl < 9; fl++) {
                if (f[1 - cur][fl][k] == -1) continue;
                //printf("f[%d][%d][%d] = %d\n", i-1, fl + 1, kk, f[1 - cur][fl][k]);
                for(int j = 0; j < 4; j++) {
                    if (d[j] == 0 || (j > 0 && d[j-1] == d[j])) continue;
                    // To d[j]
                    int nd[4];
                    for(int z = 0; z < 4; z++) {
                        nd[z] = d[z];
                        if (z == j) nd[z] = 0;
                    }
                    sort(nd, nd + 4);
                    int nk = nd[0] * 1000 + nd[1] * 100 + nd[2] * 10 + nd[3];
                    int diff = abs(fl + 1 - d[j]);
                    update(f[1 - cur][d[j]-1][s2idx[nk]], f[1 - cur][fl][k]  + diff + 1);
                }
            }
            if (i == n+1) continue;
            // loading

            for(int fl = 0; fl < 9; fl++) {
                if (d[3] != 0 || f[1 - cur][fl][k] == -1) continue;
                int nd[4] = {d[0], d[1], d[2], p[i].second};
                sort(nd, nd + 4);
                int nk = nd[0] * 1000 + nd[1] * 100 + nd[2] * 10 + nd[3];
                //printf("%d:  %d -> %d\n", i, kk, nk);
                int diff = abs(fl + 1 - p[i].first);
                update(f[cur][p[i].first - 1][s2idx[nk]], f[1 - cur][fl][k] + diff + 1);
            }
        }
    }
    int ans = inf;
    for(int i = 0; i < 9; i++) {
        if (f[n&1][i][0] == -1 || f[n&1][i][0]  > ans) continue;
        ans = f[n&1][i][0];
    }
    cout << ans << endl;
}


int main() {
    ios::sync_with_stdio(false);
    //cout << std::fixed;
    //cout << setprecision(16);
#ifdef _zzz_
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    //precalc();
    int T = 1;
    //scanf("%d", &T);
    //cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
        //test();
    }
}
