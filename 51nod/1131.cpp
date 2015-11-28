/*
desc:
    Given two integer range [a, b], [x, y].
    We can use some integers from [a, b] to add up to cover 
    some integers from [x, y]. Each integer can use multiple times.
    Caclulate how many integers can we cover in this way?
solu:
    math
*/
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

void precalc() {}
ll x, y, a, b;
ll calc(ll n) {
    if (a > n) return 0;
    if (a == b) {
        return n / a;
    }
    ll p1 = a / (b - a);
    ll p2 = n / b;
    ll ans = 0;
    ll m = min(p1, p2);
    ans = m * (b - a + 1 + b - a + 1 + (m - 1) * (b - a)) / 2;
    ll m2 = max(m * b + 1, a * (m + 1));
    ans += (n >= m2 ? n - m2 + 1 : 0); 
    return ans;
}
void solve(int ncase) {
    cin >> a >> b >> x >> y;
    cout << calc(y) - calc(x - 1) << endl;
}
int main() {
    //ios::sync_with_stdio(false);
    //cout << std::fixed << setprecision(16);
    //init();
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
    //freopen("A-small-practice.in", "r", stdin);
    //freopen("A-large-practice.in", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    int T = 1;
    precalc();
    cin >> T;
    //scanf("%d", &T);
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
