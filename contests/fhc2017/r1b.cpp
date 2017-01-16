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
#include <haha.h>
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;

const int inf = 0x3f3f3f3f;

const int d[][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

ll R;

void RectCover(const vector<PLL>& v, vector<vector<int>>& result) {
    for(int i = 0; i < v.size(); i++) {
        for(int j = 0; j < v.size(); j++) {
            for(int t = 0; t < 4; t++) {
                PLL x;
                x.first = min(v[i].first, v[i].first + d[t][0] * R);
                x.second = min(v[j].second, v[j].second + d[t][1] * R);
                vector<int> tmp;
                for(int z = 0; z < v.size(); z++) {
                    if (x.first <= v[z].first && v[z].first <= x.first + R
                           && x.second <= v[z].second && v[z].second <= x.second + R) {
                        tmp.push_back(z);
                    }
                }
                result.push_back(tmp);
            }
        }
    }
}

void solve(int ncase) {
    int n;
    cin >> n >> R;
    vector<PLL> p(n);

    for(int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
    }
    vector<vector<int>> result;
    RectCover(p, result);
    int res = 0;
    for(int i = 0; i < result.size(); i++) {
        for(int j = 0; j < result.size(); j++) {
            vector<int> mark(n);
            int tmp = 0;
            for(auto v: result[i]) {
                if (!mark[v]) {
                    tmp++;
                    mark[v] = 1;
                }    
            }
            for(auto v: result[j]) {
                if (!mark[v]) {
                    tmp++;
                    mark[v] = 1;
                }    
            }
            res = max(res, tmp);
        }
    }
    cout << "Case #" << ncase << ": " << res << endl;
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
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
