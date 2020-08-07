// from: https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/LineContainer.h
// verification: https://codeforces.com/contest/1083/submission/89193199
// This is to implement the Convex Hull Trick for DP optimizations.
// Quickly get the maximum or the minimum from a bunch of linear functions.
// Line : y = k * x + m. p is the x coordination of the intersection with the next line in the container.
// Add(k, m) : insert y = k * x + m to the container
// Query(x) : returns the maximum y at x.
// isect(x, y): calculate x.p and if x.p >= y.p, it means y can be removed.
// To query minimum, need to insert -k and -m, which is basically making symmetric by x axis.
// need at least c++14 to work.

struct Line {
  mutable ll k, m, p;
  bool operator<(const Line &o) const { return k < o.k; }
  bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
 private:
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  const ll inf = LLONG_MAX;
  ll div(ll a, ll b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b);
  }
  bool isect(iterator x, iterator y) {
    if (y == end()) {
      x->p = inf;
      return false;
    }
    if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
    else x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
 public:
  void add(ll k, ll m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  ll query(ll x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};
