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

int w, h, b;
struct Block {
    int x0, y0, x1, y1;
    void init() {
        cin >> x0 >> y0 >> x1 >> y1;
    }
};

int diff(int a1, int a2, int b1, int b2) {
    if (a2 < b1) {
        return b1 - a2 - 1;
    }
    if (b2 < a1) {
        return a1 - b2 - 1;
    }
    return 0;
}

int dist(const Block& b1, const Block& b2) {
    return max(diff(b1.x0, b1.x1, b2.x0, b2.x1),
               diff(b1.y0, b1.y1, b2.y0, b2.y1));
}

int dijkstra(const vector<vector<int>>& g, int s, int t) {
    int n = g.size();
    vector<int> d(n, inf);
    vector<int> used(n, 0);
    d[s] = 0;
    while(true) {
        int m_idx = -1;
        for(int i = 0; i < n; i++) {
            if (!used[i] && (m_idx == -1 || d[i] < d[m_idx])) {
                m_idx = i;
            } 
        }
        if (m_idx == -1) break;
        used[m_idx] = 1;
        for(int i = 0; i < n; i++) {
            if (!used[i] && g[m_idx][i] < inf) {
                d[i] = min(d[i], d[m_idx] + g[m_idx][i]);
            }
        }
    }
    return d[t];
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    cin >> w >> h >> b;
    vector<Block> vb(b);
    for(int i = 0; i < b; i++) {
        vb[i].init();
    }
    vector<vector<int>> g(b + 2, vector<int>(b + 2, inf));
    int s = b, t = b + 1;
    g[s][t] = g[t][s] = w;
    for(int i = 0; i < b; i++) {
        g[s][i] = g[i][s] = vb[i].x0;
        g[t][i] = g[i][t] = w - 1 - vb[i].x1;
        for(int j = i + 1; j < b; j++) {
            g[i][j] = g[j][i] = dist(vb[i], vb[j]);
            //cout << i << " " << j << " "<< g[i][j] <<endl;
        }
    }
    cout << dijkstra(g, s, t) << endl;
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
