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
typedef pair<int,int> PII;
template<class T>bool umin(T& a,T b){if(a>b){a=b;return 1;}return 0;}
template<class T>bool umax(T& a,T b){if(a<b){a=b;return 1;}return 0;}
int fup[MAXN],tin[MAXN],TIM,S,comp[MAXN];
stack<int>st;
vector<int>adj[MAXN];
void dfs(int nd,int pr=-1){
	tin[nd]=fup[nd]=++TIM;
	st.push(nd);
	int seen=0;
	tr(it,adj[nd]){
		if(*it==pr and !seen){
			seen=true;
			continue;
		}
		if(!tin[*it]){
			dfs(*it,nd);
			umin(fup[nd],fup[*it]);	
		}
		else
			umin(fup[nd],tin[*it]);
	}
	if(fup[nd]==tin[nd]){
		int aux;S++;
		do{
			aux=st.top();st.pop();
			comp[aux]=S;
		}while(aux!=nd);
	}
}
