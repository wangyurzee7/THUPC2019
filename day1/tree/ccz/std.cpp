#include<bits/stdc++.h>
using std::max;
using std::min;
using std::vector;
void mins(int&a,int b){if(a>b)a=b;}
void maxs(int&a,int b){if(a<b)a=b;}
typedef long long i64;
const int N=1.1e5+7;
#define F(i,n) for(int i=0;i<(n);++i)
#define F3(i,l,r) for(int i=(l);i<(r);++i)
#define f0(a,n) memset((a),0,sizeof((a)[0])*(n))
char ib[1<<23],*ip=ib,ob[1<<22],*op=ob;
int read(){
	int x=0;
	while(*ip<48)++ip;
	while(*ip>47)x=x*10+*ip++-48;
	return x;
}
void print(i64 x){
	char ss[20];
	int sp=0;
	do ss[sp++]=x%10+48;while(x/=10);
	while(sp)*op++=ss[--sp];
	*op++=10;
}
int n,m,cur_q,B;
i64 ans[N];
vector<int>e[N];
int fa[N],sz[N],dep[N],son[N],top[N],*rs[N];
void* operator new(size_t n){
	static char* l=0,*r=0;
	if(r-l<n){
		int L=1<<24;
		l=(char*)malloc(L),r=l+L,f0(l,L);
	}
	r-=n;
	return r;
}
void operator delete(void*){}
struct Q{
	int d0,d1,qid,bid;
	void fix(){
		if(d0<d1)std::swap(d0,d1);
	}
	void fix(int m0,int m1){
		mins(d0,m0);
		mins(d1,m1);
	}
	bool operator<(const Q&x)const{
		if(bid!=x.bid)return bid<x.bid;
		if(d1!=x.d1)return (d1<x.d1)^(bid&1);
		return 0;
	}
};
struct Ans{
	i64 ans;
	int sz;
	void set(Ans&a,Ans&b,int d){
		ans=a.ans+b.ans+(i64)b.sz*d;
		sz=a.sz+b.sz;
	}
	void clr(){ans=0;sz=0;}
	void add(Ans&a,int d){
		ans+=a.ans+(i64)a.sz*d;
		sz+=a.sz;
	}
	i64 cal(Ans&a,int d){
		return ans*a.sz+(a.ans+(i64)a.sz*d)*sz;
	}
};
struct bfs{
	int **ls,*sz,n;
	i64 *ds[2];
	void init_ls(int size){
		ls=new int*[n+1];
		ls[0]=new int[size];
		F(i,n)ls[i+1]=ls[i]+sz[i];
		memcpy(rs,ls,sizeof(ls[0])*n);
	}
	void ins0(int a,bfs &x){
		F(i,x.n)sz[i+a]+=x.sz[i];
	}
	void ins(int a,bfs &x){
		F(i,x.n)F(j,x.sz[i])*rs[i+a]++=x.ls[i][j];
	}
	void init_ds0(){
		ds[0]=new i64[n];
		ds[0][0]=0;
		F3(i,1,n)ds[0][i]=ds[0][i-1]+(i64)i*sz[i];
	}
	void init(int size,int*d,int*d1,bfs&cl,bfs&cr){
		bfs*c[2]={&cl,&cr};
		n=1;
		F(i,2)maxs(n,c[i]->n+d[i]);
		sz=new int[n];
		F(i,2)ins0(d[i],*c[i]);
		init_ls(size);
		F(i,2)ins(d[i],*c[i]);
		init_ds0();
		if(!d1)return;
		ds[1]=new i64[n];
		F(i,2){
			bfs&cw=*c[i];
			F(j,cw.n){
				ds[1][d[i]+j]+=(i64)d1[i]*cw.sz[j]+cw.ds[1][j]-(j?cw.ds[1][j-1]:0);
			}
		}
		F3(i,1,n)ds[1][i]+=ds[1][i-1];
	}
	Ans get_ds(int t,int x){
		mins(x,n-1);
		return (Ans){ds[t][x],int(ls[x+1]-ls[0])};
	}
};
struct node;
namespace MO{
	Q qs1[N*3];
	i64 ans[N*2],s0[N],s1[N],s2[N];
	i64 a0[N],a1[N];
	int id[N],idp,fa[N],dep[N];
	int bid[N],bp,bp0,bfa[N],br[N],bdep[N];
	int id1[N*2];
	vector<node*>bs;
	void add(int x){
		int x0=bid[x];
		a1[x0]+=dep[x];
		for(int b=bfa[x0];b;b=bfa[b])a1[b]+=bdep[b],++s2[b];

		int l=br[x0-1]+1,r=br[x0]+1;
		for(;x;x=fa[x])++a0[x];
		F3(i,l,r)a0[i]+=a0[fa[i]],s0[i]+=a0[i];
		f0(a0+l,r-l);
	}
	void upd(){
		F3(i,1,bp0+1)s1[i]=s1[bfa[i]]+a1[i];
	}
	i64 sum(int x){
		int x0=bid[x];
		return s0[x]+s1[bfa[x0]]+s2[x0]*dep[x];
	}
	void Q_sort(Q*qs,int qp,bfs&b0){
		f0(a1,bp+1);
		f0(s0,idp+1);
		f0(s1,bp+1);
		f0(s2,bp+1);
		std::sort(qs,qs+qp,[](const Q&a,const Q&b){return a.bid<b.bid;});
		int p=0;
		F(i,qp){
			Q&q=qs[i];
			if(p<q.bid){
				do add(id[b0.ls[0][p++]]);while(p<q.bid);
				upd();
			}
			i64 s=0;
			if(q.d0<q.d1)F3(j,q.d0,q.d1)s+=sum(id1[j]);
			else F3(j,q.d1,q.d0)s-=sum(id1[j]);
			ans[q.qid]+=s;
		}
	}
}
struct node{
	#define l c[0]
	#define r c[1]
	node*c[2],*fa;
	int sz,top,btm;
	struct{
		int p,d;
		void set(int _p,int _d){if(_d>=0)p=_p,d=_d;}
	}q[2];
	Ans dtop[2],dbtm[2];
	bfs tops,btms;
	vector<Q>qt,qb,qtb;
	void set(int t,int d){
		int p=top;
		node*w=this,*f=fa,*u;
		w->q[t].set(p,d);
		for(;f;w=f,f=w->fa){
			f->q[t].set(-1,0);
			if(!f->btm){
				d-=dep[p]-dep[f->top];
				p=f->top;
				u=(w==f->l?f->r:f->l);
				if(u)u->q[t].set(u->top,d-(dep[u->top]-dep[p]));
			}else if(f->btm!=f->top){
				if(w==f->l){
					u=f->r;
					u->q[t].set(u->top,d-(dep[u->top]-dep[p]));
				}else{
					u=f->l;
					u->q[t].set(u->btm,d-(dep[p]-dep[u->btm]));
				}
			}else{
				d-=dep[p]-dep[f->top];
				p=f->top;
				if(d>=0)f->q[t].set(-1,1);
			}
		}
	}
	void cal(){
		if(!this)return;
		F(t,2)dtop[t].clr();
		if(btm)F(t,2)dbtm[t].clr();
		if(!q[0].p&&!q[1].p)return;

		if(!btm){//R
			F(t,2)if(q[1-t].p==-1&&q[t].p>0){
				int p=q[t].p,d=q[t].d;
				F(i,2)c[i]->q[t].set(c[i]->top,d-(dep[c[i]->top]-dep[p]));
				q[t].set(-1,0);
			}
			if(q[0].p==-1||q[1].p==-1){
				F(i,2)c[i]->cal();
				F(t,2){
					F(i,2)dtop[t].add(c[i]->dtop[t],dep[c[i]->top]-dep[top]);
					if(r)ans[cur_q]+=l->dtop[t].cal(r->dtop[1-t],dep[l->top]+dep[r->top]-dep[top]*2);
				}
			}else{
				F(t,2){
					if(q[t].p)dtop[t]=tops.get_ds(0,q[t].d);
				}
				if(q[0].p&&q[1].p){
					F(t,2)ans[cur_q]+=dtop[t].ans*dtop[1-t].sz;
					qt.push_back((Q){q[0].d,q[1].d,cur_q});
				}
			}
		}else if(top!=btm){//C
			F(t,2)if(q[1-t].p==-1&&q[t].p>0){
				int p=q[t].p,d=q[t].d;
				if(p==top){
					l->q[t].set(p,d);
					r->q[t].set(r->top,d-(dep[r->top]-dep[p]));
				}else{
					l->q[t].set(l->btm,d-(dep[p]-dep[l->btm]));
					r->q[t].set(p,d);
				}
				q[t].set(-1,0);
			}
			if(q[0].p==-1||q[1].p==-1){
				F(i,2)c[i]->cal();
				F(t,2){
					dtop[t].set(l->dtop[t],r->dtop[t],dep[r->top]-dep[top]);
					dbtm[t].set(r->dbtm[t],l->dbtm[t],dep[btm]-dep[l->btm]);
					ans[cur_q]+=l->dbtm[t].cal(r->dtop[1-t],1);
				}
			}else{
				F(t,2){
					if(q[t].p){
						if(q[t].p==top){
							dtop[t]=tops.get_ds(0,q[t].d);
							dbtm[t]=tops.get_ds(1,q[t].d);
						}else{
							dtop[t]=btms.get_ds(1,q[t].d);
							dbtm[t]=btms.get_ds(0,q[t].d);
						}
					}
				}
				if(q[0].p&&q[1].p){
					F(t,2)ans[cur_q]+=dtop[t].ans*dtop[1-t].sz;
					ans[cur_q]+=(i64)dtop[0].sz*dtop[1].sz*2;
					if(q[0].p==top){
						(q[1].p==top?qt:qtb).push_back((Q){q[0].d,q[1].d,cur_q});
					}else{
						(q[1].p==top?qtb:qb).push_back((Q){q[1].d,q[0].d,cur_q});
					}
				}
			}
		}else{//CR
			F(t,2)if(q[t].p>0){
				int p=q[t].p,d=q[t].d;
				if(l)l->q[t].set(l->top,d-(dep[l->top]-dep[p]));
				q[t].set(-1,1);
			}
			l->cal();
			F(t,2){
				dtop[t].clr();
				if(l){
					dtop[t].add(l->dtop[t],dep[l->top]-dep[top]);
					if(q[1-t].p==-1&&q[1-t].d==1)ans[cur_q]+=dtop[t].ans;
				}
				if(q[t].p==-1&&q[t].d==1)++dtop[t].sz;
				dbtm[t]=dtop[t];
			}
		}
		q[0].set(0,0);
		q[1].set(0,0);
	}
	void initC(node*_l,node*_r){
		l=_l;r=_r;
		sz=l->sz+r->sz;
		top=l->top;
		btm=r->btm;
		init();

		int d0[2],d1[2];
		d0[0]=0,d0[1]=dep[r->top]-dep[top];
		d1[1]=0,d1[0]=dep[btm]-dep[l->btm];
		tops.init(sz,d0,d1,l->tops,r->tops);
		btms.init(sz,d1,d0,l->btms,r->btms);
	}
	void initR(int w,node*_l,node*_r){
		l=_l;r=_r;
		sz=l->sz+r->sz;
		top=w,btm=0;
		init();

		int d[2];
		F(i,2)d[i]=dep[c[i]->top]-dep[top];
		tops.init(sz,d,0,l->tops,r->tops);
	}
	void initCR(int w,node*_l){
		l=_l;r=0;
		sz=1;
		if(l)sz+=l->sz;
		top=btm=w;
		init();

		int d=0;
		tops.n=1;
		if(l){
			d=dep[l->top]-dep[top];
			maxs(tops.n,l->tops.n+d);
		}
		tops.sz=new int[tops.n];
		++tops.sz[0];
		if(l)tops.ins0(d,l->tops);
		tops.init_ls(sz);
		*rs[0]++=top;
		if(l)tops.ins(d,l->tops);
		tops.init_ds0();
		tops.ds[1]=tops.ds[0];
		btms=tops;
	}
	void init(){
		F(i,2)if(c[i])c[i]->fa=this;
	}
	void sort_qs(vector<Q>&qs,bfs&as,bfs&bs){
		int bsz=sz/sqrt(qs.size())+1;
		for(Q&q:qs){
			q.d0=as.ls[min(q.d0+1,as.n)]-as.ls[0];
			q.d1=bs.ls[min(q.d1+1,bs.n)]-bs.ls[0];
			q.bid=q.d0/bsz;
		}
		std::sort(qs.begin(),qs.end());
	}
	void mo(vector<Q>&qs,vector<Q>&qs2,bfs&as,bfs&bs,bool rev){
		for(Q&q:qs)q.fix();
		sort_qs(qs,as,as);
		if(!rev)sort_qs(qs2,as,bs);
		int d0=0,d1=0;
		int m1=qs.size(),m2=qs2.size();
		using namespace MO;
		f0(MO::ans,m1+m2);
		if(as.ls)F(i,sz)id1[i]=id[as.ls[0][i]];
		if(bs.ls)F(i,sz)id1[sz+i]=id[bs.ls[0][i]];
		F(i,m1){
			Q&q=qs[i];
			qs1[i]=(Q){d0,q.d0,i,d1};
			d0=q.d0;
			qs1[m1+i]=(Q){d1,q.d1,i,d0};
			d1=q.d1;
		}
		d0=d1=0;
		F(i,m2){
			Q&q=qs2[i];
			if(rev)qs1[m1*2+i]=(Q){sz+d0,sz+q.d0,m1+i,d1};
			d0=q.d0;
			if(!rev)qs1[m1*2+i]=(Q){sz+d1,sz+q.d1,m1+i,d0};
			d1=q.d1;
		}
		Q_sort(qs1,m1*2+m2,as);
		F3(i,1,m1)MO::ans[i]+=MO::ans[i-1];
		F3(i,m1+1,m1+m2)MO::ans[i]+=MO::ans[i-1];
		F(i,m1)::ans[qs[i].qid]-=MO::ans[i]*2;
		F(i,m2)::ans[qs2[i].qid]-=MO::ans[m1+i]*2;
	}
	void init_block(){
		using namespace MO;
		bfs&b=tops;
		int e=(btm?::fa[top]:top);
		bfa[++bp]=bid[id[e]];
		
		F(i,sz){
			int w=b.ls[0][i],f=::fa[w];
			id[w]=++idp;
			bid[idp]=bp;
			MO::fa[idp]=(f==e?0:id[f]);
		}
		if(btm){
			for(int w=top,d=1;;w=son[w],++d){
				MO::dep[id[w]]=d;
				if(w==btm)break;
			}
			F3(i,br[bp-1]+1,idp+1){
				if(!MO::dep[i])MO::dep[i]=MO::dep[MO::fa[i]];
			}
			bdep[bp]=::dep[btm]-::dep[top]+1;
		}else bdep[bp]=0;
		br[bp]=idp;
	}
	void get_blocks(bool leaf){
		using namespace MO;
		if(top==btm){
			if(!l&&leaf)return bs.push_back(this);
			id[top]=++idp;
			MO::dep[idp]=1;
			MO::fa[idp]=0;
			bid[idp]=++bp;
			br[bp]=idp;
			bfa[bp]=bid[id[::fa[top]]];
			bdep[bp]=1;
			if(l)l->get_blocks(1);
			return;
		}
		if(sz<=B){
			if(!leaf)init_block();
			else bs.push_back(this);
			return;
		}
		if(!btm){
			F(i,2)c[i]->get_blocks(1);
		}else{
			l->get_blocks(0);
			r->get_blocks(leaf);
		}
	}
	void get_blocks(){
		using namespace MO;
		B=sqrt(sz);
		id[btm?::fa[top]:top]=0;
		idp=bp=0;
		f0(MO::dep,sz+1);
		bs.clear();
		get_blocks(0);
		bp0=bp;
		for(auto w:bs)w->init_block();
	}
	void offline(){
		if(!this)return;
		using namespace MO;

		if(qt.size()||qb.size()||qtb.size()){
			get_blocks();
			mo(qt,qtb,tops,btms,0);
			mo(qb,qtb,btms,tops,1);
		}

		l->offline();
		r->offline();
	}
	void* operator new(size_t);
	#undef l
	#undef r
}*crs[N];
void* node::operator new(size_t){
	static node ns[N*2],*np=ns;
	return np++;
}
node*build(int l,int r=0){
	assert(l!=r);
	int sr=sz[r],s=sz[l]-sr;
	for(int w=l,u=son[w],f=0;;f=w,w=u,u=son[u])if((sz[u]-sr)*2<s){
		node*cur=new node;
		if(f&&(r==u||sz[w]+sz[u]-sr*2<s))u=w,w=f;
		if(l==w&&r==u){
			struct cmp{
				bool operator()(node*a,node*b){return a->sz>b->sz;}
			};
			std::priority_queue<node*,std::vector<node*>,cmp> q;
			for(int x:e[w])if(x!=u)q.push(build(x));
			while(q.size()>1){
				node*a=q.top();q.pop();
				node*b=q.top();q.pop();
				node*r=new node;
				r->initR(w,a,b);
				q.push(r);
			}
			cur->initCR(w,q.size()?q.top():0);
			crs[w]=cur;
		}else{
			cur->initC(build(l,u),build(u,r));
		}
		return cur;
	}
}
void dfs(int w){
	sz[w]=1;
	for(int u:e[w]){
		dfs(u);
		sz[w]+=sz[u];
		if(sz[u]>sz[son[w]])son[w]=u;
	}
}
int main(){
	fread(ib,1,sizeof(ib),stdin);
	n=read();
	assert(1<=n&&n<=100000);
	for(int i=2;i<=n;++i){
		int f=read();
		assert(1<=f&&f<i);
		e[f].push_back(i);
		fa[i]=f;
		dep[i]=dep[f]+1;
	}
	dfs(1);
	node*rt=build(1);

	m=read();
	assert(1<=m&&m<=100000);
	for(cur_q=1;cur_q<=m;++cur_q){
		int p0=read(),d0=read(),p1=read(),d1=read();
		assert(1<=p0&&p0<=n);
		assert(0<=d0&&d0<=n-1);
		assert(1<=p1&&p1<=n);
		assert(0<=d1&&d1<=n-1);
		crs[p0]->set(0,d0);
		crs[p1]->set(1,d1);
		rt->cal();
	}
	rt->offline();
	for(int i=1;i<=m;++i)print(ans[i]);
	fwrite(ob,1,op-ob,stdout);
	return 0;
}
