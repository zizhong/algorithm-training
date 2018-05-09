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

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    int n;
    cin >> n;
    vector<int> weight(n);
    for(int i = 0; i < n; i++) {
        cin >> weight[i];
    }

    const int length = 150;
    vector<ll> dp(length, long_inf);
    dp[0] = 0;
    for(int i = 0; i < n; i++) {
        for(int j = length - 1; j >= 0; j--) {
            if (dp[j] == long_inf) continue;

            if (dp[j] <= weight[i] * 1LL * 6) {
                dp[j + 1] = min(dp[j + 1], dp[j] + weight[i]);
            }
            //printf("i = %d, j = %d, dp[%d] = %I64d, weight[%d] = %d, dp[%d] = %I64d\n", i, j, j, dp[j], i, weight[i], j+1, dp[j+1]);
        }
    }
    int ans = 0;
    for(int i = length-1; i >= 0; i--) {
        if (dp[i] == long_inf) continue;
        ans = i;
        break;
    }
    cout << ans << endl;
}

int main() {
    //ios::sync_with_stdio(false);
    //cout << std::fixed;
    //cout << setprecision(16);
#ifdef _zzz_
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    //precalc();
    int T = 1;
    //scanf("%d", &T);
    cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}

/**
 *  1. obeserved the length in the final result is small. That's because the weight above increases dramatically. Using a Python script determined the length can be up to 140 for w = 1e9.
    A small issue:
        1. if condition was wrong as "dp[j] <= weight[i] * 1LL * 6"
*/
