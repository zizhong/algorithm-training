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
#include <list>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> PII;
typedef pair<int, double> PID;
typedef pair<string, int> PSI;
typedef pair<string, string> PSS;
typedef pair<PII, int> PIP;
void precalc(){};

const int N = 512;
int matrix[N][N];
int calc(vector<int>& h) {
    int n = h.size();
    vector<int> left(n, 0), right(n, n - 1);
    stack<int> st;
    for(int i = 0; i < n; i ++) {
        while(!st.empty() && h[st.top()] >= h[i]) st.pop();
        if (!st.empty()) left[i] = st.top() + 1;
        st.push(i);
    }
    while(!st.empty()) st.pop();
    for(int i = n - 1; i >= 0; i --) {
        while(!st.empty() && h[st.top()] >= h[i]) st.pop();
        if (!st.empty()) right[i] = st.top() - 1;
        st.push(i);
    }
    int ret = 0;
    for(int i = 0; i < n; i ++) {
        ret = max(h[i], ret);
        ret = max(ret, h[i] * (right[i] - left[i] + 1));
    }
    return ret;
}
void solve(int ncase) {
    int m, n;
    cin >> m >> n;
    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= m; j ++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    vector<int> height(m + 1 , 0);
    int ans = 0;
    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= m; j ++) {
            height[j] = matrix[i][j] ? 1 + height[j] : 0;
        }
        ans = max(ans, calc(height));
    }
    cout << ans << endl;
}
int main() {
    //ios::sync_with_stdio(false);
    //cout << std::fixed << setprecision(16);
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
    //freopen("A-small-practice.in", "r", stdin);
    //freopen("A-large-practice.in", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    int T = 1;
    precalc();
    //cin >> T;
    //scanf("%d", &T);
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
