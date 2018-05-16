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
const int inf = 0x3fffffff;
const string imp = "IMPOSSIBLE";
const ll long_inf = 1LL<<60;
int gcd(int a, int b) {return b ? gcd(b, a % b) : a; }

int sgn(int x) {return x == 0 ? 0 : (x > 0 ? 1 : -1);}

const int N = 1000010;
int cnt;
int x[N], y[N];

void calc(vector<int> d) {
    if (d.size() == 0) return;
    if (d.size() == 1) {
        // 1 ... d+1 clique
        for(int i = 1; i <= d.back() + 1; i++) {
            for(int j = i + 1; j <= d.back() + 1; j++) {
                x[cnt] = i;
                y[cnt] = j;
                cnt++;
            }
        }
        return;
    }
    vector<int> nd;
    for(int i = 1; i < d.size() - 1; i++) {
        nd.push_back(d[i] - d[0]);
    }
    int partA = nd.size() ? nd.back() + 1 : 1;
    // 1..partA
    // dk - dk-1 : partA + 1 ~ partA + partB
    // d[0]: partA + partB + 1 ~ partA + partB + partC
    int partB = d[d.size() - 1] - d[d.size() - 2];
    int partC = d[0];

    // edge inside partA
    calc(nd);

    // edge between partA and partC
    for(int i = 1; i <= partA; i++) {
        for(int j = 1; j <= partC; j++) {
            x[cnt] = i;
            y[cnt] = partA + partB + j;
            cnt++;
        }
    }

    // edge between partB and PartC
    for(int i = 1; i <= partB; i++) {
        for(int j = 1; j <= partC; j++) {
            x[cnt] = partA + i;
            y[cnt] = partA + partB + j;
            cnt++;
        }
    }

    // edge inside partC
    for(int i = 1; i <= partC; i++) {
        for(int j = i + 1; j <= partC; j++) {
            x[cnt] = partA + partB + i;
            y[cnt] = partA + partB + j;
            cnt++;
        }
    }
}

void solve(int ncase) {
    //cout << "Case #" << ncase << ": ";
    int n;
    cin >> n;
    vector<int> d(n);
    for(int i = 0; i < n; i++) {
        cin >> d[i];
    }
    calc(d);

    printf("%d\n", cnt);
    for(int i = 0; i < cnt; i++) {
        printf("%d %d\n", x[i], y[i]);
    }
}


int main() {
    ios::sync_with_stdio(false);
    //cout << std::fixed;
    //cout << setprecision(16);
#ifdef _zzz_
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    //precalc();
    int T = 1;
    //scanf("%d", &T);
    //cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
        //test();
    }
}

/*
    Give a degree set D, construct an undirected graph whose degree set is D with no self loop and multiple edges.

    Constructive method.

    Dunno how to come up with this, but let me repeat the algorithm mentioned in the editorial.

    Give a D (d1, d2, d3, ... dk), we can get it from a D' (d2 - d1, d3 - d1, .. , dk-1 - d1) <partA> by adding dk - dk-1 nodes<partB>
        that originally don't have any edges and d1 nodes<partC> connect to all the other nodes.
    So, |partA| + |partB| + |partC| = dk-1 - d1 + 1 + dk - dk-1 + d1 = dk + 1
    And D' becomes (d2, d3, ..., dk-1),
        partB becomes all nodes with degree d1
        partC becomes all nodes with degree dk

    let me try to understand the motivate here.
    We need to find the sub problem of the original one. The way to narrow down the degree set is to remove one or two elements.
    The particular elements we are considering is from the beginning and the end.
    Neither only removing head nor removing tail can easily solve this.(?)
    So, we try to remove them together. And making all the nodes from head with degree dk and all the nodes from the tail with degree d1.(why?)
    That means all the nodes from tail need to connect some part with d1 nodes, and all the nodes from the head need to connect all the other node.
    So, the first part is d1 nodes, the second part becomes (d2 - d1, d3 - d1, .. , dk-1 - d1) with dk-1 - d1 + 1 nodes and the last part is
        dk - dk-1 nodes.
    Hmmm, it's understandable but to come up with this some insight is needed.


    And how to ensure there are no more than 1e6 edges?
*/
