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

bool canGetMetal(int idx, ll mg, const vector<PII>& f, vector<int>& g, vector<int>& vst) {
    if (g[idx] >= mg) {
        g[idx] -= mg;
        return true;
    }
    if (vst[idx]) return false;
    vst[idx] = 1;
    ll need = mg - g[idx];
    g[idx] = 0;
    bool ret = canGetMetal(f[idx].first, need, f, g, vst) &&
        canGetMetal(f[idx].second, need, f, g, vst);
    vst[idx] = 0;
    return ret;
}

bool okay(ll x, const vector<PII>& f, vector<int> g) {
    vector<int> vst(g.size(), 0);
    return canGetMetal(0, x, f, g, vst);
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    int m;
    cin >> m;
    vector<PII> f(m);
    for(int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        f[i] = PII(x-1, y-1);
    }
    vector<int> g(m);
    for(int i = 0; i < m; i++) {
        cin >> g[i];
    }
    ll l = g[0];
    ll r = 100 * 1e9 + 1;
    while(l + 1 < r) {
        ll mid = (l + 0LL + r) / 2;
        if (okay(mid, f, g)) l = mid;
        else r = mid;
    }
    cout << l << endl;
}

int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    cout << setprecision(16);
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
  Binary search

*/
