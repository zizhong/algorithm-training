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


int n, k;
double p[256];

double dp(const vector<int>& idx) {
    vector<vector<double>> f(n, vector<double>(n+1));
    f[0][0] = 1 - p[idx[0]];
    f[0][1] = p[idx[0]];
    for(int i = 1; i < k; i++) {
        for(int j = 0; j <= n; j++) {
            f[i][j] = (1 - p[idx[i]]) * f[i-1][j];
            if (j) f[i][j] += p[idx[i]] * f[i-1][j-1];
        }
    }
    return f[k-1][k/2];
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> p[i];
    }
    sort(p, p + n);
    double ans = 0;
    for(int i = 0; i <= k; i++) {
        vector<int> idx;
        for(int j = 0; j < i; j++) idx.push_back(j);
        for(int j = n - 1; idx.size() < k; j--) idx.push_back(j);
        ans = max(ans, dp(idx));
    }
    cout << ans << endl;
}


int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    cout << setprecision(16);
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
