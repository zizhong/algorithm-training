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

int n, p;
vector<int> a;
vector<int> b;

bool ok(double t) {
    double changeT = 0;
    for(int i = 0; i < n; i++) {
        double e = a[i] * t - b[i];
        if (e > 0) {
            changeT += e / p;
        }
        if (changeT > t) return false;
    }
    return true;
}

void solve(int ncase) {
    //cout << "Case #" << ncase << ": ";
    double l = 0, r = 1e40;
    cin >> n >> p;
    a.assign(n, 0);
    b.assign(n, 0);
    double suma = 0, sumb = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d%d", &a[i], &b[i]);
        suma += a[i];
        sumb += b[i];
    }
    if (suma <= p) {
        cout << -1 << endl;
        return;
    }
    for(int i = 0; i < 1000; i++) {
        double mid = 0.5 * (l + r);
        if (ok(mid)) l = mid;
        else r = mid;
    }
    cout << l << endl;
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
    //scanf("%d", &T);
    //cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
