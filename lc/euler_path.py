# https://leetcode.com/problems/valid-arrangement-of-pairs/
class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        in_degree = defaultdict(int)
        out_degree = defaultdict(int)
        g = defaultdict(list)
        for start, end in pairs:
            out_degree[start] += 1
            in_degree[end] += 1
            g[start].append(end)
        start = -1
        for k in out_degree:
            if in_degree[k] + 1 == out_degree[k]:
                start = k
                break
        if start == -1:
            start = pairs[0][0]
        euler_path = list()
        self.dfs_euler(start, g, euler_path)
        ret = list()
        for i, v in enumerate(euler_path):
            if i == 0:
                continue
            ret.append([v, euler_path[i-1]])
        ret.reverse()
        return ret
    
    def dfs_euler(self, u: int, g: Dict[int, List], euler_path: List[int]):
        while len(g[u]) > 0:
            self.dfs_euler(g[u].pop(), g, euler_path)
        euler_path.append(u)
        
        
