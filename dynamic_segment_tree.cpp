#include "bits/stdc++.h"
#define MAXN 100009
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
typedef pair<ll,ll> PII;
template<class T>bool umin(T& a,T b){if(a>b){a=b;return 1;}return 0;}
template<class T>bool umax(T& a,T b){if(a<b){a=b;return 1;}return 0;}
struct node {
    ll ans,mx,lazy;
    PII pre,suf;
    node *l, *r;
    node(){
    	l=r=NULL;
    }
};
const ll B=1e18;
void merge(node *v,node *cep,node *sag){
	if(cep==NULL){
		v=sag;
		return;	
	}
	if(sag==NULL){
		v=cep;
		return;	
	}
	v->mx=max(cep->mx,sag->mx);
	if(v->mx==sag->mx and v->mx==cep->mx)
		v->ans=max(sag->ans,cep->ans);
	else if(v->mx==cep->mx)
		v->ans=cep->ans;
	else
		v->ans=sag->ans;
	if(cep->suf.ff==v->mx and sag->pre.ff==v->mx)
		umax(v->ans,cep->suf.ss+sag->pre.ss);
		
	v->pre=cep->pre;
	if(cep->pre==cep->suf and sag->pre.ff==cep->pre.ff)	
		v->pre.ss=cep->pre.ss+sag->pre.ss;
		
	v->suf=sag->suf;
	if(sag->pre==sag->suf and sag->suf.ff==cep->suf.ff)	
		v->suf.ss=cep->suf.ss+sag->suf.ss;
}
void add(node *v,ll val){
	if(v==NULL)return;
	v->lazy+=val;v->mx+=val;
	v->pre.ff+=val;v->suf.ff+=val;	
}
void shift(node *v){
	if(v==NULL or v->lazy==0)
		return;
	add(v->l,v->lazy);
	add(v->r,v->lazy);
	v->lazy=0;
}
void inc(node *v,ll l,ll r,ll val,ll x=1,ll y=B){
	if(v==NULL or l>y or x>r or l>r or x>y)
		return;
	if(l<=x and y<=r){
		add(v,val);
		return;
	}
	ll mid=(x+y)>>1LL;
	if(v->l==NULL){
		v->l=new node();
		v->l->ans=v->l->pre.ss=v->l->suf.ss=(mid-x+1);
		v->l->mx=v->l->lazy=v->l->pre.ff=v->l->suf.ff=0;
	}
	if(v->r==NULL){
		v->r=new node();
		v->r->ans=v->r->pre.ss=v->r->suf.ss=(y-mid);
		v->r->mx=v->r->lazy=v->r->pre.ff=v->r->suf.ff=0;
	}
	shift(v);
	inc(v->l,l,r,val,x,mid);
	inc(v->r,l,r,val,mid+1,y);
	merge(v,v->l,v->r);
}
node *ans;
void get(node *v,ll l,ll r,ll x=1,ll y=B){
	if(v==NULL or l>y or x>r or l>r or x>y)
		return;
	if(l<=x and y<=r){
		if(ans==NULL)
			ans=v;
		else{
			node *tmp=new node();
			merge(tmp,ans,v);ans=tmp;	
		}
		return;
	}
	ll mid=(x+y)>>1LL;
	if(v->lazy>0){
		if(v->l==NULL){
			v->l=new node();
			v->l->ans=v->l->pre.ss=v->l->suf.ss=(mid-x+1);
			v->l->mx=v->l->lazy=v->l->pre.ff=v->l->suf.ff=0;
		}
		if(v->r==NULL){
			v->r=new node();
			v->r->ans=v->r->pre.ss=v->r->suf.ss=(y-mid);
			v->r->mx=v->r->lazy=v->r->pre.ff=v->r->suf.ff=0;
		}
	}
	shift(v);
	get(v->l,l,r,x,mid);
	get(v->r,l,r,mid+1,y);
	merge(v,v->l,v->r);
}
int main(){
    //freopen("file.in", "r", stdin);
    node *root = new node();
	root->ans=root->pre.ss=root->suf.ss=B;
	root->mx=root->lazy=root->pre.ff=root->suf.ff=0;
    int q;
    scanf("%d",&q);
    while(q--){
    	int t;ll l,r,x;
		scanf("%d%lld%lld",&t,&l,&r);
		if(t==1){
			scanf("%lld",&x);
			inc(root,l,r,x);
		}
		else{
			ans=NULL;get(root,l,r);
			if(ans==NULL or ans->mx==0)	
				printf("%lld\n",r-l+1);
			else
				printf("%lld\n",ans->ans);
		//	printf("ans = %lld %lld\n",ans->mx,ans->ans);
		}
    }
	return 0;
}
