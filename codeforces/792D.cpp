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

void solve(int ncase) {
    ll n;
    cin >> n;
    int q;
    cin >> q;
    while(q--) {
        ll x;
        cin >> x;
        string s;
        cin >> s;

        for(int i = 0; i < s.size(); i++) {
            ll y = (x & -x);
            if (s[i] == 'U') {
                // if x is a right child, the binary of x is following the pattern of '.*110{0,}'
                if (x & (y << 1)) {
                    x -= y;
                } else {
                    if (x + y > n) continue;
                    x += y;
                }
            } else {
                x += (s[i] == 'L' ? -(y>>1) : (y>>1));
            }
        }
        cout << x << endl;
    }
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
    //scanf("%d", &T);
    //cin >> T;
    //precalc();
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
