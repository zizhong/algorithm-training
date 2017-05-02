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
//#include "utils/max_flow.h"
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;
typedef pair<double, double> PDD;
typedef pair<ll, PII> PLP;
#define CLS(x, v) (memset((x), (v), sizeof((x))))
const double pi = acos(-1);

int ac, aj;


int dp[210][800];

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    cin >> ac >> aj;
    if (ac + aj == 0) {
        cout << 0 << endl;
        return;
    }
    vector<PIP> range;
    int left = 1440;
    int leftA = 720;
    for(int i = 0; i < ac; i++) {
        int x, y;
        cin >> x >> y;
        left -= y - x;
        leftA -= y - x;
        range.push_back(PIP(x, PII(y, 0)));
    }

    for(int i = 0; i < aj; i++) {
        int x, y;
        cin >> x >> y;
        left -= y - x;
        range.push_back(PIP(x, PII(y, 1)));
    }
    sort(range.begin(), range.end());
    int offset = range[0].first;
    for(auto &p : range) {
        p.first -= offset;
        p.second.first -= offset;
    }
    for(int i = 0; i <= range.size(); i++) {
        for(int j = 0; j <= 720; j++) {
            dp[i][j] = 1441;
        }
    }
    dp[0][leftA] = 0;
    for(int i = 0; i <= range.size(); i++) {
        int len = range[(i+1) % range.size()].first - range[i].second.first;
        if (len < 0) len += 1440;
        for(int la = 0; la <= leftA; la++) {
            if (dp[i][la] <= 1440) {
                int lb = left - la;
                //printf("dp[%d][%d][%d] = %d\n", i, la, lb, dp[i][la]);
                if (i == range.size()) continue;
                for(int t = 0; t <= len && t <= la; t++) {
                    int z[2] = {t, len - t};
                    if (z[1] > lb) continue;
                    int &u = dp[i+1][la - z[0]];
                    if (range[(i+1)%range.size()].second.second != range[i].second.second) {
                        u = min(u, dp[i][la] + 1);
                        continue;
                    }
                    if (z[1-range[i].second.second]) {
                        u = min(u, dp[i][la] + 2);
                    } else {
                        u = min(u, dp[i][la]);
                    }
                }
            }
        }
        left -= len;
    }
    cout << dp[range.size()][0] << endl;
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
