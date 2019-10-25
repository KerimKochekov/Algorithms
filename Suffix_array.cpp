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
char s[MAXN];
const int LOG=21;
int S[MAXN][LOG],n;
int vis[MAXN],ord[MAXN],lcp[MAXN];
pair<PII,int> H[MAXN],C[MAXN];
void fastsort(){
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
		vis[C[i].ff.ss]++;
	for(int i=1;i<MAXN;i++)
		vis[i]+=vis[i-1];
	for(int i=n;i>=1;i--)
		H[vis[C[i].ff.ss]--]=C[i];
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
		vis[H[i].ff.ff]++;
	for(int i=1;i<MAXN;i++)
		vis[i]+=vis[i-1];	
	for(int i=n;i>=1;i--)
		C[vis[H[i].ff.ff]--]=H[i];	
}
int main(){
   // freopen("file.in", "r", stdin);
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++)
    	S[i][0]=s[i]-'a'+1;
    for(int j=1;j<LOG;j++){
		for(int i=1;i<=n;i++)
			C[i]=mp(mp(S[i][j-1],(i+(1<<j-1)<=n?S[i+(1<<j-1)][j-1]:0)),i);
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
