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
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;
#define CLS(x, v) (memset((x), (v), sizeof((x))))



void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    int n;
    cin >> n;
    vector<PII> hiker;
    for(int i = 0; i < n; i++) {
        int d, h, m;
        cin >> d >> h >> m;
        for(int j = 0; j < h; j++) {
            hiker.push_back(PII(m + j, d));
        }
    }
    sort(hiker.begin(), hiker.end());
    if (hiker.size() <= 2) {
        if (hiker.size() <= 1) {
            cout << 0 << endl;
            return;
        }
        ll fast2 = (720 - hiker[0].second) * 1LL * hiker[0].first;
        ll slow1 = (360 - hiker[1].second) * 1LL * hiker[1].first;
        cout << (slow1 >= fast2) << endl;
    }
}


int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    cout << setprecision(16);
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
