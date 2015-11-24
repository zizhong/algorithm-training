/*
desc:
    given a sequence with n different numbers,
    sort it by only swaping two numbers.
    the cost of a swap is the sum of two numbers swapped.
    calculate minimum cost to sort the given seqeuence.
solu:
    Permumtation + Construction
    a permumtation consists of many swaps.
    how to minimize the cost?
    in a cycle, we can easily swap all the other elements with the minimum one in this cycle.
    it's same to treating the min one as an empty slot.
    Or we can use the global Min as an empty slot.
    btw, it's a classic problem. I saw it on USACO at first time but only recalled it after 
    I came out the logic.
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

const int N = 50010;
int d[N];
PII p[N];
int pos[N];
int n;
void precalc() {
}

int mask[N];
void dfs(int x, ll& sum, int& len) {
    if (mask[x]) return;
    mask[x] = 1;
    sum += p[x].first;
    len ++;
    dfs(p[x].second, sum, len);
}
void solve(int ncase) {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) {
        scanf("%d", &d[i]);
        p[i] = PII(d[i], i);
    }
    sort(p, p + n);
    for(int i = 0; i < n; i ++) {
        pos[p[i].second] = i;
    }
    ll ans = 0;
    for(int i = 0; i < n; i ++) {
        if (mask[i]) continue;
        ll sum = 0;
        int len = 0;
        dfs(i, sum, len);
        ll tmp = min(p[0].first * 1LL * (len + 1) + sum + p[i].first,
                    sum - p[i].first +  p[i].first * 1LL * (len - 1));
        ans += tmp;
    }
    printf("%lld\n", ans);
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
