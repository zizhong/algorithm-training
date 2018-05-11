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
#include <unordered_set>
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
const string imp = "IMPOSSIBLE";
const ll long_inf = 1LL<<60;

const int N = 1000000 + 10;
const int LGN = 21;


int f[N][LGN];
int st[N];
int d[N];
vector<vector<int>> tree;
int n, k;


void dfs(int r) {
    int top = 0;
    st[top++] = r;
    d[r] = 1;
    while(top) {
        int u = st[--top];
        for(auto v : tree[u]) {
            if (v == f[u][0]) continue;
            f[v][0] = u;
            d[v] = d[u]+1;
            st[top++] = v;
        }
    }
}


int calc_need(int x, vector<bool>& in) {
    if (in[x]) return 0;
    int z = x;
    for(int i = 20; i >= 0; i--) {
        if (f[x][i] == -1 || in[f[x][i]]) continue;
        x = f[x][i];
    }
    return d[z] - d[x] + 1;
}

void pr_uint(unsigned int n) {
    if (n / 10 != 0)
        pr_uint(n / 10);
    putchar((n % 10) + '0');
}

unsigned int get_uint() {
    int x = 0;
    char c;
    while(isdigit(c = getchar())) x = x * 10 + c - '0';
    return x;
}

void solve(int ncase) {
    //cout << "Case #" << ncase << ": ";
    //scanf("%d%d", &n, &k);
    n = get_uint();
    k = get_uint();
    tree.resize(n + 1);
    for(int i = 0; i < n - 1; i++) {
        int x, y;
        //scanf("%d%d", &x, &y);
        x = get_uint();
        y = get_uint();
        tree[x].push_back(y);
        tree[y].push_back(x);
    }
    memset(f[n], -1, sizeof(f[n]));
    vector<bool> in(n + 1);
    int keep = n - k;
    dfs(n);
    for(int l = 1; l <= 20; l++) {
        for(int i = 1; i <= n; i++) {
            f[i][l] = f[i][l-1] > 0 ? f[f[i][l-1]][l-1] : -1;
        }
    }

    for(int x = n; x >= 1; x--) {
        int need = calc_need(x, in);
        if (need <= keep) {
            keep -= need;
            for(int u = x; u >= 0 && !in[u]; u = f[u][0]) in[u] = true;
        }
    }
    for(int i = 1; i <= n; i++) {
        if (in[i]) continue;
        pr_uint(i);
        putchar(' ');
        //printf("%d ", i);
    }

}


int main() {
    //ios::sync_with_stdio(false);
    //cout << std::fixed;
    //cout << setprecision(16);
#ifdef _zzz_
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    //precalc();
    int T = 1;
    //scanf("%d", &T);
    //cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
        //test();
    }
}

/*
    Binary Lifting:
        http://codeforces.com/blog/entry/22325
*/
