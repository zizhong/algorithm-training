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
int gcd(int a, int b) {return b ? gcd(b, a % b) : a; }

int sgn(int x) {return x == 0 ? 0 : (x > 0 ? 1 : -1);}

void solve(int ncase) {
    //cout << "Case #" << ncase << ": ";
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    // the same Vy - a * Vx
    unordered_map<ll, int> v;
    map<PII, int> p;

    for(int i = 0; i < n; i++) {
        int x0, vx, vy;
        scanf("%d%d%d", &x0, &vx, &vy);
        ll z = vy - a * 1LL * vx;
        v[vy - a * 1LL * vx]++;
        int px = sgn(vx);
        int py = sgn(vy);
        if (vx != 0 && vy != 0) {
            int d = gcd(vx, vy);
            px = vx / abs(d);
            py = vy / abs(d);
        }
        p[PII(px, py)]++;
    }
    ll ans = 0;
    for(auto a: v) {
        ans += a.second * 1LL * (a.second - 1);
    }
    //cout << ans << endl;
    for(auto a: p) {
        ans -= a.second * 1LL * (a.second - 1);
    }
    cout << ans << endl;

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

/*
http://codeforces.com/contest/975/problem/D
    Mathematical induction
        There is N ghosts with velocity (Vx, Vy) in OXY plane.
        In a picture, they all appear on a line y = a * x + b and ghost i at x0_i.
        Output the sum of ghosts collisions.

        Two ghosts A and B collide at Ti means they share the same coordinate (X, Y).
            X = x0_A + Vx_A * Ti = x0_B + Vx_B * Ti
            => Ti = (x0_B - x0_A) / (Vx_A - Vx_B).
        For Y, we can also have
            Ti = (y0_B - y0_A) / (Vy_A - Vy_B).
            => Ti = (a * x0_B + b - (a * x0_A + b)) / (Vy_A - Vy_B)
            => (x0_B - x0_A) / (Vx_A - Vx_B) = a * (x0_B - x0_A) / (Vy_A - Vy_B)
            => 1 / (Vx_A - Vx_B)  = a / (Vy_A - Vy_B)
            => (Vy_A - Vy_B) = a * (Vx_A - Vx_B)
            => a * Vx_A - Vy_A = a * Vx_B - Vy_B
        So, if two ghosts have the same a * Vx - Vy, they collide.

        However, if they parallel, no collision can happen.

*/
