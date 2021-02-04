#include "bits/stdc++.h"
#define MAXN 100009
using namespace std;

vector<int>adj[MAXN];
int who[MAXN],vis[MAXN];

bool kuhn(int nd){ // returns true if there is augmenting path
	if(vis[nd])return 0;
	vis[nd]=1;
	for(int i=0;i<int(adj[nd].size());i++){
		int to=adj[nd][i];
		if(who[to]==-1 or kuhn(who[to])){
			who[to]=nd;
			return 1;
		}
	}
	return 0;
}
bool solve(int a,int b){ // returns true if there is perfect matching
	for(int i=1;i<=a;i++)adj[i].clear();
	for(int i=1;i<=b;i++)who[i]=-1;
	for(int i=1;i<=a;i++)
		for(int j=1;j<=b;j++)
			//add edges i->j
	for(int i=1;i<=a;i++){
		for(int j=1;j<=a;j++)vis[j]=0;
		kuhn(i);
	}
	for(int i=1;i<=b;i++)if(who[i]==-1)return 0;
	return 1;
}
int main(){
    solve(5,10); //K(a,b) bipartite graph
	return 0;
}
