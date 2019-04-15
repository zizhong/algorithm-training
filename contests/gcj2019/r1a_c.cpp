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

bool invalid(int i, int j, int x, int y) {
    return i == x ||
        j == y ||
        i - j == x - y ||
        i + j == x + y;
} 

void solve(int ncase, int n, int m) {
    const int C = 18;
    vector<int> z = {18, 17, 16, 15, 14, 13, 12};
    vector<int> mod;
    for(int ii = 0; ii < 7; ii++) {
        for(int i = 0; i < C; i++) cout << z[ii%7] << (i < C - 1 ? ' ' : '\n');
        int x = 0;
        for(int i = 0; i < C; i++) {
            int y;
            cin >> y;
            x += y;
        }
        mod.push_back(x % z[ii%7]);
    }
    vector<int> choice;
    for(int i = 1; i <= m; i++) {
        bool okay = true;
        for(int j = 0; j < 7; j++) {
            if (i % z[j] != mod[j] % z[j]) {
                okay = false;
                break;
            }
        }
        //if (okay) cout << i << " ";
        if (okay) choice.push_back(i);
    }
    //cout << choice.size() << endl;
    cout << choice[0] << endl;
    int res = 0;
    cin >> res;
    if (res == -1) return;
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
    cin >> T;
    int n, m;
    cin >> n >> m;
    int ncase = 0;
    while(T --) {
        solve(++ ncase, n, m);
    }
    return 0;
}
