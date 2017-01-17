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

const int mod = 1000000007;
const int N = 2010;
int r[N];
ll fact[N], inv_fact[N];


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

void precalc() {
    fact[0] = 1;
    for(int i = 1; i < N; i ++) {
        fact[i] = fact[i - 1] * i % mod;
    }
    inv_fact[N - 1] = mod_inverse(fact[N - 1], mod);
    for(int i = N - 1; i >= 1; i--) {
        inv_fact[i-1] = inv_fact[i] * i % mod;
    }
}
ll f(ll empty, ll n) {
    if (empty < 0) return 0;
    ll ret = 1;
    for(int i = empty + 1; i <= empty + n; i++) ret = ret * 1LL * i % mod;
    return ret * inv_fact[n] % mod;
}
void solve(int ncase) {
    int n, m;
    cin >> n >> m;
    // c(s+ri+rj+n-2,n-2)
    int sum = 0;
    for(int i = 0; i < n; i++) {
         cin >> r[i];
         sum += 2 * r[i];
    }
    ll result = 0;
    if (n == 1) {
        result = m;
    } else {
        int count[2*N] = {0};
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if (i != j) count[r[i]+r[j]]++;
            }
        }
        ll empty = m - 1 - sum;
        for(int i = 0; i < 2 * N - 1; i++) {
            if (count[i]) {
                result = (result + count[i] * f(empty + i, n) % mod * fact[n-2] % mod) % mod;
            }
        }
    }
    cout << "Case #" << ncase << ": " << result << endl;
}


int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    //cout << setprecision(16) << endl;
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    int T = 1;
    scanf("%d", &T);
    //cin >> T;
    precalc();
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
