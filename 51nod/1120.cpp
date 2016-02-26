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

const int mod = 10007, MAX_P = mod + 10;
int fact[MAX_P];
void precalc() {
    fact[1] = 1;
    for(int i = 2; i < mod; i ++) {
        fact[i] = fact[i - 1] * i % mod;
    }
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
// ret = n! % p = (ret * p^e) % p
ll mod_fact(ll n, ll p, ll& e) {
    e = 0;
    if (n == 0) return 1;
    ll res = mod_fact(n / p, p, e);
    e += n / p;
    if (n / p % 2 != 0) return res * (p - fact[n % p]) % p;
    return res * fact[n % p] % p;
}
// C(k,n) % p
ll mod_comb(ll n, ll k, ll p) {
    if (n < 0 || k < 0 || n < k) return 0;
    ll e1, e2, e3;
    ll a1 = mod_fact(n, p, e1), a2 = mod_fact(k, p, e2), a3 = mod_fact(n - k, p, e3);
    if (e1 > e2 + e3) return 0;
    return a1 * mod_inverse(a2 * a3 % p, p) % p;
}
void solve(int ncase) {
    ll n;
    cin >> n;
    n --;
    ll ans = 2 * mod_comb(2 * n, n, mod) * mod_inverse(n + 1, mod) % mod;
    cout << ans << endl;
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
