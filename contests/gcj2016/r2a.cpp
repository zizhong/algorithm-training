#include <vector>
#include<cstdio>
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
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;

vector<vector<string>> n2list(13, vector<string>(3));


string gen(const string& s) {
    string ret;
    for(int i = 0; i < s.size(); i++) {
        if (s[i] == 'P') {
            ret.push_back('P');
            ret.push_back('R');
        } else if (s[i] == 'R') {
            ret.push_back('R');
            ret.push_back('S');
        } else {
            ret.push_back('P');
            ret.push_back('S');
        }
    }
    for(int i = 1; i < ret.size(); i<<=1) {
        for(int j = 0; j < ret.size(); j += 2 * i) {
            string a = ret.substr(j, i);
            string b = ret.substr(j + i, i);
            if (a > b) {
                for(int k = 0; k < i; k++) ret[j + k] = b[k];
                for(int k = 0; k < i; k++) ret[j + i + k] = a[k];
            }
        }
    }
    return ret;
}

void precalc() {
    n2list[0] = {"P", "R", "S"};
    for(int i = 1; i <= 12; i++) {
        for(int j = 0; j < 3; j++) {
            n2list[i][j] = gen(n2list[i-1][j]);
        }
    }
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    int n, r, p, s;
    cin >> n >> r >> p >> s;
    string ret = "IMPOSSIBLE";
    for(int i = 0; i < 3; i++) {
        string a = n2list[n][i];
        //cout << n << "-" << a << endl;
        int cnt[128] = {0};
        for(auto c : a) cnt[c]++;
        if (r == cnt['R'] && p == cnt['P'] && s == cnt['S']) {
            if (ret == "IMPOSSIBLE" || ret > a) {
                ret = a;
            }
        }
    }
    cout << ret << endl;
}


int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    //cout << setprecision(16) << endl;
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    int T = 1;
    scanf("%d", &T);
    //cin >> T;
    precalc();
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
