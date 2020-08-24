struct Disjoint {
  Disjoint(int n) {
    p.assign(n + 1, -1);
  }
  vector<int> p;
  void join(int a, int b) {
    int ra = root(a);
    int rb = root(b);
    if (ra == rb) return;
    int sum = p[ra] + p[rb];
    if (p[ra] < p[rb]) {
      p[rb] = ra;
      p[ra] = sum;
    } else {
      p[ra] = rb;
      p[rb] = sum;
    }
  }
  int root(int x) {
    return p[x] < 0 ? x : (p[x] = root(p[x]));
  }
};
