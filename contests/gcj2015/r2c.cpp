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
#include "utils/max_flow.h"
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;
typedef pair<double, double> PDD;
typedef pair<ll, PII> PLP;
#define CLS(x, v) (memset((x), (v), sizeof((x))))

int n;
void solve(int ncase) {
    cout << "Case #" << ncase << ": ";
    init();
    cin >> n;
    vector<string> str(n);
    getline(cin, str[0]);
    for(int i = 0; i < n; i++) {
        getline(cin, str[i]);
    }

    // 0~n-1 sentence, 
    // idx->word_in, idx+1->word_out
    int idx = 0;
    unordered_map<string, int> word2idx;
    int offset = n;
    for(int i = 0; i < n; i++) {
        istringstream iss(str[i]);
        string word;
        while(iss >> word) {
            if (word2idx.find(word) == word2idx.end()) {
                word2idx[word] = idx;
                add_edge(offset + idx, offset + idx + 1, 1);
                idx += 2;
            }
            int widx = word2idx[word];
            add_edge(i, offset + widx, INF);
            add_edge(offset + widx + 1, i, INF);
        }
    }
    cout << max_flow(0, 1) << endl;
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
    //scanf("%d", &T);
    cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
