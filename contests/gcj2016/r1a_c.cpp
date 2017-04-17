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
int fa[1024];
int mark[1024];
vector<vector<int>> g;

int findpath(int x, int pre) {
    mark[x] = 1;
    int ans = 0;
    for(auto c : g[x]) {
        if (c != pre) {
            ans = max(ans, findpath(c, x)); 
        }
    }
    return ans + 1;
}

int flag;

int findcycle(int x) {
    mark[x] = flag;
    vector<int> path(1, x);
    while(mark[fa[x]] != flag) {
        mark[fa[x]] = flag;
        path.push_back(fa[x]);
        x = fa[x];
    }
    int ans = 0;
    for(int i = path.size() - 1; i >= 0; i--) {
        ans ++;
        if (path[i] == fa[x]) return ans;
    }
    return 0;
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    cin >> n;
    g.assign(n+1, vector<int>());
    for(int i = 1; i <= n; i++) {
        mark[i] = 0;
        cin >> fa[i];
        g[fa[i]].push_back(i);
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            if (fa[i] == j && fa[j] == i) {
                    ans += findpath(i, j) + findpath(j, i);
            }
        }
    }
    flag = 1;
    for(int i = 1; i <= n; i++) {
        if (mark[i] == 0) {
            ++flag;
            ans = max(ans, findcycle(i));
        }
    }
    cout << ans << endl;
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
