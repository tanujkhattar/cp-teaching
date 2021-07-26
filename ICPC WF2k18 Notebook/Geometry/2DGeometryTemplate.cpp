#define CT double
const CT EPS =1e-12;
#define EQ(a, b) (fabs((a) - (b)) <= EPS)
#define LT(a, b) ((a) < (b) - EPS)         /* less than */
struct Point {
  CT x, y;
  Point() {}
  Point(CT x, CT y) : x(x), y(y) {}
  Point(const Point &p) : x(p.x), y(p.y){}
  Point operator+(const Point &p)const{return Point(x+p.x,y+p.y);}
  Point operator-(const Point &p)const{return Point(x-p.x,y-p.y);}
  Point operator * (double c) const{return Point(x*c,y*c);}
  Point operator / (double c) const{return Point(x/c,y/c);}
};CT dot(Point p, Point q){return p.x*q.x+p.y*q.y;}
double dist2(Point p, Point q){return dot(p-q,p-q);}
CT cross(Point p, Point q){return p.x*q.y-p.y*q.x;}
ostream &operator<<(ostream &os, const Point &p){
  return os << "(" << p.x << "," << p.y << ")";
}bool operator < (const Point& a, const Point& b){
  if(!EQ(a.x, b.x))return LT(a.x, b.x);
  else return LT(a.y, b.y);
}bool operator == (const Point& a, const Point& b) {
  return EQ(a.x, b.x) && EQ(a.y, b.y);
}// rotate a point CCW or CW around the origin
Point RotateCCW90(Point p){ return Point(-p.y,p.x); }
Point RotateCW90(Point p){ return Point(p.y,-p.x); }
Point RotateCCW(Point p, double t) {//t in radians.
  return Point(p.x*cos(t)-p.y*sin(t),p.x*sin(t)+p.y*cos(t));
}// project point c onto line through a and b assuming a != b
Point ProjectPointLine(Point a, Point b, Point c) {
  return a + (b-a)*dot(c-a, b-a)/dot(b-a, b-a);
}// project point c onto line segment through a and b
Point ProjectPointSegment(Point a, Point b, Point c){
  double r = dot(b-a,b-a); if (EQ(r, 0)) return a;
  r = dot(c-a, b-a)/r; if (r < 0) return a; 
  if (r > 1) return b;return a + (b-a)*r;
}//return line perp. to line through a & b, passing through c
pair<Point,Point> Perpendicularline(Point a,Point b,Point c){
  c=ProjectPointLine(a,b,c);if(a==c) a=b;
  return MP(c,c+RotateCW90(a-c));
}// compute distance from c to segment between a and b
double DistancePointSegment(Point a, Point b, Point c) {
  return sqrt(dist2(c, ProjectPointSegment(a, b, c)));
}// compute distance between point (x,y,z) & plane ax+by+cz=d
double DistancePointPlane(double x, double y, double z,
    double a, double b, double c, double d){
  return fabs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);
}// determine if lines (a, b) and (c, d) are || or collinear
bool LinesParallel(Point a, Point b, Point c, Point d) {
  return EQ(cross(b-a, c-d), 0);
}bool LinesCollinear(Point a, Point b, Point c, Point d) {
  return LinesParallel(a, b, c, d) && EQ(cross(a-b, a-c),0) 
    && EQ(cross(c-d, c-a), 0);
}// determine if line segment from a to b intersects with
// line segment from c to d
bool SegmentsIntersect(Point a, Point b, Point c, Point d) {
  if(b==d||b==c||a==d||a==c)return false;
  if (LinesCollinear(a, b, c, d)) {
    if (EQ(dist2(a, c),0) || EQ(dist2(a, d),0) || 
        EQ(dist2(b, c),0) || EQ(dist2(b, d),0))return true;
    if (dot(c-a,c-b)>0 && dot(d-a,d-b)>0 && dot(c-b,d-b)>0)
      return false;
    return true;
  }if (cross(d-a, b-a) * cross(c-a, b-a) > 0) return false;
  if (cross(a-c, d-c) * cross(b-c, d-c) > 0) return false;
  return true;
}// compute intersection of line passing through a & b with line
// passing through c & d, assuming unique intersection exists; 
// for segment intersection, check if segments intersect first.
Point ComputeLineIntersection(Point a,Point b,Point c,Point d){
  b=b-a; d=c-d; c=c-a;assert(dot(b,b)>EPS&&dot(d,d)>EPS);
  return a + b*cross(c, d)/cross(b, d);
}// compute center of circle given three points
Point ComputeCircleCenter(Point a, Point b, Point c) {
  b=(a+b)/2;c=(a+c)/2;return //next line.
    ComputeLineIntersection(b,b+RotateCW90(a-b),c,c+RotateCW90(a-c));
}// determine if point is in a possibly non-convex polygon
// returns 1 for strictly interior points, 0 for strictly
// exterior points, and 0 or 1 for the remaining points.
bool PointInPolygon(const vector<Point> &p, Point q) {
  bool c = 0;REP(i, SZ(p)){
    int j = (i+1)%SZ(p);
    if((p[i].y<=q.y&&q.y<p[j].y||p[j].y<=q.y&&q.y<p[i].y)&&
        q.x<p[i].x+(p[j].x-p[i].x)*(q.y-p[i].y)/(p[j].y-p[i].y))
      c = !c;
  }return c;
}// determine if point is on the boundary of a polygon
bool PointOnPolygon(const vector<Point> &p, Point q){
  REP(i,SZ(p)){auto pp=ProjectPointSegment(p[i],p[(i+1)%SZ(p)],q);
    if(dist2(pp, q) < EPS)return true;}
  return false;
}// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<Point> CircleLineIntersection(Point a,Point b,Point c,double r){
  vector<Point> ret; b = b-a; a = a-c;
  double A = dot(b, b); double B = dot(a, b);
  double C = dot(a, a) - r*r; double D = B*B - A*C;
  if (D < -EPS) return ret;
  ret.PB(c+a+b*(-B+sqrt(D+EPS))/A);
  if (D > EPS)ret.PB(c+a+b*(-B-sqrt(D))/A);
  return ret;
}// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<Point> CircleCircleIntersection(Point a,Point b,double r,double R){
  vector<Point> ret; double d = sqrt(dist2(a, b));
  if (d > r+R || d+min(r, R) < max(r, R)) return ret;
  double x = (d*d-R*R+r*r)/(2*d); double y = sqrt(r*r-x*x);
  Point v = (b-a)/d; ret.PB(a+v*x + RotateCCW90(v)*y);
  if (y > 0) ret.PB(a+v*x - RotateCCW90(v)*y);
  return ret;
}// Computes the area/centroid of (possibly nonconvex) polygon,
// assuming that the coordinates are listed in a clockwise or
// anticlockwise fashion. Note: the centroid is often known as
// the "center of gravity" or "center of mass".
double ComputeSignedArea(const vector<Point> &p) {
  double area = 0;
  REP(i, SZ(p)){ int j = (i+1) % SZ(p);
    area += p[i].x*p[j].y - p[j].x*p[i].y;
  }return area / 2.0;
}double ComputeArea(const vector<Point> &p) {
  return fabs(ComputeSignedArea(p));
}Point ComputeCentroid(const vector<Point> &p) {
  Point c(0,0); double scale = 6.0 * ComputeSignedArea(p);
  REP(i, SZ(p)){ int j = (i+1) % SZ(p);
    c = c + (p[i]+p[j])*(p[i].x*p[j].y - p[j].x*p[i].y);
  }return c / scale;
}// tests if a given polygon (in CW/CCW order) is simple
bool IsSimple(const vector<Point> &p) {
  REP(i, SZ(p)) FOR(k, i + 1, SZ(p)){
    int j = (i+1) % SZ(p), l = (k+1) % SZ(p);
    if (i == l || j == k) continue;
    if (SegmentsIntersect(p[i], p[j], p[k], p[l]))
      return false;
  }return true;}
#define sqr(x) (x)*(x)
#define REMOVE_REDUNDANT
CT area2(Point a,Point b,Point c){return cross(b-a,c-a);}//2*A
#ifdef REMOVE_REDUNDANT
bool between(Point &a,Point &b,Point &c){// b is between a & c
  return EQ(area2(a, b, c),0) && (a.x-b.x)*(c.x-b.x) <= 0 
    && (a.y-b.y)*(c.y-b.y) <= 0;}
#endif
void ConvexHull(vector<Point> &pts) {
  sort(ALL(pts));pts.erase(unique(ALL(pts)), pts.end());
  vector<Point> up, dn;
  REP(i, SZ(pts)) {
    while(SZ(up)>1&&area2(up[SZ(up)-2],up.back(),pts[i])>=0) 
      up.pop_back();
    while(SZ(dn)>1&&area2(dn[SZ(dn)-2],dn.back(),pts[i])<=0) 
      dn.pop_back();
    up.PB(pts[i]);dn.PB(pts[i]);
  }pts = dn;
  for (int i = (int) SZ(up) - 2; i >= 1; i--) pts.PB(up[i]);
#ifdef REMOVE_REDUNDANT
  if (SZ(pts) <= 2) return;
  dn.clear();dn.PB(pts[0]);dn.PB(pts[1]);
  FOR(i, 2, SZ(pts)){
    if(between(dn[SZ(dn)-2],dn[SZ(dn)-1],pts[i]))dn.pop_back();
    dn.PB(pts[i]);}
  if (SZ(dn) >= 3 && between(dn.back(), dn[0], dn[1])) {
    dn[0] = dn.back();dn.pop_back();
  }pts = dn;
#endif}//returns (B-A)X(C-A)
#define Det(a,b,c) ((b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x)) 
bool in_convex(vector<Point>& l, Point p){
  int a = 1, b = SZ(l)-1, c;
  if (Det(l[0], l[a], l[b]) > 0) swap(a,b);
  // orientation of area, a is above 0 and b below 0
  // Allow on edge --> if (Det... > 0 || Det ... < 0)
  if(Det(l[0],l[a],p)>=0||Det(l[0],l[b],p)<=0)return false;
  while(abs(a-b) > 1) {c = (a+b)/2;
    if (Det(l[0], l[c], p) > 0)b = c; else a = c;
  }// Alow on edge --> return Det... <= 0
  return Det(l[a], l[b], p) <= 0;}
#define line pair<Point,Point>
#define NEED3RDTANGENT
// need to be careful when tangent has single common point with
// both circles specially when one cricle lies inside other
vector<line> find_tangent(Point a, Point b, CT r1, CT r2) {
  vector<line> Q;if(dist2(a, b) <= sqr(r1 - r2))return Q;
  int f = 0; if(r2 > r1) swap(a, b), swap(r1, r2), f = 1;
  if(abs(r2 - r1) <= EPS) {
    line m=Perpendicularline(a,b,a),n=Perpendicularline(a,b,b);
    vector<Point> l1 = CircleLineIntersection(m.F, m.S, a, r1),
      l2 = CircleLineIntersection(n.F, n.S, b, r2);
    assert(SZ(l1) == 2 && SZ(l2) == 2);
    if(cross(b-a,l1[0]-b)*cross(b-a,l2[0]-b)<0)swap(l2[0],l2[1]);
    Q.PB(MP(l1[0], l2[0]));Q.PB(MP(l1[1], l2[1]));
  } else {Point out = (b * r1 - a * r2) / (r1 - r2);
    assert(dist2(out, a) >= r1 && dist2(out, b) >= r2);
    vector<Point> l1 = CircleCircleIntersection(a, out, r1,
        sqrt(dist2(out, a) - sqr(r1))),
      l2 = CircleCircleIntersection(b, out, r2,
          sqrt(dist2(out, b) - sqr(r2)));
    assert(SZ(l1) == 2 && SZ(l2) == 2);
    if(cross(b-a,l1[0]-b)*cross(b-a,l2[0]-b)<0)swap(l2[0],l2[1]);
    Q.PB(MP(l1[0], l2[0]));Q.PB(MP(l1[1], l2[1]));
  }if (dist2(a, b) > sqr(r1 + r2) + EPS) {
    Point out = (b * r1 + a * r2) / (r1 + r2);
    assert(dist2(out, a) >= r1 && dist2(out, b) >= r2);
    vector<Point> l1 = CircleCircleIntersection(a, out, r1,
        sqrt(dist2(out, a) - sqr(r1))),
      l2 = CircleCircleIntersection(b, out, r2,
          sqrt(dist2(out, b) - sqr(r2)));
    assert(SZ(l1) == 2 && SZ(l2) == 2);
    if(cross(b-a,l1[0]-b)*cross(b-a,l2[0]-b)>0)swap(l2[0], l2[1]);
    Q.PB(MP(l1[0], l2[0])); Q.PB(MP(l1[1], l2[1]));
  } else if (abs(sqr(r1 + r2) - dist2(a, b)) < EPS) {
#ifdef NEED3RDTANGENT
    Point out = (b * r1 + a * r2) / (r1 + r2);
    Q.PB(Perpendicularline(a, b, out));
#endif}
    if (f == 1) {REP(i, Q.size()) swap(Q[i].F, Q[i].S);}
    return Q;}
