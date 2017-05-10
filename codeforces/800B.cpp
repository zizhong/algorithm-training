#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <deque>
#include <set>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <unordered_map>
#include <cassert>
#endif
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
//
#include <cstdio>
#include <cmath>
const double eps = 1e-8;
//const double pi = std::acos(-1.0);
//点
class point
{
public:
    double x, y;
    point(){};
    point(double x, double y):x(x),y(y){};

    static int xmult(const point &ps, const point &pe, const point &po)
    {
        return (ps.x - po.x) * (pe.y - po.y) - (pe.x - po.x) * (ps.y - po.y);
    }

    //相对原点的差乘结果，参数：点[_Off]
    //即由原点和这两个点组成的平行四边形面积
    double operator *(const point &_Off) const
    {
        return x * _Off.y - y * _Off.x;
    }
    //相对偏移
    point operator - (const point &_Off) const
    {
        return point(x - _Off.x, y - _Off.y);
    }
    //点位置相同(double类型)
    bool operator == (const point &_Off) const
    {
        return std::fabs(_Off.x - x) < eps && std::fabs(_Off.y - y) < eps;
    }
    //点位置不同(double类型)
    bool operator != (const point &_Off) const
    {
        return ((*this) == _Off) == false;
    }
    //两点间距离的平方
    double dis2(const point &_Off) const
    {
        return (x - _Off.x) * (x - _Off.x) + (y - _Off.y) * (y - _Off.y);
    }
    //两点间距离
    double dis(const point &_Off) const
    {
        return std::sqrt((x - _Off.x) * (x - _Off.x) + (y - _Off.y) * (y - _Off.y));
    }
};

//两点表示的向量
class pVector
{
public:
    point s, e;//两点表示，起点[s]，终点[e]
    double a, b, c;//一般式,ax+by+c=0

    pVector(){}
    pVector(const point &s, const point &e):s(s),e(e){}

    //向量与点的叉乘,参数：点[_Off]
    //[点相对向量位置判断]
    double operator *(const point &_Off) const
    {
        return (_Off.y - s.y) * (e.x - s.x) - (_Off.x - s.x) * (e.y - s.y);
    }
    //向量与向量的叉乘,参数：向量[_Off]
    double operator *(const pVector &_Off) const
    {
        return (e.x - s.x) * (_Off.e.y - _Off.s.y) - (e.y - s.y) * (_Off.e.x - _Off.s.x);
    }
    //从两点表示转换为一般表示
    bool pton()
    {
        a = s.y - e.y;
        b = e.x - s.x;
        c = s.x * e.y - s.y * e.x;
        return true;
    }

    //-----------点和直线（向量）-----------
    //点在向量左边（右边的小于号改成大于号即可,在对应直线上则加上=号）
    //参数：点[_Off],向量[_Ori]
    friend bool operator<(const point &_Off, const pVector &_Ori)
    {
        return (_Ori.e.y - _Ori.s.y) * (_Off.x - _Ori.s.x)
            < (_Off.y - _Ori.s.y) * (_Ori.e.x - _Ori.s.x);
    }

    friend bool operator>(const point &_Off, const pVector &_Ori)
    {
        return (_Ori.e.y - _Ori.s.y) * (_Off.x - _Ori.s.x)
             > (_Off.y - _Ori.s.y) * (_Ori.e.x - _Ori.s.x);
    }

    //点在直线上,参数：点[_Off]
    bool lhas(const point &_Off) const
    {
        return std::fabs((*this) * _Off) < eps;
    }
    //点在线段上,参数：点[_Off]
    bool shas(const point &_Off) const
    {
        return lhas(_Off)
            && _Off.x - std::min(s.x, e.x) > -eps && _Off.x - std::max(s.x, e.x) < eps
            && _Off.y - std::min(s.y, e.y) > -eps && _Off.y - std::max(s.y, e.y) < eps;
    }

    //点到直线/线段的距离
    //参数： 点[_Off], 是否是线段[isSegment](默认为直线)
    double dis(const point &_Off, bool isSegment = false)
    {
        //化为一般式
        pton();

        //到直线垂足的距离
        double td = (a * _Off.x + b * _Off.y + c) / sqrt(a * a + b * b);

        //如果是线段判断垂足
        if(isSegment)
        {
            double xp = (b * b * _Off.x - a * b * _Off.y - a * c) / ( a * a + b * b);
            double yp = (-a * b * _Off.x + a * a * _Off.y - b * c) / (a * a + b * b);
            double xb = std::max(s.x, e.x);
            double yb = std::max(s.y, e.y);
            double xs = s.x + e.x - xb;
            double ys = s.y + e.y - yb;
            if(xp > xb + eps || xp < xs - eps || yp > yb + eps || yp < ys - eps)
                td = std::min(_Off.dis(s), _Off.dis(e));
        }

        return fabs(td);
    }

    //关于直线对称的点
    point mirror(const point &_Off) const
    {
        //注意先转为一般式
        point ret;
        double d = a * a + b * b;
        ret.x = (b * b * _Off.x - a * a * _Off.x - 2 * a * b * _Off.y - 2 * a * c) / d;
        ret.y = (a * a * _Off.y - b * b * _Off.y - 2 * a * b * _Off.x - 2 * b * c) / d;
        return ret;
    }
    //计算两点的中垂线
    static pVector ppline(const point &_a, const point &_b)
    {
        pVector ret;
        ret.s.x = (_a.x + _b.x) / 2;
        ret.s.y = (_a.y + _b.y) / 2;
        //一般式
        ret.a = _b.x - _a.x;
        ret.b = _b.y - _a.y;
        ret.c = (_a.y - _b.y) * ret.s.y + (_a.x - _b.x) * ret.s.x;
        //两点式
        if(std::fabs(ret.a) > eps)
        {
            ret.e.y = 0.0;
            ret.e.x = - ret.c / ret.a;
            if(ret.e == ret. s)
            {
                ret.e.y = 1e10;
                ret.e.x = - (ret.c - ret.b * ret.e.y) / ret.a;
            }
        }
        else
        {
            ret.e.x = 0.0;
            ret.e.y = - ret.c / ret.b;
            if(ret.e == ret. s)
            {
                ret.e.x = 1e10;
                ret.e.y = - (ret.c - ret.a * ret.e.x) / ret.b;
            }
        }
        return ret;
    }

    //------------直线和直线（向量）-------------
    //直线重合,参数：直线向量[_Off]
    bool equal(const pVector &_Off) const
    {
        return lhas(_Off.e) && lhas(_Off.s);
    }
    //直线平行，参数：直线向量[_Off]
    bool parallel(const pVector &_Off) const
    {
        return std::fabs((*this) * _Off) < eps;
    }
    //两直线交点，参数：目标直线[_Off]
    point crossLPt(pVector _Off)
    {
        //注意先判断平行和重合
        point ret = s;
        double t = ((s.x - _Off.s.x) * (_Off.s.y - _Off.e.y) - (s.y - _Off.s.y) * (_Off.s.x - _Off.e.x))
                / ((s.x - e.x) * (_Off.s.y - _Off.e.y) - (s.y - e.y) * (_Off.s.x - _Off.e.x));
        ret.x += (e.x - s.x) * t;
        ret.y += (e.y - s.y) * t;
        return ret;
    }

    //------------线段和直线（向量）----------
    //线段和直线交
    //参数：线段[_Off]
    bool crossSL(const pVector &_Off) const
    {
        double rs = (*this) * _Off.s;
        double re = (*this) * _Off.e;
        return rs * re < eps;
    }

    //------------线段和线段（向量）----------
    //判断线段是否相交(注意添加eps)，参数：线段[_Off]
    bool isCrossSS(const pVector &_Off) const
    {
        //1.快速排斥试验判断以两条线段为对角线的两个矩形是否相交
        //2.跨立试验（等于0时端点重合）
        return (
            (std::max(s.x, e.x) >= std::min(_Off.s.x, _Off.e.x)) &&
            (std::max(_Off.s.x, _Off.e.x) >= std::min(s.x, e.x)) &&
            (std::max(s.y, e.y) >= std::min(_Off.s.y, _Off.e.y)) &&
            (std::max(_Off.s.y, _Off.e.y) >= std::min(s.y, e.y)) &&
            ((pVector(_Off.s, s) * _Off) * (_Off * pVector(_Off.s, e)) >= 0.0) &&
            ((pVector(s, _Off.s) * (*this)) * ((*this) * pVector(s, _Off.e)) >= 0.0)
            );
    }
};

class polygon
{
public:
    const static long maxpn = 100;
    point pt[maxpn];//点（顺时针或逆时针）
    long n;//点的个数

    point& operator[](int _p)
    {
        return pt[_p];
    }

    //求多边形面积，多边形内点必须顺时针或逆时针
    double area() const
    {
        double ans = 0.0;
        int i;
        for(i = 0; i < n; i ++)
        {
            int nt = (i + 1) % n;
            ans += pt[i].x * pt[nt].y - pt[nt].x * pt[i].y;
        }
        return std::fabs(ans / 2.0);
    }
    //求多边形重心，多边形内点必须顺时针或逆时针
    point gravity() const
    {
        point ans;
        ans.x = ans.y = 0.0;
        int i;
        double area = 0.0;
        for(i = 0; i < n; i ++)
        {
            int nt = (i + 1) % n;
            double tp = pt[i].x * pt[nt].y - pt[nt].x * pt[i].y;
            area += tp;
            ans.x += tp * (pt[i].x + pt[nt].x);
            ans.y += tp * (pt[i].y + pt[nt].y);
        }
        ans.x /= 3 * area;
        ans.y /= 3 * area;
        return ans;
    }
    //判断点在凸多边形内，参数：点[_Off]
    bool chas(const point &_Off) const
    {
        double tp = 0, np;
        int i;
        for(i = 0; i < n; i ++)
        {
            np = pVector(pt[i], pt[(i + 1) % n]) * _Off;
            if(tp * np < -eps)
                return false;
            tp = (std::fabs(np) > eps)?np: tp;
        }
        return true;
    }
    //判断点是否在任意多边形内[射线法]，O(n)
    bool ahas(const point &_Off) const
    {
        int ret = 0;
        double infv = 1e-10;//坐标系最大范围
        pVector l = pVector(_Off, point( -infv ,_Off.y));
        for(int i = 0; i < n; i ++)
        {
            pVector ln = pVector(pt[i], pt[(i + 1) % n]);
            if(fabs(ln.s.y - ln.e.y) > eps)
            {
                point tp = (ln.s.y > ln.e.y)? ln.s: ln.e;
                if(fabs(tp.y - _Off.y) < eps && tp.x < _Off.x + eps)
                    ret ++;
            }
            else if(ln.isCrossSS(l))
                ret ++;
        }
        return (ret % 2 == 1);
    }
    //凸多边形被直线分割,参数：直线[_Off]
    polygon split(pVector _Off)
    {
        //注意确保多边形能被分割
        polygon ret;
        point spt[2];
        double tp = 0.0, np;
        bool flag = true;
        int i, pn = 0, spn = 0;
        for(i = 0; i < n; i ++)
        {
            if(flag)
                pt[pn ++] = pt[i];
            else
                ret.pt[ret.n ++] = pt[i];
            np = _Off * pt[(i + 1) % n];
            if(tp * np < -eps)
            {
                flag = !flag;
                spt[spn ++] = _Off.crossLPt(pVector(pt[i], pt[(i + 1) % n]));
            }
            tp = (std::fabs(np) > eps)?np: tp;
        }
        ret.pt[ret.n ++] = spt[0];
        ret.pt[ret.n ++] = spt[1];
        n = pn;
        return ret;
    }

    //-------------凸包-------------
    //Graham扫描法，复杂度O(nlg(n)),结果为逆时针
    //#include <algorithm>
    static bool graham_cmp(const point &l, const point &r)//凸包排序函数
    {
        return l.y < r.y || (l.y == r.y && l.x < r.x);
    }
    polygon& graham(point _p[], int _n)
    {
        int i, len;
        std::sort(_p, _p + _n, polygon::graham_cmp);
        n = 1;
        pt[0] = _p[0], pt[1] = _p[1];
        for(i = 2; i < _n; i ++)
        {
            while(n && point::xmult(_p[i], pt[n], pt[n - 1]) >= 0)
                n --;
            pt[++ n] = _p[i];
        }
        len = n;
        pt[++ n] = _p[_n - 2];
        for(i = _n - 3; i >= 0; i --)
        {
            while(n != len && point::xmult(_p[i], pt[n], pt[n - 1]) >= 0)
                n --;
            pt[++ n] = _p[i];
        }
        return (*this);
    }

    //凸包旋转卡壳(注意点必须顺时针或逆时针排列)
    //返回值凸包直径的平方（最远两点距离的平方）
    double rotating_calipers()
    {
        int i = 1;
        double ret = 0.0;
        pt[n] = pt[0];
        for(int j = 0; j < n; j ++)
        {
            while(fabs(point::xmult(pt[j], pt[j + 1], pt[i + 1])) > fabs(point::xmult(pt[j], pt[j + 1], pt[i])) + eps)
                i = (i + 1) % n;
            //pt[i]和pt[j],pt[i + 1]和pt[j + 1]可能是对踵点
            ret = std::max(ret, std::max(pt[i].dis(pt[j]), pt[i + 1].dis(pt[j + 1])));
        }
        return ret;
    }

    //凸包旋转卡壳(注意点必须逆时针排列)
    //返回值两凸包的最短距离
    double rotating_calipers(polygon &_Off)
    {
        int i = 0;
        double ret = 1e10;//inf
        pt[n] = pt[0];
        _Off.pt[_Off.n] = _Off.pt[0];
        //注意凸包必须逆时针排列且pt[0]是左下角点的位置
        while(_Off.pt[i + 1].y > _Off.pt[i].y)
            i = (i + 1) % _Off.n;
        for(int j = 0; j < n; j ++)
        {
            double tp;
            //逆时针时为 >,顺时针则相反
            while((tp = point::xmult(pt[j], pt[j + 1], _Off.pt[i + 1]) - point::xmult( pt[j], pt[j + 1], _Off.pt[i])) > eps)
                i = (i + 1) % _Off.n;
            //(pt[i],pt[i+1])和(_Off.pt[j],_Off.pt[j + 1])可能是最近线段
            ret = std::min(ret, pVector(pt[j], pt[j + 1]).dis(_Off.pt[i], true));
            ret = std::min(ret, pVector(_Off.pt[i], _Off.pt[i + 1]).dis(pt[j + 1], true));
            if(tp > -eps)//如果不考虑TLE问题最好不要加这个判断
            {
                ret = std::min(ret, pVector(pt[j], pt[j + 1]).dis(_Off.pt[i + 1], true));
                ret = std::min(ret, pVector(_Off.pt[i], _Off.pt[i + 1]).dis(pt[j], true));
            }
        }
        return ret;
    }

    //-----------半平面交-------------
    //复杂度:O(nlog2(n))
    //#include <algorithm>
    //半平面计算极角函数[如果考虑效率可以用成员变量记录]
    static double hpc_pa(const pVector &_Off)
    {
        return atan2(_Off.e.y - _Off.s.y, _Off.e.x - _Off.s.x);
    }
    //半平面交排序函数[优先顺序: 1.极角 2.前面的直线在后面的左边]
    static bool hpc_cmp(const pVector &l, const pVector &r)
    {
        double lp = hpc_pa(l), rp = hpc_pa(r);
        if(fabs(lp - rp) > eps)
            return lp < rp;
        return point::xmult(l.s, r.e, r.s) < 0.0;
    }
    //用于计算的双端队列
    pVector dequeue[maxpn];
    //获取半平面交的多边形（多边形的核）
    //参数：向量集合[l]，向量数量[ln];(半平面方向在向量左边）
    //函数运行后如果n[即返回多边形的点数量]为0则不存在半平面交的多边形（不存在区域或区域面积无穷大）
    polygon& halfPanelCross(pVector _Off[], int ln)
    {
        int i, tn;
        n = 0;
        std::sort(_Off, _Off + ln, hpc_cmp);
        //平面在向量左边的筛选
        for(i = tn = 1; i < ln; i ++)
            if(fabs(hpc_pa(_Off[i]) - hpc_pa(_Off[i - 1])) > eps)
                _Off[tn ++] = _Off[i];
        ln = tn;
        int bot = 0, top = 1;
        dequeue[0] = _Off[0];
        dequeue[1] = _Off[1];
        for(i = 2; i < ln; i ++)
        {
            if(dequeue[top].parallel(dequeue[top - 1]) ||
                dequeue[bot].parallel(dequeue[bot + 1]))
                return (*this);
            while(bot < top &&
                point::xmult(dequeue[top].crossLPt(dequeue[top - 1]), _Off[i].e, _Off[i].s) > eps)
                top --;
            while(bot < top &&
                point::xmult(dequeue[bot].crossLPt(dequeue[bot + 1]), _Off[i].e, _Off[i].s) > eps)
                bot ++;
            dequeue[++ top] = _Off[i];
        }

        while(bot < top &&
            point::xmult(dequeue[top].crossLPt(dequeue[top - 1]), dequeue[bot].e, dequeue[bot].s) > eps)
            top --;
        while(bot < top &&
            point::xmult(dequeue[bot].crossLPt(dequeue[bot + 1]), dequeue[top].e, dequeue[top].s) > eps)
            bot ++;
        //计算交点(注意不同直线形成的交点可能重合)
        if(top <= bot + 1)
            return (*this);
        for(i = bot; i < top; i ++)
            pt[n ++] = dequeue[i].crossLPt(dequeue[i + 1]);
        if(bot < top + 1)
            pt[n ++] = dequeue[bot].crossLPt(dequeue[top]);
        return (*this);
    }
};
class circle
{
public:
    point c;//圆心
    double r;//半径
    double db, de;//圆弧度数起点， 圆弧度数终点(逆时针0-360)

    //-------圆---------

    //判断圆在多边形内
    bool inside(const polygon &_Off) const
    {
        if(_Off.ahas(c) == false)
            return false;
        for(int i = 0; i < _Off.n; i ++)
        {
            pVector l = pVector(_Off.pt[i], _Off.pt[(i + 1) % _Off.n]);
            if(l.dis(c, true) < r - eps)
                return false;
        }
        return true;
    }

    //判断多边形在圆内（线段和折线类似）
    bool has(const polygon &_Off) const
    {
        for(int i = 0; i < _Off.n; i ++)
            if(_Off.pt[i].dis2(c) > r * r - eps)
                return false;
        return true;
    }

    //-------圆弧-------
    //圆被其他圆截得的圆弧，参数：圆[_Off]
    circle operator-(circle &_Off) const
    {
        //注意圆必须相交，圆心不能重合
        double d2 = c.dis2(_Off.c);
        double d = c.dis(_Off.c);
        double ans = std::acos((d2 + r * r - _Off.r * _Off.r) / (2 * d * r));
        point py = _Off.c - c;
        double oans = std::atan2(py.y, py.x);
        circle res;
        res.c = c;
        res.r = r;
        res.db = oans + ans;
        res.de = oans - ans + 2 * pi;
        return res;
    }
    //圆被其他圆截得的圆弧，参数：圆[_Off]
    circle operator+(circle &_Off) const
    {
        //注意圆必须相交，圆心不能重合
        double d2 = c.dis2(_Off.c);
        double d = c.dis(_Off.c);
        double ans = std::acos((d2 + r * r - _Off.r * _Off.r) / (2 * d * r));
        point py = _Off.c - c;
        double oans = std::atan2(py.y, py.x);
        circle res;
        res.c = c;
        res.r = r;
        res.db = oans - ans;
        res.de = oans + ans;
        return res;
    }

    //过圆外一点的两条切线
    //参数：点[_Off](必须在圆外),返回：两条切线(切线的s点为_Off,e点为切点)
    std::pair<pVector, pVector>  tangent(const point &_Off) const
    {
        double d = c.dis(_Off);
        //计算角度偏移的方式
        double angp = std::acos(r / d), ango = std::atan2(_Off.y - c.y, _Off.x - c.x);
        point pl = point(c.x + r * std::cos(ango + angp), c.y + r * std::sin(ango + angp)),
            pr = point(c.x + r * std::cos(ango - angp), c.y + r * std::sin(ango - angp));
        return std::make_pair(pVector(_Off, pl), pVector(_Off, pr));
    }

    //计算直线和圆的两个交点
    //参数：直线[_Off](两点式)，返回两个交点，注意直线必须和圆有两个交点
    std::pair<point, point> cross(pVector _Off) const
    {
        _Off.pton();
        //到直线垂足的距离
        double td = fabs(_Off.a * c.x + _Off.b * c.y + _Off.c) / sqrt(_Off.a * _Off.a + _Off.b * _Off.b);

        //计算垂足坐标
        double xp = (_Off.b * _Off.b * c.x - _Off.a * _Off.b * c.y - _Off.a * _Off.c) / ( _Off.a * _Off.a + _Off.b * _Off.b);
        double yp = (- _Off.a * _Off.b * c.x + _Off.a * _Off.a * c.y - _Off.b * _Off.c) / (_Off.a * _Off.a + _Off.b * _Off.b);

        double ango = std::atan2(yp - c.y, xp - c.x);
        double angp = std::acos(td / r);

        return std::make_pair(point(c.x + r * std::cos(ango + angp), c.y + r * std::sin(ango + angp)),
            point(c.x + r * std::cos(ango - angp), c.y + r * std::sin(ango - angp)));
    }
};

class triangle
{
public:
    point a, b, c;//顶点
    triangle(){}
    triangle(point a, point b, point c): a(a), b(b), c(c){}

    //计算三角形面积
    double area()
    {
        return fabs(point::xmult(a, b, c)) / 2.0;
    }

    //计算三角形外心
    //返回：外接圆圆心
    point circumcenter()
    {
        pVector u,v;
        u.s.x = (a.x + b.x) / 2;
        u.s.y = (a.y + b.y) / 2;
        u.e.x = u.s.x - a.y + b.y;
        u.e.y = u.s.y + a.x - b.x;
        v.s.x = (a.x + c.x) / 2;
        v.s.y = (a.y + c.y) / 2;
        v.e.x = v.s.x - a.y + c.y;
        v.e.y = v.s.y + a.x - c.x;
        return u.crossLPt(v);
    }

    //计算三角形内心
    //返回：内接圆圆心
    point incenter()
    {
        pVector u, v;
        double m, n;
        u.s = a;
        m = atan2(b.y - a.y, b.x - a.x);
        n = atan2(c.y - a.y, c.x - a.x);
        u.e.x = u.s.x + cos((m + n) / 2);
        u.e.y = u.s.y + sin((m + n) / 2);
        v.s = b;
        m = atan2(a.y - b.y, a.x - b.x);
        n = atan2(c.y - b.y, c.x - b.x);
        v.e.x = v.s.x + cos((m + n) / 2);
        v.e.y = v.s.y + sin((m + n) / 2);
        return u.crossLPt(v);
    }

    //计算三角形垂心
    //返回：高的交点
    point perpencenter()
    {
        pVector u,v;
        u.s = c;
        u.e.x = u.s.x - a.y + b.y;
        u.e.y = u.s.y + a.x - b.x;
        v.s = b;
        v.e.x = v.s.x - a.y + c.y;
        v.e.y = v.s.y + a.x - c.x;
        return u.crossLPt(v);
    }

    //计算三角形重心
    //返回：重心
    //到三角形三顶点距离的平方和最小的点
    //三角形内到三边距离之积最大的点
    point barycenter()
    {
        pVector u,v;
        u.s.x = (a.x + b.x) / 2;
        u.s.y = (a.y + b.y) / 2;
        u.e = c;
        v.s.x = (a.x + c.x) / 2;
        v.s.y = (a.y + c.y) / 2;
        v.e = b;
        return u.crossLPt(v);
    }

    //计算三角形费马点
    //返回：到三角形三顶点距离之和最小的点
    point fermentpoint()
    {
        point u, v;
        double step = fabs(a.x) + fabs(a.y) + fabs(b.x) + fabs(b.y) + fabs(c.x) + fabs(c.y);
        int i, j, k;
        u.x = (a.x + b.x + c.x) / 3;
        u.y = (a.y + b.y + c.y) / 3;
        while (step > eps)
        {
            for (k = 0; k < 10; step /= 2, k ++)
            {
                for (i = -1; i <= 1; i ++)
                {
                    for (j = -1; j <= 1; j ++)
                    {
                        v.x = u.x + step * i;
                        v.y = u.y + step * j;
                        if (u.dis(a) + u.dis(b) + u.dis(c) > v.dis(a) + v.dis(b) + v.dis(c))
                            u = v;
                    }
                }
            }
        }
        return u;
    }
};

//
/*int n, p;
vector<int> a;
vector<int> b;

bool ok(double t) {
    double changeT = 0;
    for(int i = 0; i < n; i++) {
        double e = a[i] * t - b[i];
        if (e > 0) {
            changeT += e / p;
        }
        if (changeT > t) return false;
    }
    return true;
}

void solveA(int ncase) {
    //cout << "Case #" << ncase << ": ";
    double l = 0, r = 1e40;
    cin >> n >> p;
    cout << n << " " << p << endl;
    a.assign(n, 0);
    b.assign(n, 0);
    double suma = 0, sumb = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d%d", &a[i], &b[i]);
        suma += a[i];
        sumb += b[i];
    }
    if (suma <= p) {
        cout << -1 << endl;
        return;
    }
    for(int i = 0; i < 1000; i++) {
        double mid = 0.5 * (l + r);
        if (ok(mid)) l = mid;
        else r = mid;
    }
    cout << l << endl;
}*/

void update(const vector<int> z, const vector<point>& v, double& ans) {
    for(int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (z[i] == z[j]) return;
        }
    }
    vector<point> vp = {v[z[0]], v[z[1]], v[z[2]]};
    for(int j = 0; j < 3; j++) {
        point p = vp[j];
        pVector pv(vp[(j+1)%3], vp[(j+2)%3]);
        double d = pv.dis(p);
        ans = min(ans, d * 0.5);
    }
}

void solve(int ncase) {
    //cout << "Case #" << ncase << ": ";
    int n;
    cin >> n;
    vector<point> vp(n);
    for(int i = 0; i < n; i ++) {
        cin >> vp[i].x >> vp[i].y;
    }
    double ans = 1e40;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (i == j) continue;
            update({i, j, (i + n - 1) % n}, vp, ans);
            update({i, j, (j + n - 1) % n}, vp, ans);
            update({i, j, (i + 1) % n}, vp, ans);
            update({i, j, (j + 1) % n}, vp, ans);
            
        }
        vector<point> tripe = {vp[i], vp[(i+1)%n], vp[(i+2)%n]};
    }
    cout << ans << endl;
}
int main() {
    //ios::sync_with_stdio(false);
    cout << std::fixed;
    cout << setprecision(9);
#ifdef _zzz_
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    //precalc();
    int T = 1;
    //scanf("%d", &T);
    //cin >> T;
    int ncase = 0;
    while(T --) {
        solve(++ ncase);
    }
}
