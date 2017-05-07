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

int n;
void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    cin >> n;
    vector<int> num(n);
    for(int i = 0; i < n; i++) {
        cin >> num[i];
    }
    vector<int> a = num;
    sort(a.begin(), a.end());
    for(int i = 0; i < n; i++) {
        num[i] = lower_bound(a.begin(), a.end(), num[i]) - a.begin();
    }
    int ret = 0;
    for(int i = 0; i < n; i++) {
        int idx = 0;
        for(int j = 0; j < n; j++) {
            if (num[j] == i) {
                idx = j;
                break;
            }
        }
        int left = 0, right = 0;
        for(int j = 0; j < n; j++) {
            if (num[j] > i) {
                if (j < idx) left++;
                else right++;
            }
        }
        ret += min(right, left);
    }
    cout << ret << endl;
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
