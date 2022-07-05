# https://leetcode.com/problems/sequentially-ordinal-rank-tracker/
class MaxHeapObj(object):
  def __init__(self, val): self.val = val
  def __lt__(self, other): return self.val > other.val
  def __eq__(self, other): return self.val == other.val
  def __str__(self): return str(self.val)

class SORTracker:
    
    def __init__(self):
        self.minq = list()
        self.maxq = list()
        self.k = 0
        

    def add(self, name: str, score: int) -> None:
        item = (-score, name)
        if len(self.minq) == 0 or item > self.minq[0]:
            heapq.heappush(self.minq, item)
        else:
            heapq.heappush(self.maxq, MaxHeapObj(item))

    def get(self) -> str:
        while len(self.maxq) > self.k:
            heapq.heappush(self.minq, heapq.heappop(self.maxq).val)
        while len(self.maxq) < self.k:
            heapq.heappush(self.maxq, MaxHeapObj(heapq.heappop(self.minq)))
        self.k += 1
        return self.minq[0][1]


# Your SORTracker object will be instantiated and called as such:
# obj = SORTracker()
# obj.add(name,score)
# param_2 = obj.get()
