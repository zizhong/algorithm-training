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



ll dp[32][2][2][2];
int A, B, K;

ll dfs(int idx, bool endA, bool endB, bool endK) {
    if (idx < 0) return 1;
    ll &ans = dp[idx][endA][endB][endK];
    if (ans != -1) return ans;
    ans = 0;
    int eA = endA ? ((A >> idx) & 1) : 1;
    int eB = endB ? ((B >> idx) & 1) : 1;
    int eK = endK ? ((K >> idx) & 1) : 1;
    for(int a = 0; a <= eA; a++) {
        for(int b = 0; b <= eB; b++) {
            for(int k = 0; k <= eK; k++) {
                if ((a & b) == k) {
                    ans += dfs(
                            idx - 1,
                            endA && a == eA,
                            endB && b == eB,
                            endK && k == eK
                            );
                }
            }
        }
    }
    return ans;
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    CLS(dp, -1);
    cin >> A >> B >> K;
    A--, B--, K--;
    cout << dfs(31, true, true, true) << endl;
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
