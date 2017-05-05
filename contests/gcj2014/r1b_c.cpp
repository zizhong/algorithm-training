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

vector<string> zip;
vector<PSI> city;
vector<vector<int>> g;
int n, m;
void dfs(int r, vector<int>& used, int &fetch) {
    if (used[r]) return;
    //printf("can fetch [%d]\n", r);
    used[r] = 2;
    fetch++;
    for(int i = 0; i < n; i++) {
        if (g[r][i]) dfs(i, used, fetch);
    }
}

bool check(int r, vector<int> pre, vector<int> used) {
    //printf("\ncheck r[%d]\n", r);
    //for(auto p : pre) cout << "pre " << p << endl;
    while(pre.size() && g[pre.back()][r] == 0) {
        used[pre.back()] = 2;
        pre.pop_back();
    }

    int need = 0;
    for(int i = 0; i < n; i++) {
        //printf("used[%d] = %d\n", i, used[i]);
        if (used[i] != 2) need++;
    }
    int fetch = 0;
    if (pre.size() == 0) return need == fetch;
    for(int i = 0; i < n; i++) {
        if (used[i] == 1) {
            used[i] = 0;
            dfs(i, used, fetch);
        }
    }
    return fetch == need;
}
vector<int> used, can;
void min_spaning_tree(int idx, vector<int>& pre) {
    //printf("\nmin_spaning_tree idx[%d] [%d]", idx, idx+1);
    if (used[idx]) return;
    used[idx] = 1;
    cout << zip[idx];
    for(int i = 0; i < n; i++) {
        if (g[idx][city[i].second])  {
            can[city[i].second]++;
        }       
    }
    while(1) {
        bool skip = true;
        for(int i = 0; i < n; i++) {
            if (used[city[i].second]) continue;
            if (g[idx][city[i].second])  {
                skip = false;
                pre.push_back(idx);
                min_spaning_tree(city[i].second, pre);
                pre.pop_back();
                break;
            }
            if (can[city[i].second]) {
                used[idx] = 2;
                if (check(city[i].second, pre, used)) {
                    skip = true;
                    break;
                }
                used[idx] = 1;
            }
        }
        if (skip) break;
    }
    for(int i = 0; i < n; i++) {
        if (g[idx][city[i].second])  {
            can[city[i].second] --;
        }       
    }
    used[idx] = 2;
}
void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    cin >> n >> m;
    city.clear();
    g.assign(n, vector<int>(n));
    zip.assign(n, "");
    for(int i = 0; i < n; i++) {
        cin >> zip[i];
        city.push_back(PSI(zip[i], i));
    }
    sort(city.begin(), city.end());
    for(int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        g[x][y] = g[y][x] = 1;
    }
    used.assign(n, 0);
    can.assign(n, 0);
    vector<int> pre;
    min_spaning_tree(city[0].second, pre);
    cout << endl;
}

int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    cout << setprecision(9);
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
