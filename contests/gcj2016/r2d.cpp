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

int n;
vector<string> op;
vector<int> mark;
int flag;
vector<int> pbit;
vector<int> bit;
void dfs(int x) {
    mark[x] = flag;
    for(int i = 0; i < n; i++) {
        if (op[x][i] == '1') {
            bit[bit.size() - 1] |= (1<<i);
        }
    }
    pbit[pbit.size() - 1] |= (1 << x);
    for(int i = 0; i < n; i++) {
        if (mark[i]) continue;
        for(int j = 0; j < n; j++) {
            if (op[i][j] == '1' && op[x][j] == '1') dfs(i);
        }
    }
}


int mins;
int partused[64];

int nextidx;

void dfspart(int idx, vector<PII>& part, int empty_row, int empty_col, int tmp);
void makesquare(int idx, int r, int c, vector<PII>& part, int empty_row, int empty_col, int tmp) {
    //printf("makesquare idx=[%d], empty_row = [%d], empty_col = [%d], tmp = [%d], r = [%d], c = [%d]\n", 
    //        idx, empty_row, empty_col, tmp, r, c);
    if (tmp + r * c >= mins) return;
    if (r == c) {
        tmp += r * c;
        dfspart(nextidx, part, empty_row, empty_col, tmp);
        return;
    }
    if (idx == part.size()) {
        int diff = r - c;
        int nrow = empty_row;
        int ncol = empty_col;
        int nr, nc;
        nr = nc = max(r, c);
        if (diff > 0) ncol -= diff;
        else nrow += diff;
        if (ncol < 0 || nrow < 0) return; 
        makesquare(idx, nr, nc, part, nrow, ncol, tmp);
        return;
    }
    if (partused[idx]) {
        makesquare(idx + 1, r, c, part, empty_row, empty_col, tmp);
    } else {
        makesquare(idx + 1, r, c, part, empty_row, empty_col, tmp);
        partused[idx] = 1;
        makesquare(idx + 1, r + part[idx].first, c + part[idx].second, part, empty_row, empty_col, tmp);
        partused[idx] = 0;
    }
}

void dfspart(int idx, vector<PII>& part, int empty_row, int empty_col, int tmp) {
    //printf("dfspart idx=[%d], empty_row = [%d], empty_col = [%d], tmp = [%d]\n", idx, empty_row, empty_col, tmp);
    if (idx == part.size()) {
        mins = min(mins, tmp + max(empty_row, empty_col));
        return;
    }
    if (tmp >= mins) return;
    if (partused[idx]) {
        dfspart(idx + 1, part, empty_row, empty_col, tmp);
        return;
    }
    int r = part[idx].first;
    int c = part[idx].second;
    int prenextidx = nextidx;
    nextidx = idx + 1;
    partused[idx] = 1;
    makesquare(idx + 1, r, c, part, empty_row, empty_col, tmp);
    partused[idx] = 0;
    nextidx = prenextidx;
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    cin >> n;
    op.assign(n, string());
    int ones = 0;
    for(int i = 0; i < n; i++) {
        cin >> op[i];
        for(auto c : op[i]) ones += c == '1';
    }
    flag = 0;
    mark.assign(n, 0);
    pbit.clear();
    bit.clear();
    for(int i = 0; i < n; i++) {
        int hasone = 0;
        for(int j = 0; j < n; j++) if (op[i][j]=='1') hasone = 1;
        if (!hasone) continue;
        if (mark[i]) continue;
        pbit.push_back(0);
        bit.push_back(0);
        flag++;
        dfs(i);
    }
    vector<PII> part;
    int empty_row = n;
    int empty_col = n;
    int base = 0;
    for(int i = 0; i < pbit.size(); i++) {
        int nrow = __builtin_popcount(pbit[i]);
        int ncol = __builtin_popcount(bit[i]);
        empty_row -= nrow;
        empty_col -= ncol;
        if (nrow == ncol) {
            base += nrow * nrow;
        } else {
            part.push_back(PII(nrow, ncol));
           // printf("part [%d, %d]\n", nrow, ncol);
        }
    }
    mins = 26 * 26;
    fill(partused, partused + 52, 0);
    dfspart(0, part, empty_row, empty_col, 0);
    cout << mins - ones + base << endl;
}


int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    cout << setprecision(16);
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
