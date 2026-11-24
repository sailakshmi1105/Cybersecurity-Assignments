// Problem 07: Xenon's Attack on the Gangs
#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> g;
int parent_[3005][3005];
int sub[3005][3005];
long long memo[3005][3005];

void dfs(int root, int u, int p) {
    parent_[root][u] = p;
    sub[root][u] = 1;
    for (int v : g[u]) if (v != p) {
        dfs(root, v, u);
        sub[root][u] += sub[root][v];
    }
}

long long solve(int u, int v) {
    if (u == v) return 0;
    long long &res = memo[u][v];
    if (res != -1) return res;
    long long take = 1LL * sub[u][v] * sub[v][u];
    return res = take + max(solve(parent_[v][u], v),
                            solve(u, parent_[u][v]));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    g.assign(n+1,{});
    for(int i=1,u,v;i<n;++i){
        cin>>u>>v;
        g[u].push_back(v); g[v].push_back(u);
    }
    for(int r=1;r<=n;++r) dfs(r,r,0);
    memset(memo,-1,sizeof(memo));
    long long ans=0;
    for(int u=1;u<=n;++u)
        for(int v=1;v<=n;++v)
            ans=max(ans,solve(u,v));
    cout<<ans<<'\n';
}
