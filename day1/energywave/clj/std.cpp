#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<(n);i++)
#define mp make_pair
#define fi first
#define se second
#define pb push_back

typedef long double db;

const db EPS = 1e-9;

const db pi = acos(-1.0);
  
inline int sign(db a) { return a < -EPS ? -1 : a > EPS; }
  
inline int cmp(db a, db b){ return sign(a-b); }
  
struct P {
    db x, y;
    P() {}
    P(db _x, db _y) : x(_x), y(_y) {}
    P operator+(P p) { return {x + p.x, y + p.y}; }
    P operator-(P p) { return {x - p.x, y - p.y}; }
    P operator*(db d) { return {x * d, y * d}; }
    P operator/(db d) { return {x / d, y / d}; }
 
    bool operator<(P p) const { 
        int c = cmp(x, p.x);
        if (c) return c == -1;
        return cmp(y, p.y) == -1;
    }
 
    bool operator==(P o) const{
        return cmp(x,o.x) == 0 && cmp(y,o.y) == 0;
    }
 
    db dot(P p) { return x * p.x + y * p.y; }
    db det(P p) { return x * p.y - y * p.x; }
     
    db distTo(P p) { return (*this-p).abs(); }
    db alpha() { return atan2(y, x); }
    void read() { cin>>x>>y; }
    void write() {cout<<"("<<x<<","<<y<<")"<<endl;}
    db abs() { return sqrt(abs2());}
    db abs2() { return x * x + y * y; }
    P rot90() { return P(-y,x);}
    P unit() { return *this/abs(); }
    int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }
    P rot(db an){ return {x*cos(an)-y*sin(an),x*sin(an) + y*cos(an)}; }
};
  
struct L{ //ps[0] -> ps[1]
    P ps[2];
    P& operator[](int i) { return ps[i]; }
    P dir() { return ps[1] - ps[0]; }
    bool include(P p) { return sign((ps[1] - ps[0]).det(p - ps[0])) > 0; }
    L push(){ // push eps outward
        const double eps = 1e-6;
        P delta = (ps[1] - ps[0]).rot90().unit() * eps;
        return {ps[0] - delta, ps[1] - delta};
    }
};
  
#define cross(p1,p2,p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))
  
bool chkLL(P p1, P p2, P q1, P q2) {
    db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return sign(a1+a2) != 0;
}
 
P isLL(P p1, P p2, P q1, P q2) {
    db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}
  
P isLL(L l1,L l2){ return isLL(l1[0],l1[1],l2[0],l2[1]); }
  
bool intersect(db l1,db r1,db l2,db r2){
    if(l1>r1) swap(l1,r1); if(l2>r2) swap(l2,r2); 
    return !( cmp(r1,l2) == -1 || cmp(r2,l1) == -1 );
}
  
bool isSS(P p1, P p2, P q1, P q2){
    return intersect(p1.x,p2.x,q1.x,q2.x) && intersect(p1.y,p2.y,q1.y,q2.y) && 
    crossOp(p1,p2,q1) * crossOp(p1,p2,q2) <= 0 && crossOp(q1,q2,p1)
            * crossOp(q1,q2,p2) <= 0;
}
  
bool isSS_strict(P p1, P p2, P q1, P q2){
    return crossOp(p1,p2,q1) * crossOp(p1,p2,q2) < 0 && crossOp(q1,q2,p1)
            * crossOp(q1,q2,p2) < 0;
}
  
bool isMiddle(db a, db m, db b) {
    return sign(a - m) == 0 || sign(b - m) == 0 || (a < m != b < m);
}
  
bool isMiddle(P a, P m, P b) {
    return isMiddle(a.x, m.x, b.x) && isMiddle(a.y, m.y, b.y);
}
  
bool onSeg(P p1, P p2, P q){
    return crossOp(p1,p2,q) == 0 && isMiddle(p1, q, p2);
}
 
bool onSeg_strict(P p1, P p2, P q){
    return crossOp(p1,p2,q) == 0 && sign((q-p1).dot(p1-p2)) * sign((q-p2).dot(p1-p2)) < 0;
}
  
P proj(P p1, P p2, P q) {
    P dir = p2 - p1;
    return p1 + dir * (dir.dot(q - p1) / dir.abs2());
}
  
P reflect(P p1, P p2, P q){
    return proj(p1,p2,q) * 2 - q;
}
  
db nearest(P p1,P p2,P q){
    P h = proj(p1,p2,q);
    if(isMiddle(p1,h,p2))
        return q.distTo(h);
    return min(p1.distTo(q),p2.distTo(q));
}
  
db disSS(P p1, P p2, P q1, P q2){
    if(isSS(p1,p2,q1,q2)) return 0;
    return min(min(nearest(p1,p2,q1),nearest(p1,p2,q2)), min(nearest(q1,q2,p1),nearest(q1,q2,p2)) );
}
  
db rad(P p1,P p2){
    return atan2l(p1.det(p2),p1.dot(p2));
}
  
db incircle(P p1, P p2, P p3){
    db A = p1.distTo(p2);
    db B = p2.distTo(p3);
    db C = p3.distTo(p1);
    return sqrtl(A*B*C/(A+B+C));
}
  
//polygon
  
db area(vector<P> ps){
    db ret = 0; rep(i,0,ps.size()) ret += ps[i].det(ps[(i+1)%ps.size()]); 
    return ret/2;
}
  
int contain(vector<P> ps, P p){ //2:inside,1:on_seg,0:outside
    int n = ps.size(), ret = 0; 
    rep(i,0,n){
        P u=ps[i],v=ps[(i+1)%n];
        if(onSeg(u,v,p)) return 1;
        if(cmp(u.y,v.y)<=0) swap(u,v);
        if(cmp(p.y,u.y) >0 || cmp(p.y,v.y) <= 0) continue;
        ret ^= crossOp(p,u,v) > 0;
    }
    return ret*2;
}
  
vector<P> convexHull(vector<P> ps) {
    int n = ps.size(); if(n <= 1) return ps;
    sort(ps.begin(), ps.end());
    vector<P> qs(n * 2); int k = 0;
    for (int i = 0; i < n; qs[k++] = ps[i++]) 
        while (k > 1 && crossOp(qs[k - 2], qs[k - 1], ps[i]) <= 0) --k;
    for (int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--])
        while (k > t && crossOp(qs[k - 2], qs[k - 1], ps[i]) <= 0) --k;
    qs.resize(k - 1);
    return qs;
}

db sqr(db x){ return x*x; }

struct P3{
    db x,y,z;
    P3 operator+(P3 o){ return {x+o.x,y+o.y,z+o.z}; }
    P3 operator-(P3 o){ return {x-o.x,y-o.y,z-o.z}; }
    P3 operator-(){ return {-x,-y,-z}; }

    db operator*(P3 o){ return x*o.x+y*o.y+z*o.z; }
    P3 operator^(P3 o){ return {y*o.z-z*o.y,z*o.x-x*o.z,x*o.y-y*o.x}; }
    P3 operator*(db o){ return {x*o,y*o,z*o}; }
    P3 operator/(db o){ return {x/o,y/o,z/o}; }

    db abs2(){ return sqr(x) + sqr(y) + sqr(z); }
    db abs(){ return sqrt(abs2()); }

    P3 norm(){ return *this / abs(); } 
    bool operator<(P3 o) const{
        if(cmp(x,o.x) != 0) return x < o.x;
        if(cmp(y,o.y) != 0) return y < o.y;
        return cmp(z,o.z) == -1;
    }
    bool operator==(P3 o) const{
        return cmp(x,o.x) == 0 && cmp(y,o.y) == 0 && cmp(z,o.z) == 0;
    }
    void read(){
        cin>>x>>y>>z;
    }
    void print(){
        //printf("%lf,%lf,%lf\n",x,y,z);
    }
};

typedef vector<P3> VP;
typedef vector<VP> VVP;

struct Rect{
    db low[3],up[3];

    void read(VVP&A){
        rep(i,0,3) low[i] = 1e100, up[i] = -1e100;
        for(auto f:A) for(auto p:f){
            db cur[] = {p.x,p.y,p.z};
            rep(i,0,3) low[i] = min(low[i],cur[i]), up[i] = max(up[i],cur[i]);
        }
    }

    db vol(){
        db ret = 1.0;
        rep(i,0,3){
            if(sign(up[i] - low[i]) <= 0) return 0;
            ret *= up[i] - low[i];
        }
        return ret;
    }
};

Rect intersect(Rect A,Rect B){
    Rect ret;
    rep(i,0,3){
        ret.low[i] = max(A.low[i],B.low[i]);
        ret.up[i] = min(A.up[i],B.up[i]);
    }
    return ret;
}

db r;

db Acos(db x) {
    return acos(max(-(db)1,min(x,(db)1)));
}

db dist(P3 a,P3 b){// qiumian juli
    db r=Acos(a*b);
    return r;
}

vector<db> solve(db a,db b,db c) {
    // return cos(t)*a+sin(t)*b <= c
    // a=r*cos(th) b=r*sin(th)
    db r=sqrt(a*a+b*b);
    db th=atan2(b,a);
    // r*cos(t-th) <= c
    if (cmp(c,-r)==-1)  return {0}; // c < -r
    else if (cmp(r,c) <= 0) return {1}; // r <= c
    else {
        db tr=pi-Acos(c/r);     
        assert(tr < pi);
        return {th+pi-tr,th+pi+tr};
    }
}

P3 rnd;

vector<db> jiao(P3 a,P3 b){
    if (cmp(dist(a,b),2*r)>0) return {0};
    P3 rd=a*cos(r); P3 z=a.norm(); P3 y=(z^rnd).norm(); P3 x=(y^z).norm();
    // (rd+x*cos(t)+y*sin(t))*b >= cos(r)
    vector<db> ret = solve(-(x*b*sin(r)),-(y*b*sin(r)),-(cos(r)-rd*b)); 
    //return solve(-(x*b*sin(r)),-(y*b*sin(r)),-(cos(r)-rd*b));
    return ret;
}

db norm(db x){ //[0,2pi)
    while(x < 0) x+= 2*pi;
    while(x >= 2*pi) x-= 2*pi;
    return x;
}

db disLP(P3 p1,P3 p2,P3 q){
    return ((p2-p1)^(q-p1)).abs() / (p2-p1).abs();
}

db disLL(P3 p1,P3 p2,P3 q1,P3 q2){
    P3 o = (p2-p1) ^ (q2-q1); if(o.abs() <= EPS) return disLP(p1,p2,q1);
    return fabs(o.norm() * (p1-p2));
}

VP isFL(P3 p,P3 o,P3 q1,P3 q2){
    db a = (q2-p)*o, b = (q1-p)*o;
    db d = a - b;
    if(fabs(d) < EPS) return {};
    return {(q1*a-q2*b)/d};
}

VP isFF(P3 p1,P3 o1,P3 p2,P3 o2){
    P3 e = o1 ^ o2, v = o1 ^ e;
    db d = o2 * v; if(fabs(d) < EPS) return {};
    P3 q = p1 + v * (o2 * (p2-p1) / d);
    return {q,q+e};
}

db Volume(P3 a,P3 b,P3 c,P3 d){
    return ((b-a)^(c-a))*(d-a);
}

db rand_db(){
    return 1.0 * rand() / RAND_MAX;
}

namespace CH3{
    VVP ret;
    set<pair<int,int> > eg;
    int n;
    VP p,q;
    set<int> vt;

    void wrap(int a,int b){
        if (eg.find({a,b})==eg.end()){
            int c=-1;
            for (int i=0;i<n;i++)if (i!=a && i!=b){
                if (c==-1 || Volume(q[c],q[a],q[b],q[i])>0)
                    c=i;
            }
            if (c!=-1){
                ret.pb({p[a],p[b],p[c]});
                eg.insert({a,b});eg.insert({b,c});eg.insert({c,a});
                vt.insert(a);vt.insert(b);vt.insert(c);
                wrap(c,b);wrap(a,c);
            }
        }
    };

    VVP convexHull3d(VP _p){
        p = q = _p; n = p.size();
        ret.clear(); eg.clear();
        for(auto&i:q) i = i + (P3){rand_db()*1e-4,rand_db()*1e-4,rand_db()*1e-4};
        for (int i=1;i<n;i++)if (q[i].x<q[0].x)swap(p[0],p[i]),swap(q[0],q[i]);
        for (int i=2;i<n;i++)if (
            (q[i].x-q[0].x)*(q[1].y-q[0].y)>
            (q[i].y-q[0].y)*(q[1].x-q[0].x)) swap(q[1],q[i]),swap(p[1],p[i]);
        wrap(0,1);
        return ret;
    }

    VP convexHull3d_points(VP _p){
        p = q = _p; n = p.size();
        ret.clear(); eg.clear();
        vt.clear();
        for(auto&i:q) i = i + (P3){rand_db()*1e-4,rand_db()*1e-4,rand_db()*1e-4};
        for (int i=1;i<n;i++)if (q[i].x<q[0].x)swap(p[0],p[i]),swap(q[0],q[i]);
        for (int i=2;i<n;i++)if (
            (q[i].x-q[0].x)*(q[1].y-q[0].y)>
            (q[i].y-q[0].y)*(q[1].x-q[0].x)) swap(q[1],q[i]),swap(p[1],p[i]);
        wrap(0,1);

        VP new_p;
        for(auto i : vt) new_p.pb(p[i]);
        return new_p;
    }
}

VP convexHull2D(VP ps,P3 o){
    P3 x = {rand(),rand(),rand()}; x = x.norm();

    x = (x ^ o).norm(); P3 y = (x ^ o).norm();

    P3 vec = o.norm() * (ps[0] * o);

    vector<P> qs; for(auto p:ps) qs.pb({p*x,p*y}); qs = convexHull(qs);

    ps = {}; for(auto p : qs) ps.pb(x*p.x + y*p.y + vec);
    return ps;
}

VVP unite_tri(VVP pss){
    VVP ret;
    map<P3,VP> by_norm;
    for(auto ps:pss){
        P3 o = ((ps[1] - ps[0]) ^ (ps[2] - ps[0])).norm();
        for(auto i : ps) by_norm[o].pb(i);
    }
    for(auto it:by_norm) ret.pb(convexHull2D(it.se,it.fi));
    return ret;
}

pair<P3,P3> get_face(VP ps){
    return mp(ps[0],((ps[1]-ps[0])^(ps[2]-ps[0])).norm());
}

VVP convexCut(VVP pss, P3 p, P3 o){ // keep o*(x-p) >= 0
    VVP ret; VP sec;
    for(auto ps : pss){
        int n = ps.size();
        VP qs; bool dif = 0;
        rep(i,0,n){
            int d1 = sign(o*(ps[i]-p));
            int d2 = sign(o*(ps[(i+1)%n]-p));
            if(d1 >= 0) qs.pb(ps[i]);
            if(d1 * d2 < 0){
                P3 q = isFL(p,o,ps[i],ps[(i+1)%n])[0];
                qs.pb(q);
                sec.pb(q);
            }
            if(d1 == 0) sec.pb(ps[i]);
            else dif = 1;
            dif |= o * ((ps[(i+1)%n] - ps[i]) ^ (ps[(i+2)%n]-ps[i])) < -EPS;
        }
        if(qs.size() > 0 && dif) ret.pb(qs);
    }
    if(sec.size() > 0) ret.pb(convexHull2D(sec,o));

    if(ret.size() < 4) ret = {};

    return ret;
}

db vol(VVP pss){
    if(pss.empty()) return 0.0;

    pss = unite_tri(pss);

    P3 p = pss[0][0];
    db V = 0;
    for(auto ps : pss){
        rep(i,2,ps.size())
            V += fabs(Volume(p,ps[0],ps[i-1],ps[i]));
    }
    return V/6;
}

VP readVP(int n){
	VP ret;
	rep(i,0,n) {P3 p; p.read(); ret.pb(p); }
	return ret;
}


//global data

int mB; // at most 5

VVP BbodyPlane[5]; //3d convexhull plane
VP BbodyPoints[5]; //3d convexhull points

VVP BbodyPlaneSubSet[1<<5];
Rect BbodyRectSubset[1<<5];

VVP wavePlane;
VP wavePoints;

P3 v;

VVP intersectTwoConvexHull(VVP hA, VVP hB){
	if(hA.empty() || hB.empty()) return {};

	for(VP f : hB){
		auto w = get_face(f);
		hA = convexCut(hA,w.fi,-w.se);
	}
	return hA;
}

vector<db> calcIntersectTwoLines(P3 p1,P3 p2,P3 q1,P3 q2,P3 v){
	//<p1,p2> move along direction v, when they touch q1,q2

	P3 dp = (p2-p1).norm();
	P3 dq = (q2-q1).norm();

	P3 o = (p2-p1) ^ v;

	if(sign(o.abs()) == 0){//no move
		return {};
	}

	o = o.norm();

	P3 o2 = (dp ^ dq);

	if(sign(o2.abs()) == 0){ //parallel

		if(sign(q1*o - p1*o) == 0 && sign(q2*o - p1*o) == 0 ){
			//same plane
			P3 dir = (o ^ v).norm();
			db x = dir * (q1-p1);
            if(sign(v * dir) == 0) return {};
			return {x / (v * dir)};
		} else {
			return {};
		}
	} else {
		o2 = o2.norm();
        if(sign(v*o2) == 0) return {};
		return {( (q1 - p1) * o2 ) / (v * o2) };
	}
}

vector<db> calcIntersectPointAndPlane(P3 p1,P3 q1,P3 qo,P3 v){
	//move p1 along v , when intersect q1, qo
	db mv = (v * qo); if(sign(mv) == 0) return {};
	return {( (q1 - p1) * qo ) / mv};
}

//assume A is moving
db calc(db t){
	//for(auto&i : curWavePoints) i = i + v * t;

	VVP curWavePlane = wavePlane;
	for(auto&f : curWavePlane) for(auto&i:f) i = i + v * t;

	Rect R; R.read(curWavePlane);

	db ans = 0;
	rep(mask,1,1<<mB) if(!BbodyPlaneSubSet[mask].empty()){
		int sign = -1; rep(j,0,mB) if(mask>>j&1) sign *= -1;

		if(intersect(R,BbodyRectSubset[mask]).vol() <= EPS) continue;

		ans += sign * vol(intersectTwoConvexHull(curWavePlane,BbodyPlaneSubSet[mask]));
	}

	return ans;
}

typedef vector<db> Poly;

Poly operator*(Poly a,Poly b){
    Poly ret(a.size() + b.size() - 1, 0);
    rep(i,0,a.size()) rep(j,0,b.size())
        ret[i+j] += a[i] * b[j];
    return ret;
}

Poly operator+(Poly a,Poly b){
    if(a.size() < b.size()) swap(a,b);
    rep(i,0,b.size()) a[i] += b[i];
    return a;
}

Poly mul(Poly a, db x){
    for(auto&i : a) i *= x; return a;
}

Poly div(Poly a,db x){
    for(auto&i : a) i /= x; return a;
}

Poly D(Poly a){
    Poly ret(a.size() - 1, 0);
    rep(i,1,a.size()) ret[i-1] += a[i] * i;
    return ret;
}

db eval(Poly a, db x){
    db ret = 0;
    for(int i = a.size() - 1; i >= 0; --i)
        ret =  ret * x + a[i];
    return ret;
}

Poly integral(Poly a){
	Poly ret(a.size() + 1, 0);
	rep(i,0,a.size())
		ret[i+1] += a[i] / (i + 1);
	return ret;
}

vector<db> solve_two(db a,db b,db c){
    //ax^2+bx+c == 0
    if(sign(a) == 0){
        if(sign(b)) return {-c/b};
        else return {};
    } else {
        db del = b*b - 4 * a * c;
        if(sign(del) < 0) return {};
        del = max(del, (db)0);
        return {(-b-sqrt(del))/(2*a),(-b+sqrt(del))/(2*a)};
    }
}

db calc_integral(Poly a,db l,db r){
	Poly I = integral(a);
	return eval(I,r) - eval(I,l);
}

db solve(db l,db r){

    //four points
    db x[4], y[4];
    rep(i,0,4) {
        x[i] = l + (r-l)/3 * i; 
        y[i] = calc(x[i]);
        //cout<<y[i]<<endl;
    }

    Poly ret = {};

    rep(i,0,4){
        Poly tmp = {1};
        rep(j,0,4) if(i!=j){
            tmp = tmp * (Poly){-x[j],1};
            tmp = div(tmp,(x[i] - x[j]));
        }
        ret = ret + mul(tmp,y[i]);
    }

    //cout<<"-------------"<<endl;
    //for(auto i : ret) cout<<i<<" ";cout<<endl;

    //rep(i,0,4) {
        //cout<<y[i]<<" "<<eval(ret,x[i])<<endl;
        //assert(sign(y[i] - eval(ret,x[i])) == 0);
    //}

    return calc_integral(ret,l,r);
}

void readConvexBody(VVP&plane,VP&points){
	int n; cin>>n;
	points = readVP(n);
	plane = CH3::convexHull3d(points);
}

void calcInterestingTime(VVP&AP,VP&A,VVP&BP,VP&B,P3 v,vector<db>& is){
	//find all interesting time

	//point in A, plane in B
	for(auto pA : A)
		for(auto fB : BP){
			auto tmp = get_face(fB);
			for(auto x : calcIntersectPointAndPlane(pA,tmp.fi,tmp.se,v))
				if(x > 0)
					is.pb(x);
		}
		
	//line in A, line in B
	for(auto fA : AP)
		for(auto fB : BP){
			rep(i,0,fA.size())
				rep(j,0,fB.size())
					for(auto x : calcIntersectTwoLines(fA[i],fA[(i+1)%fA.size()],fB[j],fB[(j+1)%fB.size()],v))
						if(x > 0)
							is.pb(x);
		}

	//plane in A, point in B
	for(auto pB : B)
		for(auto fA : AP){
			auto tmp = get_face(fA);
			for(auto x :calcIntersectPointAndPlane(pB,tmp.fi,tmp.se,-v))
				if(x > 0)
					is.pb(x);
		}
}

int main() {
//	freopen("in","r",stdin);

	cin>>mB;

	rep(i,0,mB) {
		readConvexBody(BbodyPlane[i],BbodyPoints[i]);
	}

	readConvexBody(wavePlane,wavePoints);

 	v.read();

 	rep(mask,1,1<<mB){
 		int one = -1; rep(i,0,mB) if(mask>>i&1) one = i;

 		if(mask != (1<<one)) BbodyPlaneSubSet[mask] = intersectTwoConvexHull(BbodyPlaneSubSet[mask - (1<<one)],BbodyPlane[one]);
 		else BbodyPlaneSubSet[mask] = BbodyPlane[one];

 		BbodyRectSubset[mask].read(BbodyPlaneSubSet[mask]);
 	}

	vector<db> is;

	rep(i,0,mB){
		calcInterestingTime(wavePlane,wavePoints,BbodyPlane[i],BbodyPoints[i],v,is);
	}

	is.pb(0);
	sort(is.begin(), is.end());
    int cnt = 1;
    rep(i,1,is.size())
        if(is[i] > is[cnt-1] + EPS)
            is[cnt++] = is[i];
    is.resize(cnt);

//    cout<<cnt<<endl;

/*
    printf("is:\n");
    for(auto x : is)
    	printf("%0.5f\n",(double)x);
*/
    db ans = 0;

	rep(i,0,is.size() - 1){
		db l = is[i], r = is[i + 1];
        ans += solve(l,r);
	}


	printf("%0.10f\n",(double)ans);

/*
	printf("DEBUG\n");
	db l = is[0], r = is.back();
	rep(i,0,100){
		db x = (l*(100-i) + r * i)/100;
		printf("%0.5f : %0.5f\n",(double)x,(double)calc(x));
	}
*/
	return 0;
}