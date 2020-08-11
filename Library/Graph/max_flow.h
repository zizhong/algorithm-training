#include "bits/stdc++.h"
using namespace std;
struct edge {int to, cap, rev;};

const int INF = 0x3fffffff;
const int MAXV = 50000 * 2 + 10;
vector<edge> G[MAXV];
int level[MAXV];
int iter[MAXV];

void add_edge(int from, int to, int cap) {
    //cout << from << "->" << to << ": " << cap << endl;
    G[from].push_back(edge{to, cap, (int)G[to].size()});
    G[to].push_back(edge{from, 0, (int)G[from].size() - 1});
}

void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while(que.size()) {
        int v = que.front();
        que.pop();
        for(auto &e: G[v]) {
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}

int dfs(int v, int t, int f) {
    if (v == t) return f;
    for(int &i = iter[v]; i < G[v].size(); i++) {
        edge &e = G[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    for(;;) {
        bfs(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        int f;
        while((f = dfs(s, t, INF)) > 0) flow += f;
    }
}

void init() {
    for(auto &v : G) v.clear();      
    memset(level, 0, sizeof(level));
}
