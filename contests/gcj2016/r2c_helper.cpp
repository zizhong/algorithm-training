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
#define CLS(x, v) (memset((x), (v), sizeof((x))))

int r, c;
int paired[64];
int tri[4][16][16]; // up, right, down, left
int num[4][16][16]; // up, right, down, left

enum DIRECTION {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

PIP calc_init_pos(int x) {
    PIP ret;
    int z = x;
    if (x <= c) {
        num[UP][0][x - 1] = z;
        return PIP(UP, PII(0, x - 1));
    }
    x -= c;
    if (x <= r) {
        num[RIGHT][x - 1][c - 1] = z;
        return PIP(RIGHT, PII(x - 1, c - 1));
    }
    x -= r;
    if (x <= c) {
        num[DOWN][r - 1][c - x] = z;
        return PIP(DOWN, PII(r - 1, c - x));
    }
    x -= c;
    num[LEFT][r - x][0] = z;
    return PIP(LEFT, PII(r - x, 0));
}


struct Pairs {
    vector<PII> pv;
    vector<string> g;
    void show() {
        cout << string(10, '-') << endl;
        for(auto p : pv) printf("<%d, %d> ", p.first, p.second); cout << endl;
        for(auto s : g) cout << s << endl;
        cout << endl;
    }
};


void dfs(int dir, int x, int y, vector<int>& next, int cur, const vector<string>& g) {
    if (x < 0 || x >= r || y < 0 || y >= c) return;
    if (tri[dir][x][y] != -1 || next.size() > 1) return;
    //printf("dir [%d], x [%d], y [%d], cur [%d], next.size() [%d], num[dir][x][y] [%d]\n", dir, x, y, cur, next.size(), num[dir][x][y]);
    tri[dir][x][y] = 1;
    if (num[dir][x][y] != -1 && num[dir][x][y] != cur) {
        next.push_back(num[dir][x][y]);
        if (next.size() > 1) return;
    }
    if (dir == UP) {
        dfs(DOWN, x - 1, y, next, cur, g);
        dfs(g[x][y] == '/' ? LEFT : RIGHT, x, y, next, cur, g);
    } else if (dir == RIGHT) {
        dfs(LEFT, x, y + 1, next, cur, g);
        dfs(g[x][y] == '/' ? DOWN: UP, x, y, next, cur, g);
    } else if (dir == DOWN) {
        dfs(UP, x + 1, y, next, cur, g);
        dfs(g[x][y] == '/' ? RIGHT: LEFT, x, y, next, cur, g);
    } else {
        dfs(RIGHT, x, y - 1, next, cur, g);
        dfs(g[x][y] == '/' ? UP: DOWN, x, y, next, cur, g);
    }
}


vector<Pairs> ans[17][17];

void calc_all() {
    int b = r * c;
    for(int t = 0; t < 1<<b; t++) {
        vector<string> g(r, string(c, '/'));
        for(int j = 0; j < r; j++) {
            for(int k = 0; k < c; k++) {
                if ((1<<(j * c + k)) & t) {
                    g[j][k] = '\\';
                }
            }
        }
        Pairs p;
        p.g = g;

        CLS(paired, -1);
        CLS(tri, -1);
        CLS(num, -1);

        for(int i = 1; i <= 2 * (r + c); i++) {
            PIP pip = calc_init_pos(i);
        }

        vector<PII> pv;
        int flag = true;
        for(int i = 1; i <= 2 * (r + c); i++) {
            if (paired[i] != -1) continue;
            vector<int> next;
            PIP pos = calc_init_pos(i);
            dfs(pos.first, pos.second.first, pos.second.second, next, i, g);
            if (next.size() != 1) {
                flag = false;
                break;
            }
            paired[i] = next[0];
            paired[next[0]] = i;
            pv.push_back(PII(i, next[0]));
        }
        if (flag == false) continue;
        p.pv = pv;
        p.show();
        ans[r][c].push_back(p);
    }
    printf("ans[%d][%d] = [%d]\n", r, c, ans[r][c].size());
}


void precalc() {
    for(int sum = 9; sum <= 9; sum++) {
        for(r = 3; r <= 16; r++) {
            for(c = 3; c <= 16; c++) {
                if (r * c == sum) {
                    calc_all();
                }
            }
        }
    }

}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
}


int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    cout << setprecision(16);
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    precalc();
    int T = 1;
    scanf("%d", &T);
    //cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
