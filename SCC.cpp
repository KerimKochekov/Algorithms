#include "bits/stdc++.h"
#define mp(x, y) make_pair(x, y)
using namespace std;
const int N = 1e5 + 5;
int dp[N], vis[N], T, S, comp[N], in[N];
stack<int> st;
vector<int> adj[N];
void dfs(int nd){
    vis[nd] = dp[nd] = ++T;
    st.push(nd); in[nd] = 1;
    for (auto to: adj[nd]){
        if (!vis[to]){
            dfs(to);
            dp[nd] = min(dp[nd], dp[to]);
        }
        else if (in[to])
            dp[nd] = min(dp[nd], vis[to]);
    }
    if (dp[nd] == vis[nd]){
        int aux;
        do{
            aux = st.top();
            st.pop();
			in[aux] = 0;
            comp[aux] = S;
        }while (aux != nd);
        S += 1;
    }
}
