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

int k, s, l;
string key;
string word;
vector<int> char2cnt;
vector<double> char2p;
int next_status(int st, int c) {
    string pattern;
    for(int i = 0; i < st; i++) pattern.push_back(word[i]);
    pattern.push_back('A' + c);
    for(int i = min(l, (int)pattern.size()) - 1; i >= 0; i--) {
        bool find = true;
        for(int i_w = i, i_p = pattern.size() - 1; i_w >= 0 && i_p >= 0; i_w--, i_p--) {
            if (word[i_w] != pattern[i_p]) {
                find = false;
                break;
            }
        }
        if (find) {
            return i + 1;
        }
    }
    return 0;
}

int calc_max(const vector<vector<int>>& status) {
    int max_next_status = 0;
    for(int i = 0; i < 26; i++) {
        max_next_status = max(max_next_status, status[l][i]);
    }
    int left = l - max_next_status + 1;
    return 1 + (s - l) / left;
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    cin >> k >> l >> s >> key >> word;
    char2cnt.assign(26, 0);
    char2p.assign(26, 0);
    for(auto c: key) char2cnt[c - 'A']++;
    for(auto c : word) {
        if (char2cnt[c - 'A'] == 0) {
            cout << 0.0 << endl;
            return;
        }
    }
    for(int i = 0; i < 26; i++) char2p[i] = char2cnt[i] * 1.0 / k;
    vector<vector<int>> status(l + 1, vector<int>(26, 0));
    for(int i = 0; i <= l; i++) {
        for(int j = 0; j < 26; j++) {
            status[i][j] = next_status(i, j);
            //if (status[i][j]) cout << i << " " << j << " " << status[i][j] << endl;
        }
    }

    int max_banana = calc_max(status);
    vector<double> dp(l + 1);
    dp[0] = 1;
    double banana = 0;
    for(int i = 0; i < s; i++) {
        vector<double> ndp(l + 1);
        for(int st = 0; st <= l; st++) {
            for(int c = 0; c < 26; c++) {
                ndp[status[st][c]] += dp[st] * char2p[c];      
            }
        }
        dp = ndp;
        banana += dp[l];
        //for(int st = 0; st <= l; st++) cout << dp[st] << " "; cout << endl;
    }
    cout << max_banana - banana << endl;
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
