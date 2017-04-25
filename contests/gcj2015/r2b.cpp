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
typedef pair<double, double> PDD;
typedef pair<ll, PII> PLP;
#define CLS(x, v) (memset((x), (v), sizeof((x))))

const int N = 128;
const double eps = 1e-8;

int n;
double V, X;
double calc_temp(const vector<PDD>& source, const vector<double>& rate) {
    double vx = 0;
    double v = 0;
    for(int i = 0; i < n; i++) {
        v += rate[i] * source[i].second;
        vx += rate[i] * source[i].first * source[i].second;
    }
    return vx / v;
}

double calc_time(const vector<PDD>& source, const vector<double>& rate) {
    double v = 0;
    for(int i = 0; i < n; i++) {
        v += rate[i] * source[i].second;
    }
    return V / v;
}

void calc_rate(const vector<PDD>& source, vector<double>& rate, int idx) {
    double vx = 0;
    for(int i = 0; i < n; i++) {
        if (i == idx) continue;
        vx += rate[i] * source[i].second * (X - source[i].first);
    }
    rate[idx] = vx / ((source[idx].first - X) * source[idx].second); 
    //cout << "rate[" << idx << "] = " << rate[idx] << endl; 
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    cin >> n >> V >> X;
    vector<PDD> source(n);
    for(int i = 0; i < n; i++) {
        cin >> source[i].second >> source[i].first;
    }
    sort(source.begin(), source.end());
    vector<double> rate(n, 1);
    int first = 0, last = n - 1;
    while(true) {
        //cout << first << " " << last << endl;
        if (first > last) {
            cout << "IMPOSSIBLE" << endl;
            return;
        }
        double temp = calc_temp(source, rate);
        if (fabs(temp - X) < eps) {
            cout << calc_time(source, rate) << endl;
            return;
        }
        if (first == last) {
            first++;
            continue;
        }
        if (X < temp) {
            rate[last] = 0;
            if (X < calc_temp(source, rate)) {
                last--;
                continue;
            }
            calc_rate(source, rate, last);
            continue;
        }
        rate[first] = 0;
        if (X > calc_temp(source, rate)) {
            first++;
            continue;
        }
        calc_rate(source, rate, first);
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
