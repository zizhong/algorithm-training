/**
* https://leetcode.com/explore/featured/card/june-leetcoding-challenge/542/week-4-june-22nd-june-28th/3374/
*/

struct Edge {
    int to;
    bool exist;
    Edge(int t) : to(t), exist(true) {}
    bool operator < (const Edge& rhs) const {
        return to < rhs.to;
    }
};
class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& e) {
        set<string> node;
        for(auto& v : e) {
            node.insert(v[0]);
            node.insert(v[1]);
        }
        map<string, int> s2idx;
        int nidx = 0;
        vector<string> vs;
        for(auto & s : node) s2idx[s] = nidx++, vs.push_back(s);
        
        graph.assign(node.size(), vector<Edge>());
        for(auto& v : e) {
            int from = s2idx[v[0]];
            int to = s2idx[v[1]];
            graph[from].push_back(Edge(to));
        }
        for(auto& v : graph) sort(v.begin(), v.end());
        vector<int> euler_path;
        dfs(s2idx["JFK"], euler_path);
        vector<string> ret;
        for(int i = euler_path.size() - 1; i >= 0; i--) {
            ret.push_back(vs[euler_path[i]]);
        }
        return ret;
    }
    vector<vector<Edge>> graph;
    void dfs(int u, vector<int>& euler_path) {
        for(auto& e : graph[u]) {
            if (!e.exist) continue;
            e.exist = false;
            dfs(e.to, euler_path);
        }
        euler_path.push_back(u);
    }
};


/**
*  Find Euler path on an undirected graph.
* https://codeforces.com/gym/304511/problem/F
*/
struct Edge {
  int to;
  bool exist;
  int rev_idx;
  Edge(int t, int rev_idx_) : to(t), rev_idx(rev_idx_), exist(true) {}
  bool operator<(const Edge &rhs) const {
    return to < rhs.to;
  }
};


vector<vector<Edge>> graph;

void dfs(int u, vector<int> &euler_path) {
  for (auto &e : graph[u]) {
    if (!e.exist) continue;
    e.exist = false;
    graph[e.to][e.rev_idx].exist = false;
    dfs(e.to, euler_path);
  }
  euler_path.push_back(u);
}
void solve(int ncase) {
  int m = ri();
  vector<PII> edge(m);
  int idx = 0;
  unordered_map<int, int> x2idx;
  unordered_map<int, int> idx2x;
  for (int i = 0; i < m; i++) {
    edge[i].first = ri();
    edge[i].second = ri();
    if (x2idx.find(edge[i].first) == x2idx.end()) {
      idx2x[idx] = edge[i].first;
      x2idx[edge[i].first] = idx++;
    }
    if (x2idx.find(edge[i].second) == x2idx.end()) {
      idx2x[idx] = edge[i].second;
      x2idx[edge[i].second] = idx++;
    }
  }
  graph.assign(idx, vector<Edge>());
  vector<int> degree(idx);
  for (int i = 0; i < m; i++) {
    int u = x2idx[edge[i].first];
    int v = x2idx[edge[i].second];
    degree[u]++;
    degree[v]++;
    graph[u].push_back(Edge(v, graph[v].size()));
    graph[v].push_back(Edge(u, (int) graph[u].size() - 1));
  }
  int start = -1;
  for (int i = 0; i < idx; i++) {
    if (degree[i] & 1) {
      start = i;
      break;
    }
  }
  if (start < -1) start = 0;
  vector<int> euler_path;
  dfs(start, euler_path);
  if (euler_path.size() != m + 1) {
    cout << -1 << endl;
    return;
  }
  cout << euler_path.size() << endl;
  for (auto i : euler_path) cout << idx2x[i] << " ";
  cout << endl;
}
