#include "bits/stdc++.h"

using namespace std;

struct two_sat {
    int n;
    vector<vector<int>> g, gr; // gr is the reversed graph
    vector<int> comp, topological_order, answer; // comp[v]: ID of the SCC containing node v
    vector<bool> vis;

    two_sat() {}

    two_sat(int _n) { init(_n); }

    void init(int _n) {
        n = _n;
        g.assign(2 * n, vector<int>());
        gr.assign(2 * n, vector<int>());
        comp.resize(2 * n);
        vis.resize(2 * n);
        answer.resize(2 * n);
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        gr[v].push_back(u);
    }

    // For the following three functions
    // int x, bool val: if 'val' is true, we take the variable to be x. Otherwise we take it to be x's complement.

    // At least one of them is true

    int neg(int x){
        if (x < n)
            return x + n;
        return x - n;
    }

    void set(int i, bool f){
        if (!f)
            add_clause_or(neg(i), neg(i), 1);
        else
            add_clause_or(i, i, 1);
    }

    void add_clause_or(int i, int j, bool f) {
        if (f){
            add_edge(neg(i), j);
            add_edge(neg(j), i);
        }
        else{
            set(i, 0); 
            set(j, 0);
        }
    }

    void add_clause_xor(int i, int j, bool f) {
        if (f){
            add_clause_or(i, j, 1);
            add_clause_or(neg(i), neg(j), 1);
        }
        else{
            add_clause_xor(i, neg(j), 1);
        }
    }

    void add_clause_and(int i, int j, bool f) {
        if (f){
            set(i, 1); 
            set(j, 1);
        }
        else
            add_clause_or(neg(i), neg(j), 1);
    }

    // Topological sort
    void dfs(int u) {
        vis[u] = true;

        for (const auto &v : g[u])
            if (!vis[v]) dfs(v);

        topological_order.push_back(u);
    }

    // Extracting strongly connected components
    void scc(int u, int id) {
        vis[u] = true;
        comp[u] = id;

        for (const auto &v : gr[u])
            if (!vis[v]) scc(v, id);
    }

    // Returns true if the given proposition is satisfiable and constructs a valid assignment
    bool satisfiable() {
        fill(vis.begin(), vis.end(), false);

        for (int i = 0; i < 2 * n; i++)
            if (!vis[i]) dfs(i);

        fill(vis.begin(), vis.end(), false);
        reverse(topological_order.begin(), topological_order.end());

        int id = 0;
        for (const auto &v : topological_order)
            if (!vis[v]) scc(v, id++);

        // Constructing the answer
        for (int i = 0; i < n; i++) {
            if (comp[i] == comp[i + n]) return false;
            answer[i] = (comp[i] > comp[i + n] ? 1 : 0);
        }
        return true;
    }
    
    void print_answer(){
        for (int i = 0; i < n; i++)
            printf("%d ", answer[i]);
        puts("");
    }
};

int main(){
    int n = 3;
    two_sat h(n);
    if (h.satisfiable())
        h.print_answer();
}
