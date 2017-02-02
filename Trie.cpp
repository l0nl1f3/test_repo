#include<map>
#include<stack>
#include<queue>
#include<cstdio>
#include<string>
#include<bitset>
#include<vector>
#include<cstring>
#include<complex>
#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;
#define fi first
#define se second
#define il inline
#define mp make_pair
#define pb push_back
#define ll long long
#define gc getchar()
#define inf 1001001001
#define Ri register int
#define Pii pair<int,int>
#define gmax(a,b) (a)=max((a),(b))
#define gmin(a,b) (a)=min((a),(b))
#define infll 1001001001001001001LL
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
il int read(){bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;}
#define gi read()
#define N 123456
#define M 3001234
struct Trienode{Trienode*ch[2];int cnt,v,x;};
Trienode*init(int x); 
struct Trie{
	Trienode a[M];int tot;
	Trienode*init(int x){
		Trienode*nw=a+(tot++);
		nw->x=x;nw->ch[0]=nw->ch[nw->cnt=-(nw->v=-1)]=NULL;
		return nw;
	}
	void ins(Trienode*rt,int x){
		for(int i=16,k;~i;i--){
			k=(x>>i)&1;
			rt->ch[k]=init(x^=(k<<i));
			rt=rt->ch[k];
		}
	}
	int que(Trienode*rt,int x,int v){
		if(rt->cnt==1)return rt->x^x;
		int res=0;
		for(int i=v,k;~i;i--)rt->ch[k=(x>>i)&1]?rt=rt->ch[k]:(res|=1<<i,rt=rt->ch[k^1]);
		return res;
	}
	int pu(Trienode*a,Trienode*b,int t){
		if(!a||!b)return !a?b->v:a->v;
		if(a->cnt>1&&b->cnt>1)return max(a->v,b->v);
		return (a->cnt==1?que(b,a->x,t-1):que(a,b->x,t-1))|(1<<t);
	}
	Trienode*merge(Trienode*a,Trienode*b,int t){
		if(!a||!b)return !a?b:a;
		a->cnt=a->cnt+b->cnt;
		if(t==-1)return a->v=0,a;
		for(int i=0;i<2;i++)a->ch[i]=merge(a->ch[i],b->ch[i],t-1);
		return a->v=pu(a->ch[0],a->ch[1],t),a;
	}
}T;
int n,m,w[N],ans[N];Trienode*rt[N];
struct edge{int to,nxt,v;};
struct graph{
	edge e[N+N];int n,m,lst[N],cnt;
	void resize(int a,int b){n=a;m=b;cnt=0;memset(lst,0,sizeof(lst));}
	graph(){cnt=0;}
	graph(int n,int m):n(n),m(m){}
	edge operator[](int a){return e[a];};
	void ins(int a,int b,int c){e[++cnt]=(edge){b,lst[a],c};lst[a]=cnt;}
	void lnk(int a,int b){ins(a,b,0);ins(b,a,0);}
	void dfs(int v,int fa=0){
		rt[v]=T.init(w[v]);
		T.ins(rt[v],w[v]);
		for(int i=lst[v],b;i;i=e[i].nxt){
			if((b=e[i].to)!=fa){
				dfs(b,v);rt[v]=T.merge(rt[v],rt[b],16);
			}
		}
		ans[v]=rt[v]->v;
	}
}G;
int main(){
	n=gi;
	for(int i=1;i<=n;i++)w[i]=gi;
	for(int i=1,u,v;i<n;i++)G.lnk(u=gi,v=gi);
	for(G.dfs(1),m=gi;m--;printf("%d\n",ans[gi])); 
	return 0;
}
