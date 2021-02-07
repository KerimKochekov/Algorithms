#include "bits/stdc++.h"
#define MAXN 600009
#define INF 1000000007
#define mp(x,y) make_pair(x,y)
#define all(v) v.begin(),v.end()
#define pb(x) push_back(x)
#define wr cout<<"----------------"<<endl;
#define ppb() pop_back()
#define tr(ii,c) for(__typeof((c).begin()) ii=(c).begin();ii!=(c).end();ii++)
#define ff first
#define ss second
#define my_little_dodge 46
#define debug(x)  cerr<< #x <<" = "<< x<<endl;
using namespace std;

typedef long long ll;
typedef pair<int,int> PII;
template<class T>bool umin(T& a,T b){if(a>b){a=b;return 1;}return 0;}
template<class T>bool umax(T& a,T b){if(a<b){a=b;return 1;}return 0;}
vector<int>adj[MAXN];
vector<pair<PII,PII> >query[MAXN];
const int LOG=19;
int st[MAXN],en[MAXN],id[MAXN],T;
int L[MAXN],R[MAXN],arr[MAXN],ans[MAXN];
int lca[MAXN],P[MAXN][LOG],lvl[MAXN];
int low[MAXN],high[MAXN],bel[MAXN],now;
void dfs(int nd=1,int pr=-1){
	st[nd]=++T;
	id[T]=nd;
	tr(it,adj[nd])
		if(*it!=pr){
			P[*it][0]=nd;
			lvl[*it]=lvl[nd]+1;
			dfs(*it,nd);
		}
	en[nd]=++T;
	id[T]=nd;
}
int LCA(int u,int v){
	if(lvl[u]<lvl[v])swap(u,v);
	for(int i=LOG-1;i>=0;i--)
		if(P[u][i] and lvl[P[u][i]]>=lvl[v])
			u=P[u][i];
	if(u==v)return u;
	for(int i=LOG-1;i>=0;i--)
		if(P[u][i] and P[v][i]!=P[u][i])
			u=P[u][i],v=P[v][i];
	return P[u][0];
}	
void work(int nd){
	
}
int get(int l,int r){
	return -1;	
}
const int BLOK=550;
void naive(int l,int r){for(int i=l;i<=r;i++)work(id[i]);}
int main(){
    //freopen("file.in", "r", stdin);
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
    	scanf("%d",arr+i);
    low[1]=now=1;
    for(int i=1;i<=n;i++){
    	bel[i]=now;
		if(i%BLOK==0){
			high[now]=i;
			if(i<n)low[++now]=i+1;
		}	
    }high[now]=n;
    for(int i=1;i<n;i++){
    	int u,v;
		scanf("%d%d",&u,&v);
		adj[u].pb(v);
		adj[v].pb(u);	
    }
    dfs();
	for(int j=1;j<LOG;j++)
	    for(int i=1;i<=n;i++)
			if(P[i][j-1])
				P[i][j]=P[P[i][j-1]][j-1];
    for(int i=1;i<=q;i++){
    	int u,v;
    	scanf("%d%d%d%d",&u,&v,L+i,R+i);
    	lca[i]=LCA(u,v);
    	int l,r,f=0;
    	if(st[u]>st[v])swap(u,v);
    	if(u==lca[i])l=st[u],r=st[v];
    	else l=en[u],r=st[v],f=1;
    	if(r-l+1<=BLOK){
	    	if(f)work(lca[i]);
	    	naive(l,r);
	    	ans[i]=get(L[i],R[i]);
	    	naive(l,r);
	    	if(f)work(lca[i]);
	    	continue;
	    }
	    query[(l-1)/BLOK].pb(mp(mp(r,l),mp(i,f)));
    }
    for(int i=0;i<MAXN;i++){
    	if(query[i].empty())continue;
		sort(all(query[i]));
		int ls=(i+1)*BLOK;
		int p=ls+1;
		for(int j=0;j<int(query[i].size());j++){
			int r=query[i][j].ff.ff,l=query[i][j].ff.ss;
			int ind=query[i][j].ss.ff,f=query[i][j].ss.ss;
			while(p<=r)work(id[p++]);
			for(int j=l;j<=ls;j++)work(id[j]);
			if(f)work(lca[ind]);
			ans[ind]=get(L[ind],R[ind]);
			if(f)work(lca[ind]);
			for(int j=l;j<=ls;j++)work(id[j]);
		}p--;
		while(p>ls)work(id[p--]);
		query[i].clear();
    }
    for(int i=1;i<=q;i++)
    	printf("%d\n",ans[i]);
	return 0;
}
