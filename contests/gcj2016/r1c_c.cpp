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

const int N = 128;

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    int j, p, s, k;
    cin >> j >> p >> s >> k;
    k = min(k, s);
    cout << j * p * k << endl;
    for(int x = 1; x <= j; x++) {
        for(int y = 1; y <= p; y++) {
            int z = (x + y) % s + 1;
            for(int i = 0; i < k; i++) {
                cout << x << ' ' << y << ' ' << z << endl;
                z = z % s + 1;
            }
        }
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
    scanf("%d", &T);
    //cin >> T;
    //precalc();
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
