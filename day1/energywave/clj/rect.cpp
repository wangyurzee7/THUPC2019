#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<(n);i++)
#define mp make_pair
#define fi first
#define se second
#define pb push_back

typedef long double db;

const db EPS = 1e-8;

int sign(db x) { return x < -EPS ? - 1 : x > EPS; }

struct Rect{
    db low[3],up[3];

    void read(int n){

        rep(i,0,3) low[i] = 1e100, up[i] = -1e100;

        rep(_,0,n){
            int x,y,z; cin>>x>>y>>z;
            db cur[] = {x,y,z};
            rep(i,0,3) low[i] = min(low[i],cur[i]), up[i] = max(up[i],cur[i]);
        }

        //rep(i,0,3) cout<<low[i]<<" "<<up[i]<<endl;
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

int mB;

Rect B[5];

Rect Bsubset[1<<5];

Rect A;

db v[3];

vector<db> calc_event(db cur, db nxt, db v){
    if(sign(v) == 0) return {};
    return { (nxt - cur) / v };
}

db calc_intersect(db t){
    db ret = 0;

    Rect curA = A;
    rep(i,0,3) curA.low[i] += v[i] * t, curA.up[i] += v[i] * t;

    rep(mask,1,1<<mB){
        int sign = -1; rep(i,0,mB) if(mask>>i&1) sign *= -1;
        ret += intersect(curA,Bsubset[mask]).vol() * sign;
    }

    return ret;
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
    Poly ret(a.size() - 1);
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

db TOTAL_ERROR = 0;

db solve(db l,db r){
    //four points
    db x[4], y[4];
    rep(i,0,4) x[i] = l + (r-l)/3 * i, y[i] = calc_intersect(x[i]);

    Poly ret = {};

    rep(i,0,4){
        Poly tmp = {1};
        rep(j,0,4) if(i!=j){
            tmp = tmp * (Poly){-x[j],1};
            tmp = div(tmp,(x[i] - x[j]));
        }
        ret = ret + mul(tmp,y[i]);
    }

    rep(i,0,4) assert(sign(y[i] - eval(ret,x[i])) == 0);

    db test_x = l + (r - l) * 0.17;

    printf("%0.10f %0.10f\n",(double)calc_intersect(test_x),(double)eval(ret,test_x));
    printf("%0.10f\n",(double)abs(calc_intersect(test_x) - eval(ret,test_x)));

    TOTAL_ERROR += abs(calc_intersect(test_x) - eval(ret,test_x));

    return calc_integral(ret,l,r);
}

int main() {
    cin>>mB;
    rep(i,0,mB){
        int _;cin>>_;B[i].read(_);
    }

    int _;cin>>_;
    A.read(_);

    rep(i,0,3) cin>>v[i];

    rep(mask,1,1<<mB){
        int one = 0; rep(i,0,mB) if(mask>>i&1) one = i;
        if(mask == (1<<one))
            Bsubset[mask] = B[one];
        else
            Bsubset[mask] = intersect(Bsubset[mask - (1<<one)], B[one]);
    }

    //moving A with speed v
    vector<db> is = {0.0};

    rep(_,0,mB)rep(cor,0,3){
        rep(a,0,2) rep(b,0,2)
            for(auto i : calc_event( a?A.up[cor]:A.low[cor], b?B[_].up[cor]:B[_].low[cor], v[cor] ) )
                if(sign(i) > 0)
                    is.pb(i);
    }

    db ans = 0;

    sort(is.begin(), is.end());
    int cnt = 1;
    rep(i,1,is.size())
        if(is[i] > is[cnt-1] + EPS)
            is[cnt++] = is[i];
    is.resize(cnt);

//    cout<<cnt<<endl;

    rep(i,0,is.size() - 1)
        ans += solve(is[i],is[i+1]);

    printf("%0.10lf\n",(double) ans);
    printf("%0.10lf\n",(double) TOTAL_ERROR);
    fprintf(stderr, "%0.10lf\n",(double) ans);
    fprintf(stderr, "%0.10lf\n",(double) TOTAL_ERROR);

    rep(i,0,30){
        printf("%d: %0.10lf\n", i, (double) calc_intersect(1.0*i));
    }
    return 0;
}