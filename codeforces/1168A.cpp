#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <deque>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
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

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator() (const pair<T1, T2>& p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

int ok(const vector<int>& a, int x, int m) {
    int v = 0;
    for(int i = 0; i < a.size(); i++) {
        if (a[i] + x < m) {
            // a[i]...a[i]+x
            if (v > a[i] + x) return false;
            v = max(v, a[i]);
        } else {
            // a[i] .. m - 1
            // 0 .. (a[i] + x) % m
            if (v <= a[i] + x - m) continue;
            if (v >= a[i]) continue;
            v = a[i];
        }
    }
    return true;
}

void solve(int ncase) {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> a(n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    int l = 0, r = m;
    if (ok(a, 0, m)) {
        cout << 0 << endl;
        return;
    }
    while(l + 1 < r) {
        int mid = (l + r) / 2;
        if (ok(a, mid, m)) r = mid;
        else l = mid;
    }
    cout << r << endl;
}

int main() {
    //ios::sync_with_stdio(false);
    //cout << std::fixed;
    //cout << setprecision(9);
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    //precalc();
    int T = 1;
    //scanf("%d", &T);
    // cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
