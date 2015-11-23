/*
desc:
    Given N (<=10000) different integers,
    calculate length of the longest arithmetic seqeuence.
solu:
    DP + hashmap
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

int n;
const int N = 10010;
short f[N][N];
int a[N];
const int M = 23711;
int ht[M];
void solve(int ncase) {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + 1 + n);
    for(int i = 1; i <= n; i ++) {
        int k = a[i] % M;
        while(ht[k]) {
            k ++;
            if (k == M) {
                k = 0;
            }
        }
        ht[k] = i;
    }
    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= n; j ++) {
            f[i][j] = (i != j) + 1;
        }
    }
    for(int i = 2; i <= n; i ++) {
        for(int j = 1; j < i; j ++) {
            int nexta = a[i] + (a[i] - a[j]);
            int k = nexta % M;
            int pos = 0;
            while(ht[k]) {
                if (a[ht[k]] == nexta) {
                    pos = ht[k];
                    break;
                }
                k ++;
                if (k == M) k = 0;
            }
            if (pos) {
                f[pos][i] = max(f[pos][i] + 0, f[i][j] + 1);
            }
        }
    }

    short ans = 0;
    for(int i = 2; i <= n; i ++) {
        for(int j = 1; j < i; j ++) {
            ans = max(ans, f[i][j]);
        }  
    }
    printf("%d\n", ans);
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
