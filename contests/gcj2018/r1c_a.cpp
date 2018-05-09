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


void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    int n, l;
    cin >> n >> l;
    vector<string> word(n);
    for(int i = 0; i < n; i++) {
        cin >> word[i];
    }
    unordered_set<string> pre_prefix;
    for(int c = 0; c < l; c++) {
        unordered_set<string> existed_prefix;
        for(int i = 0; i < n; i++) {
            existed_prefix.insert(word[i].substr(0, c + 1));
        }
        int char_exists[26] = {0};
        for(int i = 0; i < n; i++) {
            char_exists[word[i][c]-'A'] = 1;
        }
        for(int i = 0; i < 26; i++) {
            if (!char_exists[i]) continue;
            for(auto& s : pre_prefix) {
                string n_prefix = s + string(1, 'A' + i);
                if (existed_prefix.find(n_prefix) == existed_prefix.end()) {
                    cout << n_prefix + word[0].substr(c + 1) << endl;
                    return;
                }
            }
        }
        swap(pre_prefix, existed_prefix);
    }
    cout << '-' << endl;
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
    cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}

/**
    Ad hoc
*/
