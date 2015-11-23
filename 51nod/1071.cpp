/*
desc:
    Nim game : given N heaps. each one has @num stones
    for which each player can pick at most @cap stones.
solu:
    Nim add + SG function
*/
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
void precalc() {
}

void solve(int ncase) {
    int n;
    scanf("%d", &n);
    int ans = 0;
    for(int i = 0; i < n; i ++) {
        int num, cap;
        scanf("%d%d", &num, &cap);
        int tmp = 0;
        if (num <= cap) tmp = num;
        else tmp = num % (cap + 1);
        ans ^= tmp;
    }
    printf("%s\n", ans ? "A" : "B");
}
int main() {
    //ios::sync_with_stdio(false);
    //cout << std::fixed << setprecision(16);
    //init();
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
