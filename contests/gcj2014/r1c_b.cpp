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


int n;
vector<vector<int>> g;
vector<vector<int>> g2;
vector<int> alone;
bool classify(const string& s) {
    int headidx = 0;
    int tailidx = s.size() - 1;
    for(; headidx + 1 < s.size() && s[headidx + 1] == s[headidx]; headidx++);
    for(; tailidx - 1 >= 0 && s[tailidx - 1] == s[tailidx]; tailidx--);
    if (alone[s[0] - 'a'] || alone[s[s.size() - 1] - 'a']) return false;
    for(int i = headidx + 1; i < tailidx; i++) {
        int key = s[i] - 'a';
        if (i == headidx + 1) {
            g2[s[0] - 'a'][key] = 1;
            g2[key][s[s.size() - 1] - 'a'] = 1;
        }
        if (alone[key]) return false;
        alone[key] = 1;
        int j = i;
        while( j < tailidx && s[j] == s[i]) j++;
        i = j - 1;
    }
    if (headidx + 1 < tailidx) if (s[0] == s[s.size()-1]) return false;
    g[s[0] - 'a'][s[s.size() - 1] - 'a'] ++;
    return true;
}
void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    cin >> n;
    g.assign(26, vector<int>(26, 0));
    g2.assign(26, vector<int>(26, 0));
    alone.assign(26, 0);
    bool impossible = false;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (!impossible && !classify(s)) impossible=true;
    }
    if (impossible) {
        cout << 0 << endl;
        return;
    }
    vector<int> in_degree(26);
    vector<int> exist(26);
    vector<int> next(26, -1);
    for(int i = 0; i < 26; i++) {
        int prefix = 0;
        int suffix = 0;
        for(int j = 0; j < 26; j++) {
            if (i == j) continue;
            if (g[i][j]) {
                exist[j] = exist[i] = 1;
                in_degree[j]++;
                next[i] = j;
                if (alone[i] || alone[j]) impossible = true;
            }
            if (g[i][j]) prefix+=g[i][j];
            if (g[j][i]) suffix+=g[j][i];
            if (g[i][j] && g[j][i]) {
                cout << 0 << endl;
                return;
            }
        }
        if (prefix > 1 || suffix > 1) {
            cout << 0 << endl;
            return;
        }
    }
    vector<int> used(26);
    int segment = 0;
    for(int i = 0; !impossible && i < 26; i++) {
        if (exist[i] == 0 || used[i] || in_degree[i]) continue;
        int x = i;
        segment++;
        while(x != -1) {
            if (used[x]) {
                impossible = true;
                break;
            }
            used[x] = 1;
            x = next[x];
        }
    }
    for(int i = 0; !impossible && i < 26; i++) {
        if (exist[i] && !used[i]) impossible = true;     
    }
    if (impossible) {
        cout << 0 << endl;
        return;
    }
    for(int i = 0; i < 26; i++) {
        if (!exist[i] && g[i][i]) segment++;     
    }
    ll ans = 1;
    for(int i = 1; i <= segment; i++) {
        ans = ans * i % mod;
    }
    for(int i = 0; i < 26; i++) {
        for(int j = 1; j <= g[i][i]; j++) {
            ans = ans * j % mod;
        }
    }
    cout << ans << endl;
}

int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    cout << setprecision(9);
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
