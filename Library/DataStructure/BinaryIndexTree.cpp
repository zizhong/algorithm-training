typedef long long ll;
struct BIT {
  BIT(int n) {
    a.assign(n + 1, 0);
  }
  ll sum(int x) {
    ll ret = 0;
    while(x > 0) {
      ret += a[x];
      x -= low_bit(x);
    }
    return ret;
  }
  ll sum(int l, int r) {
      return sum(r) - sum(l-1);
  }
  void add(int x, ll delta) {
    while(x < a.size()) {
      a[x] += delta;
      x += low_bit(x);
    }
  }
  vector<ll> a;
  static inline int low_bit(int x){return x&(-x);}
};
