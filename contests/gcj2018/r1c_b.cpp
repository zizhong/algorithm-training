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


void solve(int ncase) {
    cout << "Case #" << ncase << ": ";

    int n;
    cin >> n;
    if (n == -1) {
        return;
    }
    vector<int> cnt(n);
    vector<bool> exist(n, true);

    for(int i = 0; i < n; i++) {
        int d;
        cin >> d;
        if (d == -1) {
            return;
        }
        vector<int> choice(d);
        PII ans(-1, inf);
        for(int j = 0; j < d; j++) {
            cin >> choice[j];
            cnt[choice[j]]++;
            if (!exist[choice[j]]) continue;
            if (ans.second >= cnt[choice[j]]) {
                ans = PII(choice[j], cnt[choice[j]]);
            }
        }
        if (ans.first >= 0) exist[ans.first] = false;
        cout << ans.first << endl;
    }
}

int main() {
    //ios::sync_with_stdio(false);
    //cout << std::fixed;
    //cout << setprecision(16);
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
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
    debugging with testing_tool.py

    some small issues:
        1. if condition was wrong as "cnt[ans.second] >= cnt[choice[j]]";
        2. missed "if (ans.first >= 0)" check leads to invalid range access.
        3. not commenting out `cout << "Case #" <<` leads to fail to read integer on server side.
*/
