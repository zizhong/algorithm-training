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

const int N = 300010;
char s[N];

void solve(int ncase) {
    scanf("%s", s);
    int n = strlen(s);
    long long ans = 0;
    for(int i = 0; i < n; i++) {
        int x = -1;
        int index[2][4] = {0};
        int ni[2] = {0};
        for(int j = i; x == -1 && j < n; j++) {
            int ii = s[j] - '0';
            index[ii][ni[ii]++] = j;
            for(int a = 0; x == -1 && a < ni[ii] - 2; a++) {
                if (index[ii][a] % 2 != (index[ii][ni[ii]-1]) % 2) continue;
                if (s[j] == s[(index[ii][a] + index[ii][ni[ii]-1]) / 2]) x = j;
            }
        }
        if (x != -1) {
            ans += n - x;
        } else {
            break;
        }
    }
    cout << ans << endl;
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
