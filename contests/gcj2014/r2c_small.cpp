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
#include "utils/max_flow.h"
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

int W, H, B;
int in_num(int x, int y) {
    return x * W + y;
}
int out_num(int x, int y) {
    return W * H + x * W + y;
}
void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    cin >> W >> H >> B;
    vector<vector<int>> river(H, vector<int>(W, 0));
    for(int i = 0; i < B; i++) {
        int x0, y0, x1, y1;
        cin >> x0 >> y0 >> x1 >> y1;
        for(int x = x0; x <= x1; x++) {
            for(int y = y0; y <= y1; y++) {
                river[y][x] = 1;
            }
        }
    }
    init();
    int s = 0, t = 1;
    int offset = 2;
    for(int i = 0; i < W; i++) {
        // s->H=0
        if (!river[0][i]) add_edge(s, offset + in_num(0, i), 1);
        // H-1->t
        if (!river[H - 1][i]) add_edge(offset + out_num(H - 1, i), t, 1);
    }
    const int d[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            if (river[i][j]) continue;
            add_edge(offset + in_num(i, j), offset + out_num(i, j), 1);
            for(int k = 0; k < 4; k++) {
                int x = i + d[k][0];
                int y = j + d[k][1];
                if (x < 0 || x >= H || y < 0 || y >= W || river[x][y]) continue;
                add_edge(offset + out_num(x, y), offset + in_num(i, j), 1);
            }
        }
    }
    cout << max_flow(s, t) << endl;
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
