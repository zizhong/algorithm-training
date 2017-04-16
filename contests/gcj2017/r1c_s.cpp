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

int hd, ad, hk, ak, b, d;

void debuff(int nd, int &curhd, int curak, int& ret, bool& healed) {
    if (ret == -1) return;
    if (curhd <= 0) {
        ret = -1;
        return;
    }
    if (nd == 0) return;
    // if debuff this turn,
    int next_damage = max(0, curak - d);
    if (next_damage >= curhd) {
        if (healed) {
            ret = -1;
            return;
        }
        // heal this turn
        ret++;
        curhd = hd - curak;
        healed = true;
        debuff(nd, curhd, curak, ret, healed);
        return;
    }
    ret++;
    healed = false;
    curhd -= next_damage;
    debuff(nd - 1, curhd, next_damage, ret, healed);
}

void buff(int nb, int &curhd, int curak, int& ret, bool& healed) {
    if (curhd <= 0) {
        ret = -1;
    }
    if (ret == -1) return;
    if (nb == 0) return;
    if (curhd <= curak) {
        // heal this turn
        if (healed) {
            ret = -1;
            return;
        }
        curhd = hd - curak;
        ret++;
        healed = true;
        buff(nb, curhd, curak, ret, healed);
        return;
    }
    // buff this turn
    ret++;
    curhd -= curak;
    healed = false;
    buff(nb - 1, curhd, curak, ret, healed);
}

void attack(int curhd, int curhk, int curak, int curad, int &ret, bool& healed) {
    if (curhd <= 0) ret = -1;
    if (ret == -1) return;
    if (curhk <= 0) return;
    if (curhk <= curad) {
        ret++;
        return;
    }
    if (curhd <= curak) {
        // heal this turn
        if (healed) {
            ret = -1;
            return;
        }
        curhd = hd - curak;
        ret++;
        healed = true;
        attack(curhd, curhk, curak, curad, ret, healed);
        return;
    }
    ret++;
    healed = false;
    attack(curhd - curak, curhk - curad, curak, curad, ret, healed);
}

void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    cin >> hd >> ad >> hk >> ak >> b >> d;
    int ans = -1;
    int maxnd = (d == 0 ? 0 : ((ak + d - 1) / d));
    int maxnb = (b == 0 ? 0 : ((hk - ad + b - 1) / b));
    for(int nd = 0; nd <= maxnd; nd++) {
        for(int nb = 0; nb <= maxnb; nb++) {
            int ret = 0;
            int curhd = hd;
            int curhk = hk;
            bool healed = true;
            debuff(nd, curhd, ak, ret, healed);
            buff(nb, curhd, max(0, ak - d * nd), ret, healed);
            attack(curhd, curhk, max(0, ak - d * nd), ad + b * nb, ret, healed);
            if (ret == -1) continue;
            if (ans == -1 || ans > ret) ans = ret;
        }
    }
    if (ans == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << ans << endl;
    }
}


int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    //cout << setprecision(16) << endl;
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
