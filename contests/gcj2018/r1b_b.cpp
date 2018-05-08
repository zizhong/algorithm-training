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
const int inf = 0x3fffffff;
const string imp = "IMPOSSIBLE";

PII calcP(int d, int a, int b) {
    return {d - b, d + a};
}

void pushTo(PII& p, auto& num2hash, auto& num2cnt, vector<set<int>>& node, auto& degree) {
    degree[p.first]++;
    if (num2hash.find(p.first) == num2hash.end()) {
        num2hash[p.first] = unordered_map<int, int>();
    }
    num2hash[p.first][p.second]++;
    if (num2hash[p.first][p.second] == 1) {
        num2cnt[p.first]++;
        if (num2cnt[p.first] == 1) {
            node[0].insert(p.first);
        }
        if (num2cnt[p.first] == 2) {
            node[1].insert(p.first);
            node[0].erase(p.first);
        }
    }
}

void popFrom(PII& p, auto& num2hash, auto& num2cnt, vector<set<int>>& node, auto& degree) {
    degree[p.first]--;
    num2hash[p.first][p.second]--;
    if (num2hash[p.first][p.second] == 0) {
        num2cnt[p.first]--;
        if (num2cnt[p.first] == 1) {
            node[0].insert(p.first);
            node[1].erase(p.first);
        }
        if (num2cnt[p.first] == 0) {
            node[0].erase(p.first);
        }
    }
}

bool okay(int ne, auto& left2hash, auto& left_node, auto& left2degree,
        auto& right2hash, auto& right_node, auto& right2degree) {
    if (left_node[1].size() > 1 || right_node[1].size() > 1 ) {
        return false;
    }
    int left_candidate = left_node[1].size() == 1 ? *left_node[1].begin() : inf;
    int right_candidate = right_node[1].size() == 1 ? *right_node[1].begin() : inf;
    if (left_node[1].size() == 1 && right_node[1].size() == 1) {
        return ne == left2degree[left_candidate] + right2degree[right_candidate] - left2hash[left_candidate][right_candidate];
    }
    if (left_node[1].size() == 1 && right_node[1].size() == 0) {
        if(left_node[0].size() == 0) return true;
        return ne == left2degree[left_candidate] + left2degree[*left_node[0].begin()];
    }
    if (left_node[1].size() == 0 && right_node[1].size() == 1) {
        if(right_node[0].size() == 0) return true;
        //printf("right2degree[%d] = %d, right2degree[%d] = %d, ne = %d\n", right_candidate, right2degree[right_candidate], *right_node[0].begin(),right2degree[*right_node[0].begin()], ne );
        return ne == right2degree[right_candidate] + right2degree[*right_node[0].begin()];
    }
    //printf("left_node[0].size() = %d, right_node[0].size() = %d\n", left_node[0].size(), right_node[0].size());
    return left_node[0].size() < 3 && right_node[0].size() < 3;
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    int n;
    cin >> n;
    vector<int> D(n), A(n), B(n);
    for(int i = 0; i < n; i++) {
        cin >> D[i] >> A[i] >> B[i];
    }
    int maxLength = 0, cnt = 0;
    int p = 0, q = 0;
    // all the data
    unordered_map<int, unordered_map<int, int>> left2hash;
    // number to the count of numbers depend on it
    unordered_map<int, int> left2cnt;
    unordered_map<int, int> left2degree;
    vector<set<int>> left_node(2);

    unordered_map<int, unordered_map<int, int>> right2hash;
    unordered_map<int, int> right2cnt;
    unordered_map<int, int> right2degree;
    vector<set<int>> right_node(2);

    while(q < n) {
        // try [q]
        // check [p, q]
        //printf("(%d, %d)\n", p, q);
        PII p_q = calcP(D[q], A[q], B[q]);
        // insert <a, b>
        pushTo(p_q, left2hash, left2cnt, left_node, left2degree);
        swap(p_q.first, p_q.second);
        pushTo(p_q, right2hash, right2cnt, right_node, right2degree);
        while(!okay(q - p + 1, left2hash, left_node, left2degree,
                    right2hash, right_node, right2degree)) {
            PII p_p = calcP(D[p], A[p], B[p]);
            popFrom(p_p, left2hash, left2cnt, left_node, left2degree);
            swap(p_p.first, p_p.second);
            popFrom(p_p, right2hash, right2cnt, right_node, right2degree);
            p++;
        }
        q++;
        if (q - p > maxLength) maxLength = q - p, cnt = 1;
        else if (q - p == maxLength) cnt++;//, printf("(%d, %d) cnt[%d]\n", p, q, cnt);

    }
    cout << maxLength << " " << cnt << endl;
}

int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    cout << setprecision(16);
#ifdef _zzz_
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    //precalc();
    int T = 1;
    //scanf("%d", &T);
    cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}

/**
 * Wrote this code spent me a lot of time. The algorithm structure is obvious sliding window.
 * But it's not so easy for me that how to maintain good enough data structures to support quickly
 * querying the window is a valid bipartite that max edge cover <= 2.
 *
 * My first lesson is code written before you have a clear analysis 99% can go wrong. So, it's
 * important to identify the true nature of the question and analyze it systematically.
 *
 * Back to question itself. The question is very interesting, too.
 * Summary:
 * There is a sequence of road sign in a line located at D_i from west to east, with A_i on west
 * side and B_i on east side. Find the longest ranges hold the following:
 *   N and M exist for each sign in the range that at least one of
 *     . D_i + A_i == N
 *     . D_i - B_i == M
 *   is true.
 *
 * Analysis:
 * For each sign (D, A, B), we can get a pair of boolean expressions(X as N == D + A, Y as M == D - B).
 * So, !X => Y and !Y => X.
 * If we have (x1, y1) and (x2, y1) where x1 != x2, we know !y1 => x1 and !y1 => x2. Then !y1 is False.
 * So, y1 is true.                                                                              --- *1
 * For any y1 and y2 where y1 != y2, they can not be true at the same time.                     --- *2
 * We can make a logical graph (two nodes are connected iff they can hold true at the same time), where
 * an edge (u, v) means !u => v, and apparently the graph is a bipartite.
 *
 * (*1) means if a node connects more than one neighbors, the expression is true.
 * (*2) means each side can have at most 1 node with more than one neighbors.
 * Let's call a node a candidate iff it connects more than one neighbors.
 *
 * Let's discuss on whether or not a candidate exists. There're three cases:
 *   1. left side has a candidate c_left and right side has a candidate c_right, then the graph needs
 *              deg(c_left) + deg(c_right) - |E(c_left, c_right)| = |E|.
 *   2. left side has a candidate c_left but right side has only node with one neighbor, then the graph needs
 *             deg(c_left) == |E|
 *          or  deg(c_left) + deg(another_node_on_left_with_one_neighbor) == |E|.
 *      The case that right side has a candidate but left side not is similar.
 *   3. two sides have only nodes with one neighbor, then the graph needs
 *              |node_left| < 3 and |node_right| < 3.
 *
 * The sliding window should have the information to determine
 *      the candidates of each side in the graph,
 *      the non-candidates of each side,
 *      the degree of each node, and
 *      the number of edges for a specific pair of nodes.
*/
