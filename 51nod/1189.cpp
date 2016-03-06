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
#include <list>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> PII;
typedef pair<int, double> PID;
typedef pair<string, int> PSI;
typedef pair<string, string> PSS;
typedef pair<PII, int> PIP;

const int N = 1000000 + 10, mod = 1e9+7+1e-9;
int isNotP[N], plist[N], np;
void precalc() {
    for(int i = 2; i < N; i ++) {
        if (!isNotP[i]) {
            plist[np ++] = i;
            for(int j = i + i; j < N; j += i) {
                isNotP[j] = 1;
            }
        }
    }
    //cout << np << endl;
}

ll extgcd(ll a, ll b, ll& x, ll& y) {
    ll d = a;
    if (b != 0) {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    } else {
        x = 1; y = 0;
    }
    return d;
}
// ouput * a = 1 (%m)
ll mod_inverse(ll a, ll m) {
    ll x, y;
    extgcd(a, m, x, y);
    return (m + x % m) % m;
}
void solve(int ncase) {
    int n;
    cin >> n;
    ll ans = 1;
    for(int i = 0; i < np && plist[i] <= n; i ++) {
        ll pp = plist[i];
        ll tmp = 0;
        for(pp = plist[i]; pp <= n; pp *= plist[i]) tmp += n / pp;
        ans = ans * (tmp * 2 + 1) % mod;
        //cout << tmp << " " << plist[i] << endl;
    }
    cout << (ans + 1) * mod_inverse(2, mod) % mod << endl;
}
int main() {
    //ios::sync_with_stdio(false);
    //cout << std::fixed << setprecision(16);
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
    //freopen("A-small-practice.in", "r", stdin);
    //freopen("A-large-practice.in", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    int T = 1;
    precalc();
    //cin >> T;
    //scanf("%d", &T);
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
