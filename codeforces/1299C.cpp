#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <deque>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <ctime>
#include <queue>
#include <stack>
#include<iomanip>
#include <sstream>
#include <cmath>
//#include "utils/haha.h"
//#include "utils/max_flow.h"
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<string, int> PSI;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;
typedef pair<double, double> PDD;
typedef pair<ll, PII> PLP;
#define CLS(x, v) (memset((x), (v), sizeof((x))))
const double pi = acos(-1);
const int mod = 1000000007;
const int inf = 0x3fffffff;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct PairHash {
  template<typename T1, typename T2>
  std::size_t operator()(const pair<T1, T2> &p) const {
    return hash<T1>()(p.first) ^ hash<T2>()(p.second);
  }
};

//点
class Point
{
 public:
  ll x, y;
  Point(){};
  Point(ll x, ll y):x(x),y(y){};

  static ll xmult(const Point &ps, const Point &pe, const Point &po)
  {
    return (ps.x - po.x) * (pe.y - po.y) - (pe.x - po.x) * (ps.y - po.y);
  }
};

class Polygon
{
 public:
  const static long maxpn = 100010;
  vector<Point> pt;
  long n;//点的个数

  Point& operator[](int _p)
  {
    return pt[_p];
  }
  //-------------凸包-------------
  //Graham扫描法，复杂度O(nlg(n)),结果为逆时针
  //#include <algorithm>
  static bool graham_cmp(const Point &l, const Point &r)//凸包排序函数
  {
    return l.y < r.y || (l.y == r.y && l.x < r.x);
  }
  Polygon& half_graham(Point _p[], int _n)
  {
    //cout << _n << endl;
    pt.assign(_n + 10, Point(0, 0));
    int i, len;
    //std::sort(_p, _p + _n, Polygon::graham_cmp);
    n = 1;
    pt[0] = _p[0], pt[1] = _p[1];
    for(i = 2; i < _n; i ++)
    {
      while(n && Point::xmult(_p[i], pt[n], pt[n - 1]) >= 0)
        n --;
      pt[++ n] = _p[i];
    }
    len = n;
    pt[++ n] = _p[_n - 2];
    /*for(i = _n - 3; i >= 0; i --)
    {
      while(n != len && Point::xmult(_p[i], pt[n], pt[n - 1]) >= 0)
        n --;
      pt[++ n] = _p[i];
    }*/
    return (*this);
  }
};

Point pg1[1000010];
int n;
void solve(int ncase) {
  int n;
  scanf("%d", &n);
  vector<ll> pre_sum(n+1);
  pg1[0] = Point(0, 0);
  for(int i = 1; i <= n; i++) {
    scanf("%I64d", &pre_sum[i]);
    pre_sum[i] += pre_sum[i-1];
    pg1[i] = Point(i, pre_sum[i]);
  }
  Polygon p;
  p.half_graham(pg1, n+1);
  int pre = 0;
  for(int i = 1; i < p.n ; i++) {
    //cout << p.pt[i].x << " " << p.pt[i].y << endl;
    double v = pre_sum[p.pt[i].x] - (pre >= 0 ? pre_sum[pre]: 0);
    int nx = p.pt[i].x - pre;
    int z = nx;
    while(z --) printf("%.10lf\n", v / nx);
    pre = p.pt[i].x;
  }
}

int main() {
  //ios::sync_with_stdio(false);
  cout << std::fixed;
  cout << setprecision(9);
#ifdef _zzz_
  freopen("C:\\Users\\grain\\Desktop\\in.txt", "r", stdin);
  //freopen("out.txt", "w", stdout);
#endif
  //precalc();
  int T = 1;
  //scanf("%d", &T);
  //cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
