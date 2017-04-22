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
#include <cassert>
#endif
#include <ctime>
#include <queue>
#include <stack>
#include<iomanip>
#include <sstream>
#include <cmath>
//#include "utils/haha.h"
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;
#define CLS(x, v) (memset((x), (v), sizeof((x))))

const int N = 128;
int n,k;
int total[N], speed[N];
int d[N][N];
int s[N], e[N];

vector<vector<double>> g; 
vector<double> dp;

void dij(int x) {
    vector<ll> dis(n, -1);
    vector<int> used(n, 0);
    dis[x] = 0;
    used[x] = 0;
    while(true) {
        int min_i = -1;
        for(int i = 0; i < n; i++) {
            if (used[i] == 0 && dis[i] != -1 &&
                (min_i == -1 || dis[min_i] > dis[i])) {
                min_i = i;
            }
        }
        if (min_i == -1 || dis[min_i] == -1 || dis[min_i] > total[x]) break;
        used[min_i] = 1;
        for(int i = 0; i < n; i++) {
            if (used[i]) continue;
            if (d[min_i][i] == -1) continue;
            ll y = dis[min_i] + d[min_i][i];
            if (dis[i] == -1 || dis[i] > y) dis[i] = y;
        }
    }
    for(int i = 0; i < n; i++) {
        if (dis[i] == -1 || dis[i] > total[x]) continue;
        g[x][i] = dis[i] * 1.0 / speed[x];
        //printf("ride horse[%d], to stop[%d], cost [%lf]\n", x, i, g[x][i]);
    }

}

void deliver(int x, double t) {
    //cout << "deliver : " << x << " " << t << endl;
    if (dp[x] == -1 || dp[x] > t) {
        dp[x] = t;
        for(int i = 0; i < n; i++) {
            if (g[x][i] >= 0 && i != x) {
                deliver(i, t + g[x][i]);
            }
        }
    }
}
void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> total[i] >> speed[i];
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> d[i][j];
        }
    }
    g.assign(n, vector<double>(n, -1));
    for(int i = 0; i < n; i++) {
        g[i][i] = 0;
        dij(i);
    }
    for(int i = 0; i < k; i++) {
        cin >> s[i] >> e[i];
        s[i]--;e[i]--;
        dp.assign(n, -1);
        deliver(s[i], 0);
        cout << dp[e[i]] << (i == k - 1 ? '\n' : ' ');
    }

}


int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    cout << setprecision(16);
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    //precalc();
    int T = 1;
    scanf("%d", &T);
    //cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
