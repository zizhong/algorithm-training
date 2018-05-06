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
const string imp = "IMPOSSIBLE";
const int N = 170750;
void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    int n;
    int p;
    cin >> n >> p;
    vector<int> a(n);
    vector<int> b(n);
    vector<double> c(n);

    int sum_a = 0;
    int sum_b = 0;
    double sum_c = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        if (a[i] > b[i]) swap(a[i], b[i]);
        sum_a += a[i];
        sum_b += b[i];
        c[i] = sqrt(a[i] * a[i] + b[i] * b[i]);
        sum_c += c[i];
    }
    if (2 * (sum_a + sum_b + sum_c) <= p) {
        cout << 2 * (sum_a + sum_b + sum_c) << endl;
        return;
    }
    vector<double> d(N, N);

    d[2 * (sum_a + sum_b)] = 0;
    d[2 * (sum_a + sum_b) + 1] = 1;
    for(int k = 0; k < n; k ++) {
        for(int i = N - 1; i >= 0; i--) {
            if (d[i] > 0) continue;
            int r = i, l = i;
            while(l > 0 && d[l] == 0) l--;
            l++;
            i = l;

            int nl = l + 2 * a[k];
            double nr = min(r + 1 - d[r + 1] + 2 * c[k], N - 2.0);
            int ir = (int)nr;
            if (nl <= nr) for(int j = nl; j <= ir; j++) d[j] = 0;
            d[ir + 1] = min(ir + 1 - nr, d[ir + 1]);
            //printf("(%d, %d) -> (%d, %f) d[%d] = %f\n", l, r, nl, nr,ir + 1, d[ir + 1] );
        }
    }
    double ans = 2 * (sum_a + sum_b);

    for(int i = 2 * (sum_a + sum_b); i <= p; i++) {
        if (d[i] > i) continue;
        ans = max(ans, i - d[i]);
    }
    cout << ans << endl;
}

int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    cout << setprecision(16);
#ifdef _zzz_
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    //precalc();
    int T = 1;
    //scanf("%d", &T);
    cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}

/**
    This is the solution for https://codejam.withgoogle.com/2018/challenges/0000000000007883/dashboard/000000000002fff7
    Problem summary:
        Given N (<=100) rectangles with integer width w_i (<=250) and hight h_i(<=250), and integer P (<= 1e8). You can choose to
        cut a rectangle to two halves with the equal area or not.
        Find the sum of perimeters as close to P as possible without exceeding it.

    Analysis:
        Suppose that a rectangle has a side a and a side b where a <= b, and the diagonal c = sqrt(a * a + b * b).
        For a rectangle, we can choose don't do anything and it contributes 2 * (a + b), and if we cut it, it can contribute [2 * (a + b + a), 2 * (a + b + c)].
        There are N independent choices need to be made, brute-force will be O(2^N * P).

        However, results from different decisions can be merged. We only need to consider a range with length P.
        So, we can use backpack DP to solve the problem. If a point pi can be established, when we cut a rectangle j, a range [pi + 2 * a_j, pi + 2 * c_j] can be
            reached. If a range [x, y] can be established (which means all the integer points in the range can be established), when we cut a rectangle j, a new range
            [x + 2 * a_j, y + 2 * c_j] can be reached.

        The time complexity of the DP algorithm is O(N * P).
        Here P is too large to fit into the time limit.But this is only a "paper tiger". The range of w_i and h_i
            is intriguing. Why do they need to be <= 250? That leaves the largest result
                sigma(a_i) + sigma(b_i) + sigma(c_i)
                <= N * 250 + N * 250 + N * sqrt(250 * 250 + 250 * 250)
                <= 250 * 100 * (2 + sqrt(2))
                < 250 * 100 * (2 + 1.415) = 170750,
            which is dramatically less than P (1e8). And the count of operations for each case is around 1.7 * 1e7, so that time can't be the limit.

        Another obstacle is the answer is not in form of integer but double. The error needs to be less than 1e-6. If we convert double into integer by timing 1e6,
            the count of operations is 1.7 * 1e13, too large. The question becomes
                how to represent a double ended range in an array where the index is integer?
            For the rightmost end r, let i_r = (int)r. One way to do this is to store the (i_r + 1 - r) into array[i_r + 1].

*/
