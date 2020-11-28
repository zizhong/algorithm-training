// https://codeforces.com/gym/304511/problem/L

constexpr int INF = 0x3f3f3f3f;
constexpr int N = 1e5 + 100;

vector<int> v[N];

struct node {
  int type;
  int k, l, r, c, x;
} s[N];

ll kData[1050];

struct Splay {
  static const int maxn = 1e3 + 100;

#define lson(x) spl[x].ch[0]
#define rson(x) spl[x].ch[1]

  struct node {
    int ch[2], siz, fa, rev;
    ll add, sum, val;
  } spl[maxn];

  int tot = 0, st[maxn];

  bool ident(int x, int f) {
    return rson(f) == x;
  }

  void connect(int x, int f, int s) {
    spl[f].ch[s] = x;
    spl[x].fa = f;
  }

  void push_up(int x) {
    spl[x].siz = 1;
    spl[x].sum = spl[x].val;
    if (lson(x)) spl[x].siz += spl[lson(x)].siz, spl[x].sum += spl[lson(x)].sum;
    if (rson(x)) spl[x].siz += spl[rson(x)].siz, spl[x].sum += spl[rson(x)].sum;
  }

  void revtag(int x) {
    if (not x) return;
    swap(lson(x), rson(x));
    spl[x].rev ^= 1;
  }

  void addtag(int x, int val) {
    if (not x) return;
    spl[x].val += val, spl[x].sum += val * spl[x].siz, spl[x].add += val;
  }

  void push_down(int x) {
    if (spl[x].rev) {
      if (lson(x)) revtag(lson(x));
      if (rson(x)) revtag(rson(x));
      spl[x].rev = 0;
    }
    if (spl[x].add) {
      if (lson(x)) addtag(lson(x), spl[x].add);
      if (rson(x)) addtag(rson(x), spl[x].add);
      spl[x].add = 0;
    }
  }

  void rotate(int x) {
    int f = spl[x].fa, ff = spl[f].fa, k = ident(x, f);
    connect(spl[x].ch[k ^ 1], f, k);
    connect(x, ff, ident(f, ff));
    connect(f, x, k ^ 1);
    push_up(f), push_up(x);
  }

  void splaying(int x, int to) {
    int y = x, top = 0;
    // push_down on all the nodes to the root.
    st[++top] = y;
    while (spl[y].fa) st[++top] = spl[y].fa, y = spl[y].fa;
    while (top) push_down(st[top--]); // ***
    while (spl[x].fa != to) {
      int f = spl[x].fa, ff = spl[f].fa;
      if (ff == to) rotate(x);
      else if (ident(x, f) == ident(f, ff)) rotate(f), rotate(x);
      else rotate(x), rotate(x);
    }
    push_up(x);// ***
  }

  int build(int fa, int l, int r) {
    if (l > r) return 0;
    int mid = l + r >> 1;
    int now = ++tot;
    spl[now].val = kData[mid], spl[now].fa = fa, spl[now].rev = spl[now].add = 0;
    lson(now) = build(now, l, mid - 1);
    rson(now) = build(now, mid + 1, r);
    push_up(now);
    return now;
  }

  int arank(int x) {
    int now = spl[0].ch[1];
    while (true) {
      push_down(now); // *
      int sum = spl[lson(now)].siz + 1;
      if (x == sum) return now;
      if (sum > x) now = lson(now);
      else {
        x -= sum;
        now = rson(now);
      }
    }
  }

  int locate_range(int l, int r) {
    l = arank(l), r = arank(r + 2);
    splaying(l, 0);
    splaying(r, l);
    return lson(r);
  }
  void turn(int l, int r) {
    revtag(locate_range(l, r));
  }

  void add(int l, int r, ll val) {
    addtag(locate_range(l, r), val);
  }

  ll query(int l, int r) {
    return spl[locate_range(l, r)].sum;
  }

  void print(int node) {
    push_down(node);
    if (lson(node)) print(lson(node));
    if (node and spl[node].val != INF and spl[node].val != -INF) cout << spl[node].val << " ";
    if (rson(node)) print(rson(node));
  }

} tree[1050];

map<int, ll> ans;

int vis[N];

void dfs(int node, int fa) {
  int type = s[node].type;
  if (type == 1) {
    tree[s[node].k].turn(s[node].l, s[node].r);
  } else if (type == 2) {
    tree[s[node].k].add(s[node].l, s[node].r, s[node].c);
  } else if (type == 3) {
    ans[node] = tree[s[node].k].query(s[node].l, s[node].r);
  }

  for (auto to : v[node]) {
    if (to == fa) continue;
    dfs(to, node);
  }

  if (type == 1) {
    tree[s[node].k].turn(s[node].l, s[node].r);
  } else if (type == 2) {
    tree[s[node].k].add(s[node].l, s[node].r, -s[node].c);
  }
}

void solve(int ncase) {
  int n = ri(), m = ri(), q = ri();
  kData[1] = -INF, kData[m + 2] = INF;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      kData[j + 1] = rl();
    }
    tree[i].spl[0].ch[1] = tree[i].build(0, 1, m + 2);
  }

  for (int i = 1; i <= q; ++i) {
    int type = ri();
    if (type == 1 or type == 3) {
      s[i].k = ri(), s[i].l = ri(), s[i].r = ri();
    } else if (type == 2) {
      s[i].k = ri(), s[i].l = ri(), s[i].r = ri(), s[i].c = ri();
    } else if (type == 4) {
      s[i].x = ri();
    }

    s[i].type = type;

    if (type == 4) v[s[i].x].emplace_back(i), v[i].emplace_back(s[i].x);
    else if (i - 1 > 0) v[i].emplace_back(i - 1), v[i - 1].emplace_back(i);
  }

  dfs(1, 0);

  for (auto k : ans) {
    printf("%lld\n", k.second);
  }
}
