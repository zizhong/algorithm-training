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

bool square_product(int x, int y) {
    ll xy = x * 1LL * y;
    if (xy < 0) return false;
    ll z = sqrt(xy);
    return z * z == xy;
}

void solve(int ncase) {
    //cout << "Case #" << ncase << ": ";
    int n;
    cin >> n;
    vector<int> num(n);
    for(int i = 0; i < n; i++) {
        cin >> num[i];
    }
    vector<int> left(n, -1);
    for(int i = 0; i < n; i++) {
        for(int j = i - 1; j >= 0; j--) {
            if(num[j] != 0 && square_product(num[i], num[j])) {
                left[i] = j;
                break;
            }
        }
    }

    vector<int> ans(n + 1);
    for(int i = 0; i < n; i++) {
        int cnt = 1;
        ans[cnt]++;
        bool zero = num[i] == 0;
        for(int j = i + 1; j < n; j++) {
            if (left[j] >= i || zero || num[j] == 0) {
            } else {
                cnt++;
            }
            if (num[j] != 0) zero = false;
            ans[cnt]++;
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }

}

int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    cout << setprecision(16);
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
    }
}

/**
    Given an array A, print an array B where
        B[i] := # of group(sub_array(A)) = i + 1.
        group(array) := min(partition(the product of any pair of integer in the same group is a perfect square)).

    1. For each non zero integer in the same group, it is the same in terms of p1^(k1 % 2) * ... * pn^(kn % 2). So, if A*B is a perfect square,
    B*C is a perfect square, A*C is also a perfect square.
    2. For zero, we need to handle it carefully.
*/
