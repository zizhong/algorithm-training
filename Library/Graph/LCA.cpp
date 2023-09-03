const int N = 10010;
const int L = 15;

vector<vector<vector<int>>> g;
int p[N];
int up[N][L];
int w[N][L][26];

int tin[N];
int tout[N];
int T = 0;
int n;

void dfs(int x, int y, int z) {

  tin[x] = T++;
  p[x] = y;
  up[x][0] = y;
  if (z >= 0) {
    w[x][0][z]++;
  }
  for (auto &e: g[x]) {
    int v = e[0];
    if (v == y) continue;
    int l = e[1];
    dfs(v, x, l);

  }
  tout[x] = T++;
}

bool is_ancestor(int x, int y) {
  return tin[x] <= tin[y] && tout[x] >= tout[y];
}

int lca(int x, int y) {

  if (is_ancestor(x, y))
    return x;
  for (int i = L - 1; i >= 0; i--)
    if (up[x][i] != 0 && !is_ancestor(up[x][i], y))
      x = up[x][i];
  return p[x];
}

void init() {
    T = 0;
    memset(tin, 0, sizeof(tin));
    memset(tout, 0, size(tout));
    memset(p, 0, size(p));
    memset(w, 0, sizeof(w));
    memset(up, 0, sizeof(up));
}

class Solution {
 public:
  vector<int> minOperationsQueries(int nn, vector<vector<int>> &edges, vector<vector<int>> &queries) {
    init();
    n = nn;
    g = vector<vector<vector<int>>>(n + 1);

    for (auto &e: edges) {
      int u = e[0];
      int v = e[1];
      int x = e[2];
      u++;
      v++;
      x--;

      g[u].push_back({v, x});
      g[v].push_back({u, x});
    }
    dfs(1, 0, -1);

    for (int i = 1; i < L; i++) {
      for (int x = 1; x <= n; x++) {
        up[x][i] = up[up[x][i - 1]][i - 1];

        for (int k = 0; k < 26; k++) {
          w[x][i][k] = w[x][i - 1][k] + w[up[x][i - 1]][i - 1][k];
        }

      }
    }
    vector<int> ret;
    for (auto &q: queries) {
      q[0]++;
      q[1]++;
      int c = lca(q[0], q[1]);
      int tmpw[26] = {0};

      for (int i = 0; i < 26; i++) {
        tmpw[i] = w[q[0]][L - 1][i] + w[q[1]][L - 1][i] - 2 * w[c][L - 1][i];

      }

      sort(tmpw, tmpw + 26);
      ret.push_back(accumulate(tmpw, tmpw + 26, 0) - tmpw[25]);
    }
    return ret;
  }
};
