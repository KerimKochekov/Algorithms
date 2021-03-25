#include "bits/stdc++.h"
#define MAXN 100009
#define pb(x) push_back(x)
using namespace std;
class Articulation {
  public:
    std::vector<int> keyV, bcc[MAXN];
    int cnt;
    int gao(int n, const std::vector<int> e[]) {
      memset(tag, use = 0, sizeof(tag[0]) * n);
      memset(low, cnt = 0, sizeof(low[0]) * n);
      std::fill_n(bcc, n, keyV = std::vector<int>());
      for (int i = 0; i < n; ++i) if (!tag[i]) dfs(i, 1, e);
      return cnt;
    }
  private:
    int tag[MAXN], low[MAXN], dot[MAXN], use;
    void dfs(int x, int dep, const std::vector<int> e[]) {
      int src = 0, out = 1 < dep; dot[use++] = x;
      tag[x] = low[x] = dep;
      for (auto &y: e[x]) {
        if (!tag[y]) {
          dfs(y, dep + 1, e);
          low[x] = std::min(low[x], low[y]);
          if (low[y] >= tag[x]) {
            if (++out == 2) keyV.push_back(x);
            while (dot[--use] != y) bcc[dot[use]].push_back(cnt);
            bcc[x].push_back(cnt); bcc[y].push_back(cnt++);
          }
        } else if (tag[y] != tag[x] - 1 || src++) {
          low[x] = std::min(low[x], tag[y]);
        }
      }
    }
} bcc;
vector<int> G[MAXN];
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
    	int u,v;
		scanf("%d%d",&u,&v);
		G[u].pb(v);G[v].pb(u);
    }
    bcc.gao(n,G);
    for(int i=0;i<n;i++){
    	cout<<i<<endl;
    	for(auto to:bcc.bcc[i])
			cout<<to<<" ";
		cout<<endl;
	}
	return 0;
}
