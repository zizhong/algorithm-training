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
#define CLS(x, v) (memset((x), (v), sizeof((x))))

int b, n;
int mk[1024];

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    cin >> b >> n;
    for(int i = 0; i < b; i++) {
        cin >> mk[i];
    }
    int t = 100000;
    vector<int> left(b);
    int cut = 0;
    while(true) {
        vector<int> tmp = left;
        int cancut = 0;
        for(int i = 0; i < b; i++) {
            int work = t - left[i];
            cancut += (work + mk[i] - 1) / mk[i];
            left[i] = work % mk[i] ? mk[i] - work % mk[i] : 0;
        }
        if (cut + cancut >= n) {
            priority_queue<PII, vector<PII>, greater<PII>> pq;
            for(int i = 0; i < b; i++) {
                pq.push(PII(tmp[i], i));
            }
            while(true) {
                PII h = pq.top();
                //cout<< cut << " " << h.first << " " << h.second << endl;
                pq.pop();
                cut++;
                if (cut == n) {
                    cout << h.second + 1 << endl;
                    return;
                }
                pq.push(PII(mk[h.second] + h.first, h.second));
            }
        }
        cut += cancut;
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
