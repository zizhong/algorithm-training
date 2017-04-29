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


vector<vector<int>> tree;

int dfs(int r, int pre) {
    vector<int> cmax;
    for(auto c : tree[r]) {
        if (c == pre) continue;
        cmax.push_back(dfs(c, r));
    }
    if (cmax.size() < 2) {
        return 1;
    }
    sort(cmax.begin(), cmax.end(), greater<int>());
    return 1 + cmax[0] + cmax[1];
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    int n;
    cin >> n;
    tree.assign(n, vector<int>());
    for(int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }
    int ans = 0;
    for(int r = 0; r < n; r++) {
        ans = max(ans, dfs(r, -1)) ;       
    }
    cout << n - ans << endl;
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
