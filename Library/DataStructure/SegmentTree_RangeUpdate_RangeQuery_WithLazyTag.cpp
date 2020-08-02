// https://codeforces.com/contest/1389/submission/88706312

struct SegTree {
  vector<int> v;
  vector<int> lazy;
  SegTree(int n) {
    v.assign(n * 4 + 10, 0);
    lazy.assign(n * 4 + 10, 0);
  }
  inline int lc(int idx) { return 2 * idx; }
  inline int rc(int idx) { return 2 * idx + 1; }
  void update_max(int idx, int l, int r, int x, int nv) {
    if (r < x || x < l) return;
    if (l == r) {
      v[idx] = max(v[idx], nv);
      return;
    }
    push_down(idx);
    int m = (l + r) / 2;
    update_max(lc(idx), l, m, x, nv);
    update_max(rc(idx), m + 1, r, x, nv);
    push_up(idx);
  }
  void update(int idx, int l, int r, int L, int R, int delta) {
    if (R < l || r < L || R < L) return;
    if (L <= l && r <= R) {
      lazy[idx] += delta;
      v[idx] += delta;
      return;
    }
    push_down(idx);
    int m = (l + r) / 2;
    update(lc(idx), l, m, L, R, delta);
    update(rc(idx), m + 1, r, L, R, delta);
    push_up(idx);
  }
  int query(int idx, int l, int r, int L, int R) {
    if (R < l || r < L) return 0;
    if (L <= l && r <= R) return v[idx];
    push_down(idx);
    int m = (l + r) / 2;
    int ret = std::max(query(lc(idx), l, m, L, R),
                       query(rc(idx), m + 1, r, L, R));
    push_up(idx);
    return ret;
  }
  void push_down(int idx) {
    if (!lazy[idx]) return;
    int lch = lc(idx);
    int rch = rc(idx);
    lazy[lch] += lazy[idx];
    lazy[rch] += lazy[idx];
    v[lch] += lazy[idx];
    v[rch] += lazy[idx];
    lazy[idx] = 0;
  }
  void push_up(int idx) {
    v[idx] = max(v[lc(idx)], v[rc(idx)]);
  }
};
