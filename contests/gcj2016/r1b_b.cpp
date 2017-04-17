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

ll toint(const string& s) {
    ll ret = 0;
    for(int i = 0; i < s.size(); i++) {
        ret = ret * 10 + s[i] - '0';
    }
    return ret;
}

void update(const string& tmps1, const string& tmps2, string& ret1, string& ret2, ll& diff) {
    ll tmpi1 = toint(tmps1);
    ll tmpi2 = toint(tmps2);
    if (diff == -1 || diff > abs(tmpi1 - tmpi2)) {
        diff = abs(tmpi1 - tmpi2);
        ret1 = tmps1;
        ret2 = tmps2;
        return;
    }
    if (diff < abs(tmpi1 - tmpi2)) return;
    ll i1 = toint(ret1);
    ll i2 = toint(ret2);
    if (tmpi1 < i1) {
        ret1 = tmps1;
        ret2 = tmps2;
        return;
    }
    if (tmpi1 > i1) return;
    if (tmpi2 < i2) {
        ret1 = tmps1;
        ret2 = tmps2;
        return;
    }
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    string s1, s2;
    cin >> s1 >> s2;
    string ret1, ret2;
    ll diff = -1;
    bool same = true;
    int di = -1;
    for(int i = 0; i < s1.size(); i++) {
        if (s1[i] != '?' && s2[i] != '?' && s1[i] != s2[i]) {
            same = false;
            di = i;
            break;
        }
    }
    if (same) {
        string ret;
        for(int i = 0; i < s1.size(); i++) {
            if (s1[i] != '?') ret.push_back(s1[i]);
            else if (s2[i] != '?') ret.push_back(s2[i]);
            else ret.push_back('0');
        }
        cout << ret << " " << ret << endl;
        return;
    }
    for(int i = 0; i <= di; i++) {
        // i is the first index that diff it
        string ts1 = s1, ts2 = s2;
        for(int j = 0; j < i; j++) {
            if (ts1[j] != '?') ts2[j] = ts1[j];
            else if (ts2[j] != '?') ts1[j] = ts2[j];
            else ts1[j] = ts2[j] = '0';
        }
        if (s1[i] != '?' && s2[i] != '?') {
            if (s1[i] == s2[i]) continue;
            if (s1[i] > s2[i]) {
                for(int j = i + 1; j < s1.size(); j++) {
                    if (ts1[j] == '?') ts1[j] = '0';
                    if (ts2[j] == '?') ts2[j] = '9';
                }
            } else {
                for(int j = i + 1; j < s1.size(); j++) {
                    if (ts1[j] == '?') ts1[j] = '9';
                    if (ts2[j] == '?') ts2[j] = '0';
                }
            }
            update(ts1, ts2, ret1, ret2, diff);
        } else if (s1[i] != '?') {
            string tmps1 = ts1, tmps2 = ts2;
            if (s1[i] < '9') {
                tmps2[i] = s1[i] + 1;
                for(int j = i + 1; j < s1.size(); j++) {
                    if (tmps1[j] == '?') tmps1[j] = '9';
                    if (tmps2[j] == '?') tmps2[j] = '0';
                }
                update(tmps1, tmps2, ret1, ret2, diff);
            }
            tmps1 = ts1, tmps2 = ts2;
            if (s1[i] > '0') {
                tmps2[i] = s1[i] - 1;
                for(int j = i + 1; j < s1.size(); j++) {
                    if (tmps1[j] == '?') tmps1[j] = '0';
                    if (tmps2[j] == '?') tmps2[j] = '9';
                }
                update(tmps1, tmps2, ret1, ret2, diff);
            }
        } else if (s2[i] != '?') {
            string tmps1 = ts1, tmps2 = ts2;
            if (s2[i] < '9') {
                tmps1[i] = s2[i] + 1;
                for(int j = i + 1; j < s1.size(); j++) {
                    if (tmps1[j] == '?') tmps1[j] = '0';
                    if (tmps2[j] == '?') tmps2[j] = '9';
                }
                update(tmps1, tmps2, ret1, ret2, diff);
            }
            tmps1 = ts1, tmps2 = ts2;
            if (s2[i] > '0') {
                tmps1[i] = s2[i] - 1;
                for(int j = i + 1; j < s1.size(); j++) {
                    if (tmps1[j] == '?') tmps1[j] = '9';
                    if (tmps2[j] == '?') tmps2[j] = '0';
                }
                update(tmps1, tmps2, ret1, ret2, diff);
            }
        } else {
            string tmps1 = ts1, tmps2 = ts2;
            tmps1[i] = '0'; tmps2[i] = '1';
            for(int j = i + 1; j < s1.size(); j++) {
                if (tmps1[j] == '?') tmps1[j] = '9';
                if (tmps2[j] == '?') tmps2[j] = '0';
            }
            update(tmps1, tmps2, ret1, ret2, diff);
            tmps1 = ts1, tmps2 = ts2;
            tmps1[i] = '1'; tmps2[i] = '0';
            for(int j = i + 1; j < s1.size(); j++) {
                if (tmps1[j] == '?') tmps1[j] = '0';
                if (tmps2[j] == '?') tmps2[j] = '9';
            }
            update(tmps1, tmps2, ret1, ret2, diff);
        }
    }
    cout << ret1 << " " << ret2 << endl;
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
    //precalc();
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
