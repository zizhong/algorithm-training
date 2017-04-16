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

PII calc_p(int req, int x) {
    // req * r * 9 <= x * 10
    int r = (x * 10) / (9 * req);
    // x <= req * 1.1 * l
    int l = (x * 10 + 11 * req - 1) / (11 * req);
    return PII(l, r);
}

bool cmp(const PII& p1, const PII& p2) {
    if (p1.second != p2.second) {
        return p1.second < p2.second;
    }
    return p1.first < p2.first;
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    int n, p;
    cin >> n >> p;
    vector<int> r(n);
    for(int i = 0; i < n; i++) cin >> r[i];
    vector<vector<int>> g(n, vector<int>(p));
    vector<vector<PII>> pg(n, vector<PII>());
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < p; j++) {
            cin >> g[i][j];
            PII pii = calc_p(r[i], g[i][j]);
            if (pii.first <= pii.second) {
                pg[i].push_back(pii);
            }
        }
        sort(pg[i].begin(), pg[i].end(), cmp);
    }
    vector<int> idx(n);
    int ret = 0;
    while(true) {
        bool flag = false;
        for(int i = 0; i < n; i++) {
            if (idx[i] == pg[i].size())  {
                flag = true;
                break;
            }   
        }
        if (flag) break;
        int l = pg[0][idx[0]].first, r = pg[0][idx[0]].second, next = 0;
        for(int i = 1; i < n; i++) {
            l = max(l, pg[i][idx[i]].first);
            r = min(r, pg[i][idx[i]].second);
            if (pg[i][idx[i]].second < pg[next][idx[next]].second) {
                next = i;
            }
        }
        if (l <= r) {
            for(int i = 0; i < n; i++) idx[i]++;
            ret++;
        } else {
            idx[next]++;
        }
    }
    cout << ret << endl;
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
    //precalc();
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
