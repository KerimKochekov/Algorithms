#include "bits/stdc++.h"
#define mp(x, y) make_pair(x, y)
using namespace std;

const int N = 1e5 + 5;
int dp[N], vis[N], T, S, comp[N];
stack<int> st;
vector<int> adj[N];
void dfs(int nd, int pr = -1){
    vis[nd] = dp[nd] = ++T;
    st.push(nd);
    for (auto to: adj[nd]){
        if (to == pr)
            continue;
        if (!vis[to]){
            dfs(to, nd);
            dp[nd] = min(dp[nd], dp[to]);
        }
        else
            dp[nd] = min(dp[nd], vis[to]);
    }
    if (dp[nd] == vis[nd]){
        int aux;
        do{
            aux = st.top();
            st.pop();
            comp[aux] = S;
        }while (aux != nd);
        S += 1;
    }
}
