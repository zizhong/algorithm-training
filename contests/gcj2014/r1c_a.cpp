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

ll p, q;
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    scanf("%lld/%lld", &p, &q);
    ll d = gcd(p, q);
    p /= d;
    q /= d;
    if ((1LL << 40) % q) {
        cout << "impossible" << endl;
        return;
    }
    int ans = 0;
    while(p < q) {
        q/=2;
        ans++;
    }
    cout << ans << endl;
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
