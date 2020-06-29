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
