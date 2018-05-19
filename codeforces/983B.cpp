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
ll gcd(ll a, ll b) {return b ? gcd(b, a % b) : a; }

int sgn(int x) {return x == 0 ? 0 : (x > 0 ? 1 : -1);}
const int N = 5010;

int d[N];
int f[N][N];
void solve(int ncase) {
    //cout << "Case #" << ncase << ": ";
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &d[i]);
        f[i][i] = d[i];
    }
    for(int l = 2; l <= n; l++) {
        for(int i = 1;; i++) {
            int j = i + l - 1;
            if (j > n) break;
            f[i][j] = (f[i][j-1]^f[i+1][j]);
        }
    }
    for(int l = 2; l <= n; l++) {
        for(int i = 1;; i++) {
            int j = i + l - 1;
            if (j > n) break;
            f[i][j] = max(f[i][j], max(f[i][j-1], f[i+1][j]));
        }
    }
    int q;
    scanf("%d", &q);
    while(q--) {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", f[x][y]);
    }
}


int main() {
    ios::sync_with_stdio(false);
    //cout << std::fixed;
    //cout << setprecision(16);
#ifdef _zzz_
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
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
}
