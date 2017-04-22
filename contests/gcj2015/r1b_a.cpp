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
#define CLS(x, v) (memset((x), (v), sizeof((x))))

int dfs(const string& str) {
    if (str.size() == 1) {
        int x = stoi(str);
        return x;
    }
    ll n = stoll(str);
    int ans = 0;
    // left_part[middle]right_part
    int right_part = 0, left_part = 0, middle_part = 0;

    for(int i = str.size() / 2 - 1; i >= 0; i--) left_part = left_part * 10 + str[i] - '0';
    for(int i = (str.size() + 1) / 2; i < str.size(); i++) right_part = right_part * 10 + str[i] - '0';
    
    if (str.size() % 2) {
        middle_part = str[str.size() / 2] - '0';
        for(int i = str.size() / 2 + 1; i < str.size(); i++) middle_part *= 10;
    }
    //cout << str << " left_v = " << left_part << ",  right = " << right_part << " " << middle_part << endl;
    if (right_part == 0) {
        return ans + 1 + dfs(to_string(n - 1));
    }
    ans += 1 + dfs(string(str.size() - 1, '9'));
    if (left_part > 1) {
        // 10000 -> 100right_part
        ans += left_part;
        // swap -> right_part + 0001
        ans ++;
        ans += right_part - 1;
        return ans + middle_part;
    }
    return ans + right_part + middle_part;
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    string str;
    cin >> str;
    ll n = stoll(str);
    cout << dfs(str) << endl;
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
