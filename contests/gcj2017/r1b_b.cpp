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
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;
#define CLS(x, v) (memset((x), (v), sizeof((x))))

const string noway = "IMPOSSIBLE";

int n, r, o, y, g, b, v;

int memo[3][1024][1024][1024];

void precalc() {CLS(memo, -1);}


bool dfs(int pre, int nr, int ny, int nb, int idx, vector<int>& s) {
    if (nr < 0 || ny < 0 || nb < 0) return false;
    int &tmp = memo[pre][nr][ny][nb];
    if (memo[pre][nr][ny][nb] == -2) return false;
    if (tmp != -1) {
        int p = tmp;
        for(;idx < n; idx++) {
            s[idx] = p;
            if (0 == p) nr--;
            if (1 == p) ny--;
            if (2 == p) nb--;
            p = memo[p][nr][ny][nb];
        }
        //dfs(tmp, nr, ny, nb, idx + 1, s);

        return true;
    }
    if (nr + ny + nb == 0) {
        if (pre == 0) tmp = -2;
        else tmp = pre;
        return tmp >= 0;
    }
    for(int p = 0; p < 3; p++) {
        if (p != pre) {
            int zr = nr;
            int zy = ny;
            int zb = nb;
            if (p == 0) zr--;
            if (p == 1) zy--;
            if (p == 2) zb--;
            if (dfs(p, zr, zy, zb, idx + 1, s)) {
                tmp = p;
                s[idx] = tmp;
                return true;
            }
        }
    }
    tmp = -2;
    return false;
}
string solve_ryb() {
    string cc = "RYB";
    vector<PII> color = {PII(r, 0), PII(y, 1), PII(b, 2)};
    sort(color.begin(), color.end());
    //printf("%c[%d], %c[%d], %c[%d]\n", cc[color[0].second], color[0].first, cc[color[1].second], color[1].first, cc[color[2].second], color[2].first);
    if (r < 0 || y < 0 || b < 0) return noway;
    n = r + y + b;
    vector<int> s(n, -1);
    if (color[0].first == 0) {
        if (color[1].first != color[2].first) {
            return noway;
        }
        for(int i = 0; i < n; i += 2) s[i] = color[1].second;
        for(int i = 1; i < n; i += 2) s[i] = color[2].second;
        string ret;
        for(auto c : s) ret+=cc[c];
        return ret;
    }
    s[0] = 0;
    string ret;
    if (dfs(0, r - 1, y, b, 1, s)) {
        for(auto c : s) ret+=cc[c];
    } else {
        ret = noway;
        //cout << noway << endl;
    }
    return ret;
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    cin >> n;
    cin >> r >> o >> y >> g >> b >> v;
    int n_one = (b > 0) + (r > 0) + (y > 0);
    int n_two = (o > 0) + (g > 0) + (v > 0);
    if (n_two == 0) {
        cout << solve_ryb() << endl;
        return;
    }
    if (n_two == 1 && n_one == 1){
        string ret(n, '-'); 
        if (o > 0) {
            if (b == o) {
                for(int i = 0; i < n; i+= 2) ret[i] = 'B';
                for(int i = 1; i < n; i+= 2) ret[i] = 'O';
            } else {
                ret = noway;
            }
        } else if (g > 0) {
            if (r == g) {
                for(int i = 0; i < n; i+= 2) ret[i] = 'G';
                for(int i = 1; i < n; i+= 2) ret[i] = 'R';
            } else {
                ret = noway;
            }
        } else if (v > 0) {
            if (v == y) {
                for(int i = 0; i < n; i+= 2) ret[i] = 'V';
                for(int i = 1; i < n; i+= 2) ret[i] = 'Y';
            } else {
                ret = noway;
            }
        }
        cout << ret << endl;
        return ;
    }
    
    if (b && b <= o || r && r <= g || y && y <= v) {
        cout << noway << endl;
        return;
    }
    b -= o;
    r -= g;
    y -= v;
    string ret = solve_ryb();
    if (ret == noway) {
        cout << noway << endl;
        return;
    }

    for(auto c : ret) {
        if (c == 'B') {
            cout << "B";
            while(o-- > 0) cout << "OB";
        }
        if (c == 'R') {
            cout << 'R';
            while(g-->0) cout << "GR"; 
        }
        if (c == 'Y') {
            cout << 'Y';
            while(v-->0) cout << "VY"; 
        }
    }
    cout << endl;
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
