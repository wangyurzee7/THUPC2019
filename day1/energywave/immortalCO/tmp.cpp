#include <bits/stdc++.h>
using namespace std;

namespace __main__ {
	using db = double;
	#define eps 1e-9
	#define pi 3.1415926535987932384626

	constexpr int sgn(db a) {return a < -eps ? -1 : a > eps;}
	constexpr int cmp(db a, db b) {return sgn(a - b);}
	inline void cmin(db& a, db b) {(a > b) ? a = b, 1 : 0;}
	inline void cmax(db& a, db b) {(a < b) ? a = b, 1 : 0;}

	struct P {
		db x, y;

		inline P operator + (const P& p) const {return {x + p.x, y + p.y};}
		inline P operator - (const P& p) const {return {x - p.x, y - p.y};}
		inline P operator * (db d) const {return {x * d, y * d};}
		inline P operator / (db d) const {return {x / d, y / d};}
		inline bool operator < (const P& p) const {
			if(cmp(x, p.x)) return x < p.x;
			return cmp(y, p.y) == -1;
		}
		inline db operator / (const P& p) const {return x * p.y - y * p.x;}

	};

	struct L {
		P p[2];
	};

	db cro3(const P& a, const P& b, const P& c) {return (b - a) / (c - a);}

	struct P3 {
		db x, y, z;
		inline db& d(int t) {return ((db*) this)[t];}

		#define opr2(ret, name) inline ret operator name (const P3& p) const
		opr2(P3, +) {return {x + p.x, y + p.y, z + p.z};}
		opr2(P3, -) {return {x - p.x, y - p.y, z - p.z};}
		opr2(db, *) {return x * p.x + y * p.y + z * p.z;}
		opr2(P3, /) {return {y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x}; }
		opr2(bool, <) {
			if(cmp(x, p.x)) return x < p.x;
			if(cmp(y, p.y)) return y < p.y;
			return cmp(z, p.z) == -1;
		}

		#define oprn(name) inline P3 operator name (db t) const
		oprn(*) {return {x * t, y * t, z * t}; }
		oprn(/) {return {x / t, y / t, z / t};}

		db len2() const {return x * x + y * y + z * z;}
		db len() const {return sqrt(len2());}
		P3 norm() const {return *this / len();}
		P3 operator - () const {return {-x, -y, -z};}

		void F() {cin >> x >> y >> z;}
	};

	using VP = vector<P>;
	using VP3 = vector<P3>;
	using VVP3 = vector<VP3>;

	void print(VVP3 &V) {
		for(int i = 0; i < (int)V.size(); ++i) {
			printf("[%d] : ", i);
			for(auto b : V[i]) printf("(%.4lf, %.4lf, %.4lf) ", (double)b.x,(double)b.y,(double)b.z);
			puts("");
		}
	}

	struct R {
		db min[3], max[3];

		void init(VVP3 &A) {
			min[0] = min[1] = min[2] = 1e100;
			max[0] = max[1] = max[2] = -1e100;

			for(auto& a : A) for(auto &p : a) {
				cmin(min[0], p.x); cmax(max[0], p.x);
				cmin(min[1], p.y); cmax(max[1], p.y);
				cmin(min[2], p.z); cmax(max[2], p.z);
			}
		}
		db vol() {
			if(max[0] <= min[0] + eps 
			|| max[1] <= min[1] + eps 
			|| max[2] <= min[2] + eps) return 0;
			return (max[0] - min[0]) * (max[1] - min[1]) * (max[2] - min[2]);
		}
		R inter(R B) const {
			cmax(B.min[0], min[0]); cmin(B.max[0], max[0]);
			cmax(B.min[1], min[1]); cmin(B.max[1], max[1]);
			cmax(B.min[2], min[2]); cmin(B.max[2], max[2]);
			return B;
		}
	};

	db vol(const P3& b, const P3& c, const P3& d) {
		return ((b) / (c)) * (d);
	}
	db vol(const P3& a, const P3& b, const P3& c, const P3& d) {
		return vol(b - a, c - a, d - a);
	}

	

	int B;
	VVP3 bpla[5], bplasub[32];
	VP3 bpts[5];
	R brectsub[32];

	VVP3 wpla;
	VP3 wpts;
	P3 v;

	db rand01() {
		return db(rand()) / RAND_MAX;
	}

	struct ConvexHull3 {
		int N;
		set< pair<int, int> > E;
		VVP3 ret;
		VP3 p, q;

		void wrap(int a, int b) {
			if(E.count({a, b})) return;
			int c = -1;
			for(int i = 0; i < N; ++i) 
				if(i != a && i != b 
					&& (c == -1 || sgn(vol(q[c], q[a], q[b], q[i])) == 1))
					c = i;
			if(c != -1) {
				ret.push_back({p[a], p[b], p[c]});
				E.insert({a, b}); E.insert({b, c}); E.insert({c, a});
				wrap(c, b); wrap(a, c);
			}
		}
		VVP3 work(VP3 a) {
			p = q = a; N = a.size();
			ret.clear(); E.clear();  
			for(auto& i : q) i = i + ((P3) {rand01(), rand01(), rand01()}) * 1e-4;
			for(int i = 1; i < N; ++i) if(q[i].x < q[0].x) {swap(p[0], p[i]); swap(q[0], q[i]);}
			for(int i = 2; i < N; ++i) 
				if((q[i].x - q[0].x) * (q[1].y - q[0].y) > (q[i].y - q[0].y) * (q[1].x - q[0].x))
					{swap(q[1], q[i]); swap(p[1], p[i]);}
			wrap(0, 1);
			return ret;
		}
	}	CH3;

	VP CH2(VP a) {
		int n = a.size();
		if(n <= 1) return a;
		sort(a.begin(), a.end());
		VP s; unsigned lim = 1;
		for(auto &p : a) {
			while(s.size() > lim && sgn(cro3(s[s.size() - 2], s.back(), p)) <= 0) s.pop_back();
			s.push_back(p);
		}
		a.pop_back(); reverse(a.begin(), a.end());
		lim = s.size();
		for(auto &p : a) {
			while(s.size() > lim && sgn(cro3(s[s.size() - 2], s.back(), p)) <= 0) s.pop_back();
			s.push_back(p);
		}
		s.pop_back();
///*bgg*/printf("ch2 ans = "); for(auto a : s) printf("(%.4lf, %.4lf) ", a.x,a.y); puts("");
		return s;
	}

	VP3 CH2(VP3 p, P3 o) {
///*bgg*/assert(!cmp(o.len2(), 1));
///*bgg*/#warning FIX MAGIC NUMBER
		P3 x = (((P3) {(db) rand(), (db) rand(), (db) rand()}).norm() / o).norm();
		P3 y = (x / o).norm();
		P3 v = o * (p[0] * o);

		vector<P> q;
		for(auto &P : p) q.push_back({P * x, P * y});
///*bgg*/printf("ch2 o = (%.4lf, %.4lf, %.4lf) ans = ", o.x, o.y, o.z); for(auto a : q) printf("(%.4lf, %.4lf, %.4lf) ", a.x,a.y,0.0); puts("");
		q = CH2(q);
		p.clear();
		for(auto &P : q) p.push_back(x * P.x + y * P.y + v);
		return p;
	}
	VVP3 process(const VVP3 p) {
		map<P3, VP3> mp;
		for(auto &ps : p) {
			P3 o = ((ps[1] - ps[0]) / (ps[2] - ps[0])).norm();
///*bgg*/printf("o = (%.4lf, %.4lf, %.4lf)\n", o.x, o.y, o.z);
			for(auto &i : ps) mp[o].push_back(i);
		}
		VVP3 ret;
		for(auto &v : mp) ret.push_back(CH2(v.second, -v.first));
		return ret;
	}

	void read(int N, VP3 &pts) {
		P3 p; while(N--) {p.F(); pts.push_back(p);}
	}
	void read(VVP3& pla, VP3& pts) {
		int n; cin >> n;
		read(n, pts);
		pla = CH3.work(pts);
		pla = process(pla);
///*bgg*/printf("read pla\n"); print(pla);	
	}

	pair<P3, P3> face(VP3 p) {
///*bgg*/assert(p.size() > 3u);
		return {p[0], ((p[1] - p[0]) / (p[2] - p[0])).norm()};
	}

	pair<P3, bool> isFL(const P3& p, const P3& o, const P3& q1, const P3& q2) {
		db a = (q2 - p) * o, b = (q1 - p) * o;
		db d = a - b;
		if(fabs(d) < eps) return {p, 0};
		return {(q1 * a - q2 * b) / d, 1};
	}

	VVP3 cut(VVP3 A, P3 p, P3 o) {
		VVP3 ret; VP3 S;
		for(auto &a : A) {
			int n = a.size();
			VP3 b; 
			bool diff = 0;
			for(int i = 0; i < n; ++i) {
				int d1 = sgn(o * (a[i] - p));
				int d2 = sgn(o * (a[(i + 1) % n] - p));
				if(d1 >= 0) b.push_back(a[i]);
				if(d1 * d2 < 0) {
					P3 q = isFL(p, o, a[i], a[(i + 1) % n]).first;
					b.push_back(q);
					S.push_back(q);
				}
				if(!d1) S.push_back(a[i]); else diff = 1;
				diff |= o * ((a[(i + 1) % n] - a[i]) / (a[(i + 1) % n] - a[i])).norm() < -eps;
			}
			if(b.size() >= 3u && diff) ret.push_back(b);
		}
		if(S.size()) {
			S = CH2(S, o);
			if(S.size() >= 3u) ret.push_back(S);
		}
		if(ret.size() < 4u) ret.clear();
		return ret;
	}

	VVP3 CH3inter(VVP3 A, VVP3 B) {
		if(A.empty() || B.empty()) return {};
		for(auto& f : B) {
			auto w = face(f);
			A = cut(A, w.first, -w.second);
			if(A.empty()) break;
		}
		return A;
	}

	VP3 points(VVP3 &a) {
		VP3 ret;
		for(auto &b : a) for(auto &p : b) ret.push_back(p);
		return ret;
	}

	vector<db> inter_pts_pla(const P3& p1, const P3& q1, const P3& qo, const P3& v) {
		db mv = (v * qo); if(!sgn(mv)) return {};
		return {((q1 - p1) * qo) / mv};
	}
	vector<db> inter_ln_ln(const P3& p1, const P3& p2, const P3& q1, const P3& q2, const P3& v) {
		P3 dp = (p2 - p1).norm();
		P3 dq = (q2 - q1).norm();
		P3 o = (p2 - p1) / v;

		if(!sgn(o.len2())) return {};

		o = o.norm();
		P3 o2 = dp / dq;
		if(!sgn(o2.len2())) {
			// if(!sgn(q1 * o - p1 * o) && !sgn(q2 * o - p1 * o)) {
			if(!sgn((q1 - p1) * o) && !sgn((q2 - p1) * o)) {
				P3 d = (o / v).norm();
				db x = d * (q1 - p1);
				db f = v * d;
				if(sgn(f)) return {x / f};
			};
		} else {
			o2 = o2.norm();
			db f = v * o2;
			if(sgn(f)) return {(q1 - p1) * o2 / f};
		}
		return {};
	}

	void calc(const VVP3& AP, const VP3 &A, const VVP3& BP, const VP3& B, P3 v, vector<db>& cut) {
		for(auto a : A) for(auto f : BP) {
			auto t = face(f);
			for(auto x : inter_pts_pla(a, t.first, t.second, v)) if(x > 0) cut.push_back(x);
		}
		for(auto a : B) for(auto f : AP) {
			auto t = face(f);
			for(auto x : inter_pts_pla(a, t.first, t.second, v)) if(x > 0) cut.push_back(x);
		}
		for(auto fA : AP) for(auto fB : BP)
			for(int i = 0; i < (int) fA.size(); ++i)
				for(int j = 0; j < (int) fB.size(); ++j) 
					for(auto x : inter_ln_ln(fA[i], fA[(i + 1) % fA.size()],
											fB[j], fB[(j + 1) % fB.size()], v))
						if(x > 0) cut.push_back(x);
		
	}

	db vol(VVP3 a) {
		if(a.empty()) return 0;
		a = process(a);
		P3 p = a[0][0];
		db v = 0;
		for(auto b : a) for(int i = 2; i < (int) b.size(); ++i)
			v += fabs(vol(p, b[0], b[i - 1], b[i]));
		return v / 6;
	}

	db calc(db t) {
///*bgg*/printf("calc t = %.4lf\n", t);
		VVP3 w = wpla;
		for(auto &f : w) for(auto &i : f) i = i + v * t;
		__main__::R R; R.init(w);

		db ans = 0;
		for(int s = 1; s < (1 << B); ++s) if(bplasub[s].size()) {
			if(R.inter(brectsub[s]).vol() <= eps) continue;
			db tmp = (__builtin_parity(s) ? 1 : -1) * vol(CH3inter(w, bplasub[s]));
			ans += tmp;
///*bgg*/printf("    tmp[%d] = %.4lf\n",s, tmp);		
		}
		return ans;
	}
	

	void __main__() {
		cin >> B;
		for(int i = 0; i < B; ++i) read(bpla[i], bpts[i]);
		read(wpla, wpts);
		v.F();

		vector<db> cut = {0.0};
		for(int s = 1; s < (1 << B); ++s) {
			int p = __builtin_ctz(s);
			if(s == (1 << p)) bplasub[s] = bpla[p];
			else bplasub[s] = CH3inter(bplasub[s - (1 << p)], bpla[p]);
			brectsub[s].init(bplasub[s]);
			calc(wpla, wpts, bplasub[s], points(bplasub[s]), v, cut);
		}
		sort(cut.begin(), cut.end());
		cut.erase(unique(cut.begin(), cut.end(), [] (db a, db b) {return !cmp(a, b);}), cut.end());
		
		db ans = 0;
		db pre = calc(cut[0]);
		for(int i = 0; i + 1 < (int) cut.size(); ++i) {
			double l = cut[i], r = cut[i + 1];
			double cur = calc(r), mid = calc((l + r) / 2);
			ans += (pre + cur + 4 * mid) / 6 * (r - l);
			pre = cur;
		}
		printf("%.8lf\n", (double) ans);

	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	__main__::__main__();
}