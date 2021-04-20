
// https://nanti.jisuanke.com/t/49111 攀登山峰
struct TreeNode {
  int l, r, sum;
};
struct PersistentSegmentTree {
  vector<TreeNode> v;
  vector<int> root;
  int cnt = 0;
  PersistentSegmentTree(int n) {
    v.assign(40 * n, TreeNode());
    root.assign(n + 1, 0);
  }
  void insert(int l, int r, int pre, int &now, int x) {
    now = ++cnt;
    v[now] = v[pre];
    v[now].sum++;
    if (l == r) return;
    int mid = (l + r) / 2;
    if (x <= mid) {
      insert(l, mid, v[pre].l, v[now].l, x);
    } else {
      insert(mid + 1, r, v[pre].r, v[now].r, x);
    }
  }
  int query(int l, int r, int pre, int now, int x) {
    //debug(l, r, v[v[now].l].sum, v[v[pre].l].sum, v[v[now].r].sum, v[v[pre].r].sum);
    if (l == r) {
      if (v[now].sum - v[pre].sum < x) return -1;
      return l;
    }
    int mid = (l + r) / 2;
    int sumR = v[v[now].r].sum - v[v[pre].r].sum;
    int ret = -1;
    if (sumR >= x) {
      ret = query(mid + 1, r, v[pre].r, v[now].r, x);
    }
    if (ret == -1) {
      ret = query(l, mid, v[pre].l, v[now].l, x);
    }
    return ret;
  }
};

void solve(int ncase) {
  int n = ri(), m = ri();
  const int R = 1e9;
  PersistentSegmentTree pst(n);
  for (int i = 0; i < n; i++) {
    int x = ri();
    pst.insert(1, R, pst.root[i], pst.root[i + 1], x);
  }
  while (m--) {
    int l = ri(), r = ri(), t = ri();
    int x = (r - l + 1) / t + 1;
    printf("%d\n", pst.query(1, R, pst.root[l - 1], pst.root[r], x));
  }
}
