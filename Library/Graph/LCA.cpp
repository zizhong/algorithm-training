/**
* LCA implemented with double incremental.
* https://codeforces.com/contest/1380/submission/87211594
*/

const int N = 200043;
const int L = 20;
 
vector<int> g[2 * N];
int p[2 * N];
int up[2 * N][L];
int idx[N];
int psum[N];
int cur[N];
int tin[2 * N];
int tout[2 * N];
int T = 0;
 
void dfs(int x, int y) {
  tin[x] = T++;
  p[x] = y;
  up[x][0] = y;
  for (int i = 1; i < L; i++)
    up[x][i] = up[up[x][i - 1]][i - 1];
  for (auto z : g[x])
    dfs(z, x);
  tout[x] = T++;
}
 
bool is_ancestor(int x, int y) {
  return tin[x] <= tin[y] && tout[x] >= tout[y];
}
 
int lca(int x, int y) {
  if (is_ancestor(x, y))
    return x;
  for (int i = L - 1; i >= 0; i--)
    if (!is_ancestor(up[x][i], y))
      x = up[x][i];
  return p[x];
}
