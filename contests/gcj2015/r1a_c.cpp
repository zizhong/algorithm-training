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
#include "utils/haha.h"
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;
#define CLS(x, v) (memset((x), (v), sizeof((x))))

const int N = 3010;
int n;
vector<point> v;
point po;


// 
double cross(const point& a, const point& b) {
    return a.x * b.y - a.y * b.x;
}

bool cmp_angle(const point& pa, const point& pb) {
    point p1 = pa - po;
    point p2 = pb - po;
    if (p1.y == 0 && p2.y == 0 && p1.x * p2.x <= 0) return p1.x > p2.x;
    if (p1.y == 0 && p1.x >= 0 && p2.y != 0) return true;
    if (p2.y == 0 && p2.x >= 0 && p1.y != 0) return false;
    if (p1.y * p2.y < 0) return p1.y > p2.y;
    float c = cross(p1, p2);
    return c > 0 || c == 0 && abs(p1.x) < abs(p2.x);
}

int left_start, left_end, right_start, right_end;

void update_ans(vector<int>& ans, int idx) {
    int L = left_end == -1 ? 0 : (left_end >= left_start ?  left_end + 1 - left_start : left_end + n - left_start);
    int R = right_end == -1 ? 0 : (right_end >= right_start ?  right_end + 1 - right_start : right_end + n - right_start);
    //fprintf(stderr, "L [%d], R [%d]\n", L, R);
    ans[idx] = min(ans[idx], min(L, R));
}

void solve(int ncase) {
    cout << "Case #" << ncase << ":\n";
    cin >> n;
    v.clear();
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v.push_back(point(x, y));
    }
    if (n < 4) {
        for(int i = 0; i < n; i++) {
            cout << 0 << endl;
        }
        return;
    }
    vector<int> ans(n, n);
    for(int k = 0; k < n; k++) {
        po = v[k];
        vector<point> pv;
        for(int j = 0; j < n; j++) {
            if (k == j) continue;
            pv.push_back(v[j]);
        }
        int nn = n - 1;
        sort(pv.begin(), pv.end(), cmp_angle);
        //fprintf(stderr, "po[%lld, %lld]\n", po.x, po.y);
        //for(int i = 0; i < nn; i++) {
            //fprintf(stderr, "pv[%lld, %lld]\n", pv[i].x, pv[i].y);
        //}
        left_start = -1, left_end = -1;
        right_start = -1, right_end = -1;
        pVector line(po, pv[0]);
        for(int i = 1; i < nn; i++) {
            //fprintf(stderr, "line * pv[%d] = [%lld]\n", i, line * pv[i]);
            //if (line.lhas(pv[i])) continue;
            if (pv[i] < line) {
                if (left_start == -1) {
                    left_start = i;
                }
                left_end = i;
            } else if (pv[i] > line) {
                if (right_start == -1) {
                    right_start = i;
                }
                right_end = i;
            }
        }
        //fprintf(stderr, "pVector[%d] left_start [%d], left_end [%d], right_start [%d], right_end [%d]\n", 0, left_start, left_end, right_start, right_end);
        update_ans(ans, k);
        if (left_end == -1 || right_end == -1) continue;
        for(int i = 1; i < nn; i++) {
            line = pVector(po, pv[i]);
            //for(int j = 0; j < nn; j++) fprintf(stderr, "line * pv[%d] = [%lld]\n", j, line * pv[j]);
            for(int nx = (left_end + 1) % nn; pv[nx] < line; nx = (nx + 1) % nn) left_end = nx;
            for(; left_start != left_end && !(pv[left_start] < line); left_start = (left_start + 1) % nn);
            if (!(pv[left_start] < line)) left_end = -1;
            for(int nx = (right_end + 1) % nn; pv[nx] > line; nx = (nx + 1) % nn) right_end = nx;
            for(; right_start != right_end && !(pv[right_start] > line); right_start = (right_start + 1) % nn);
            if (!(pv[right_start] > line)) right_end = -1;
            //fprintf(stderr, "pVector[%d] left_start [%d], left_end [%d], right_start [%d], right_end [%d]\n", i, left_start, left_end, right_start, right_end);
            update_ans(ans, k);
            if (left_end == -1 || right_end == -1) break;
        }
    }
    for(int i = 0; i < n; i++) {
        cout << ans [i] << endl;
    }
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
