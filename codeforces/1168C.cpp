#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <deque>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
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

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator() (const pair<T1, T2>& p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

const int N = 300010;
int n, q;
int d[N];
int f[N][20];

void solve(int ncase) {
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) scanf("%d", &d[i]);
    vector<int> last(20, n+1);
    for(int i = n; i >= 1; i--) {
        for(int k = 0; k < 20; k++) {
            f[i][k] = n + 1;
        }
        for(int k = 0; k < 20; k++) {
            if ((1<<k) & d[i]) {
                if (last[k] <= n) {
                    for(int j = 0; j < 20; j++) {
                        f[i][j] = min(f[i][j], f[last[k]][j]);
                    }
                }
                f[i][k] = i;
                last[k] = i;
            }
        }
    }
    while(q--) {
        int x, y;
        scanf("%d%d", &x, &y);
        bool flag = false;
        for(int k = 0; !flag && k < 20; k++) {
            if (d[y] & (1 << k)) {
                if (f[x][k] <= y) flag = true;
            }
        }
        printf("%s\n", flag ? "Shi" : "Fou");
    }
}

int main() {
    //ios::sync_with_stdio(false);
    //cout << std::fixed;
    //cout << setprecision(9);
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    //precalc();
    int T = 1;
    //scanf("%d", &T);
    // cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
