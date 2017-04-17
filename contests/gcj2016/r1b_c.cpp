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

int n;
vector<PSS> sheet;
vector<string> firstlist, secondlist;

//Hungarian start
int na, nb;
vector<vector<int>> g;
vector<int> matcha, matchb;
vector<int> check;

bool dfs(int x) {
    for(auto v : g[x]) {
        if (!check[v]) {
            check[v] = 1;
            if (matchb[v] == -1 || dfs(matchb[v])) {
                matcha[x] = v;
                matchb[v] = x;
                return true;
            }
        }
    }
    return false;
}

int hungarin() {
    int ret = 0;
    na = firstlist.size();
    nb = secondlist.size();
    matcha.assign(na, -1);
    matchb.assign(nb, -1);
    for(int u = 0; u < na; u++) {
        if (matcha[u] == -1) {
            check.assign(nb, 0);
            if (dfs(u)) ret++;
        }
    }
    return ret;
}

//Hungarin end

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    firstlist.clear();
    secondlist.clear();
    sheet.clear();
    cin >> n;
    for(int i = 0; i < n; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        sheet.push_back(PSS(s1, s2));
        firstlist.push_back(s1);
        secondlist.push_back(s2);
    }
    sort(firstlist.begin(), firstlist.end());
    firstlist.erase(unique(firstlist.begin(), firstlist.end()), firstlist.end());
    sort(secondlist.begin(), secondlist.end());
    secondlist.erase(unique(secondlist.begin(), secondlist.end()), secondlist.end());
    g.assign(firstlist.size(), vector<int>());
    for(auto p : sheet) {
        int u = lower_bound(firstlist.begin(), firstlist.end(), p.first) - firstlist.begin();
        int v = lower_bound(secondlist.begin(), secondlist.end(), p.second) - secondlist.begin();
        g[u].push_back(v);
    }
    int ans = hungarin();
    for(int i = 0; i < na; i++) ans += (matcha[i] == -1);
    for(int i = 0; i < nb; i++) ans += (matchb[i] == -1);
    cout << n - ans << endl;
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
