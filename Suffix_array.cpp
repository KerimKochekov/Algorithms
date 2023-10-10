#include "bits/stdc++.h"
#define ff first
#define ss second
#define mp(x,y) make_pair(x,y)
using namespace std;

typedef long long ll;
typedef pair<int,int> PII;
const int N = 1e5 + 5;
const int LOG = 21;
char s[N];
int S[N][LOG], n;
int vis[N], ord[N], lcp[N];
pair<PII,int> H[N], C[N];
void fastsort(){
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
		vis[C[i].ff.ss]++;
	for(int i=1;i<N;i++)
		vis[i]+=vis[i-1];
	for(int i=n;i>=1;i--)
		H[vis[C[i].ff.ss]--]=C[i];
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
		vis[H[i].ff.ff]++;
	for(int i=1;i<N;i++)
		vis[i]+=vis[i-1];	
	for(int i=n;i>=1;i--)
		C[vis[H[i].ff.ff]--]=H[i];	
}
int main(){
    scanf("%s",s+1);
    n = strlen(s+1);
    for(int i=1;i<=n;i++)
    	S[i][0] = s[i]-'a'+1;
    for(int j=1;j<LOG;j++){
		for(int i=1;i<=n;i++)
			C[i]=mp(mp(S[i][j-1],(i+(1<<(j-1))<=n?S[i+(1<<(j-1))][j-1]:0)),i);
		fastsort();
		for(int i=1;i<=n;i++)
			S[C[i].ss][j]=S[C[i-1].ss][j]+(C[i].ff!=C[i-1].ff);	
	}
	for(int i=1;i<=n;i++)
		ord[S[i][LOG-1]]=i;
	int j=0;
	for(int i=1;i<=n;i++){
		if(S[i][LOG-1]==1)
			continue;
		while(i+j<=n and ord[S[i][LOG-1]-1]+j<=n and s[i+j]==s[ord[S[i][LOG-1]-1]+j])
			j++;
		lcp[S[i][LOG-1]-1]=j;
		if(j)
			j--;
	}	
	return 0;
}
