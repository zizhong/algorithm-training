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

void solve(int ncase) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> ingrade(n, vector<int>(m, m * n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(int ii = 0; ii < n; ii++) {
                for(int jj = 0; jj < m; jj++) {
                    if (invalid(i, j, ii, jj)) ingrade[i][j]--;
                }
            }
        }
    }
    vector<PII> ans;
    const PII NOP = PII(-1,-1);
    vector<vector<int>> used(n, vector<int>(m));
    while(true) {
        // find pair with mini ingrade that is valid with the previous pair
        PII prep = ans.size() ? ans.back() : NOP;
        PII nextp = NOP;
        int mini_in = n * m;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if (!used[i][j] && (prep == NOP || !invalid(prep.first, prep.second, i, j)) && ingrade[i][j] < mini_in) {
                    nextp = PII(i, j);
                    mini_in = ingrade[i][j];
                }
            }
        }
        if (nextp == NOP) {
            break;
        }
        ans.push_back(nextp);
        // update ingrade for all the unused invalid pairs <ingrade, vs>
        used[nextp.first][nextp.second] = 1;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if (!used[i][j] && !invalid(i, j, nextp.first, nextp.second)) {
                    ingrade[i][j] --;
                }
            }
        }
    }
    cout << "Case #" << ncase << ": " << (ans.size() == n * m ? "POSSIBLE" : "IMPOSSIBLE") << endl;
    if (ans.size() == n * m) {
        for(auto p : ans) {
            cout << p.first + 1 << " " << p.second + 1 << endl;
        }
    }
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
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
