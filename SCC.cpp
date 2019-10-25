#include "bits/stdc++.h"
#define MAXN 1000009
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
int in[MAXN],fup[MAXN],tin[MAXN],TIM,S,comp[MAXN];
stack<int>st;
vector<int>adj[MAXN],group[MAXN];
void dfs(int nd){
	tin[nd]=fup[nd]=++TIM;
	st.push(nd);in[nd]=1;
	tr(it,adj[nd]){
		if(!tin[*it]){
			dfs(*it);
			umin(fup[nd],fup[*it]);	
		}
		else if(in[*it])
			umin(fup[nd],tin[*it]);
	}
	if(fup[nd]==tin[nd]){
		int aux;S++;
		do{
			aux=st.top();st.pop();
			comp[aux]=S;in[aux]=0;
			group[S].pb(aux);
		}while(aux!=nd);
	}
}

