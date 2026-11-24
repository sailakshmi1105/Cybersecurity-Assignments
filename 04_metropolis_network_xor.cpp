// Problem 04: Metropolis Network
#include <bits/stdc++.h>
using namespace std;
static const long long MOD = 1000000007LL;

struct DSU {
    vector<int> p, sz;
    DSU(int n): p(n), sz(n,1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { while (p[x] != x) x = p[x] = p[p[x]]; return x; }
    void unite(int a, int b) {
        a=find(a); b=find(b); if(a==b) return;
        if(sz[a]<sz[b]) swap(a,b);
        p[b]=a; sz[a]+=sz[b];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m,k; cin>>n>>m>>k;
    vector<long long> c(n);
    for(auto &x:c) cin>>x;
    unordered_map<long long, vector<pair<int,int>>> groups;
    groups.reserve(m*2+1);
    for(int i=0,u,v;i<m;++i){
        cin>>u>>v; --u;--v;
        groups[c[u]^c[v]].push_back({u,v});
    }

    long long totalX = (k==60 ? (1LL<<60) : (1LL<<k));
    long long pow2n = 1;
    for(int i=0;i<n;++i) pow2n=pow2n*2%MOD;

    long long ans = ((totalX - (long long)groups.size()) % MOD + MOD) % MOD;
    ans = ans * pow2n % MOD;

    for(auto &entry: groups){
        DSU dsu(n);
        for(auto [u,v]:entry.second) dsu.unite(u,v);
        int components=0;
        for(int i=0;i<n;++i) if(dsu.find(i)==i) ++components;
        long long ways=1;
        for(int i=0;i<components;++i) ways=ways*2%MOD;
        ans=(ans+ways)%MOD;
    }
    cout<<ans<<'\n';
}
