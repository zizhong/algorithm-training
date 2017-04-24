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
typedef pair<ll, PII> PLP;
#define CLS(x, v) (memset((x), (v), sizeof((x))))



void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    int n;
    cin >> n;
    priority_queue<PLP, vector<PLP>, greater<PLP>> hiker;
    for(int i = 0; i < n; i++) {
        int d, h, m;
        cin >> d >> h >> m;
        for(int j = 0; j < h; j++) {
            hiker.push(PLP((360 - d) * 1LL * (m + j), PII(1, m + j)));
        }
    }
    int left = hiker.size();
    ll ret = hiker.size();
    ll passed = 0;
    while(passed <= ret) {
        PLP head = hiker.top();
        int first = 0;
        while(hiker.size() && passed <= ret && hiker.top().first == head.first) {
            PLP cur = hiker.top();
            hiker.pop();
            if (cur.second.first == 1) {
                left--;
            } else {
                passed++;
            }
            hiker.push(PLP(cur.first + cur.second.second * 360LL, PII(2, cur.second.second)));
        }
        ret = min(ret, passed + left);
    }
    cout << ret << endl;
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
