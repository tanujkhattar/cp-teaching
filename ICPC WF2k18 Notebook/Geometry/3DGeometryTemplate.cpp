#define eq(a,b) (fabs((a) - (b)) < EPS)
class point{
  public: double x,y,z;
    point(){x=y=z=0;}
    point(double _x,double _y,double _z=0):x(_x),y(_y),z(_z){}
    point(point &p){x=p.x;y=p.y;z=p.z;}
    bool operator == (point p) const{return eq(x,p.x) && eq(y,p.y) && eq(z,p.z);}
    bool operator < (point p) const{
      if(eq(x,p.x) && eq(y,p.y)) return z<p.z;
      if(eq(x,p.x))return y<p.y; return x<p.x;
    }point operator + (point p) const {return point(x+p.x,y+p.y,z+p.z);}
    point operator - () const {return point(x-p.x,y-p.y,z-p.z);}
}null;point tovect(point a,point b){return point(b.x-a.x,b.y-a.y,b.z-a.z);}
point cross(point a,point b){return point(a.y*b.z - a.z*b.y , -(a.x*b.z-a.z*b.x) , a.x*b.y-b.x*a.y);
}double dot(point a,point b){return a.x*b.x + a.y*b.y + a.z*b.z;}
double scalarTripleProduct(point a,point b, point c){return dot(a,cross(b,c));}
double mod(point v){return sqrt(dot(v,v));}
point norm(point v){double d = mod(v);v.x/=d;v.y/=d;v.z/=d;return v;}
double angle(point a,point b){a = norm(a);b = norm(b);return acos(dot(a,b));}
//********** LINE ***************
class line{
  public: point a,b; line(){}
    line(point x ,point y):a(x),b(tovect(x,y)){}
};bool areParallel(line l1,line l2){
  return cross(l1.b,l2.b)==null && !(cross(point(l1.a,l2.a),l2.b) == null);
}bool areSame(line l1,line l2){
  return cross(l1.b,l2.b)==null && (cross(point(l1.a,l2.a),l2.b) == null);
}bool areIntersect(line l1,line l2){
  return !(cross(l1.b,l2.b)==null) && (fabs(scalarTripleProduct(point(l1.a,l2.a),l1.b,l2.b))<EPS);
}bool areIntersect(line l1,line l2,point& p1){
  if(!(cross(l1.b,l2.b)==null) && (fabs(scalarTripleProduct(point(l1.a,l2.a),l1.b,l2.b))<EPS)){
    point temp = cross(l2.b,l1.b);
    double k2 = dot(cross(point(l2.a,l1.a),l1.b),temp)/dot(temp,temp);
    p1 = point(l2.a.x + k2*l2.b.x , l2.a.y + k2*l2.b.y,l2.a.z + k2*l2.b.z);
    return true;}return false;
}bool areSkew(line l1,line l2){
  return !areParallel(l1,l2) && !areSame(l1,l2) && !areIntersect(l1,l2);
}/*************** PLANE **************/
class plane{ //point and normal vector
  public: point a,n; plane(){}
    plane(point _x,point _a,point _b){
      n = cross(_a,_b);a = _x;
      if(n == null)n = cross(tovect(_x,point(_a.x,_a.y,_a.z)),_b);
    }plane(line l1,line l2){a = l1.a;n = cross(l1.b,l2.b);
      if(n == null)n = cross(tovect(l1.a,l2.a),l1.b);
    }plane(plane & p){a = p.a;n = p.n;}
    plane(const plane & p){a = p.a;n = p.n;}
    bool operator == (plane p) const{
      return cross(n,p.n)==vect(0,0,0) && (fabs(dot(n,tovect(a,p.a)))<EPS);
    }bool operator < (plane p) const{
      if(cross(n,p.n)==null && fabs(dot(n,tovect(a,p.a)))<EPS)return false;
      if(a==p.a)return n<p.n;return a < p.a;}
};/****************Miscellaneous***********************/
// distance from point (x, y, z) to plane aX + bY + cZ + d = 0
double ptPlaneDist(double x, double y, double z,
    double a, double b, double c, double d){
  return abs(a*x + b*y + c*z + d) / sqrt(a*a + b*b + c*c);
}// distance from point (px, py, pz) to line (x1, y1, z1)-(x2, y2, z2)
// (or ray, or segment; in the case of the ray, the endpoint is the first point)
const int LINE = 0, SEGMENT = 1, RAY = 2;
double ptLineDistSq(double x1, double y1, double z1,
    double x2, double y2, double z2, double px, double py, double pz,
    int type){double pd2 = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2);
  double x,y,z; if(eq(pd2,0)){x = x1;y = y1;z = z1;} 
  else{ double u = ((px-x1)*(x2-x1) + (py-y1)*(y2-y1) + (pz-z1)*(z2-z1)) / pd2;
    x = x1 + u * (x2 - x1);y = y1 + u * (y2 - y1);z = z1 + u * (z2 - z1);
    if(type!=LINE && u < 0){x = x1;y = y1;z = z1;}
    if(type==SEGMENT && u > 1.0){x = x2;y = y2;z = z2;}
  }return (x-px)*(x-px) + (y-py)*(y-py) + (z-pz)*(z-pz);
}double ptLineDist(double x1, double y1, double z1,
    double x2, double y2, double z2, double px, double py, double pz,
    int type) {return sqrt(ptLineDistSq(x1, y1, z1, x2, y2, z2, px, py, pz, type));
}//projection of point p on plane A
point getProjection(point p,plane A){
  double a = A.n.x, b = A.n.y, c = A.n.z;
  double d = A.a.x, e = A.a.y, f = A.a.z;
  double t = (a*d - a*p.x + b*e - b*p.y + c*f - c*p.z)/(a*a + b*b + c*c);
  return point(p.x + t*a,p.y + t*b, p.z + t*c);
}//check if point p is in triangle A,B,C - 3D
bool ok(double x){return x>=0 && x<=1.0;}
bool inTriangle(point p,point A,point B,point C){
  double Area = mod(cross(tovect(A,B),tovect(A,C)));
  double alpha = mod(cross(tovect(p,B),tovect(p,C)))/Area;
  double beta = mod(cross(tovect(p,C),tovect(p,A)))/Area;
  double gamma = 1 - alpha - beta;
  return ok(alpha) && ok(beta) && ok(gamma);
}//rotate point A about axis B-->C by theta. C should be unit vector along the axis
point rotate(point A,point B,point C,double theta){
  double x = A.x, y = A.y, z = A.z;
  double a = B.x, b = B.y, c = B.z;
  double u = C.x, v = C.y, w = C.z;
  point ret;
  ret.x = (a*(sq(v)+sq(w)) - u*(b*v + c*w - u*x - v*y - w*z)) * (1 - cos(theta)) + x*cos(theta) + (-c*v + b*w - w*y + v*z)*sin(theta);
  ret.y = (b*(sq(u)+sq(w)) - v*(a*u + c*w - u*x - v*y - w*z)) * (1 - cos(theta)) + y*cos(theta) + (+c*u - a*w + w*x - u*z)*sin(theta);
  ret.z = (c*(sq(v)+sq(u)) - w*(a*u + b*v - u*x - v*y - w*z)) * (1 - cos(theta)) + z*cos(theta) + (-b*u + a*v - v*x + u*y)*sin(theta);
  return ret;}
