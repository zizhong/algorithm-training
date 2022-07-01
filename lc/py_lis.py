# https://leetcode.com/problems/minimum-operations-to-make-the-array-k-increasing
class Solution:
    def kIncreasing(self, arr: List[int], k: int) -> int:
        n = len(arr)
        ret = 0
        for i in range(0, k):
            l = list()
            for j in range(i, n, k):
                l.append(arr[j])
            ret += len(l) - self.longestIncreasing(l)
        return ret

    def longestIncreasing(self, l: List[int]) -> int:
        n = len(l)
        INF = 1000000000
        f = [INF] * n
        for x in l:
            f[bisect.bisect_right(f, x)] = x
        return bisect.bisect_left(f, INF)
