// Problem 08: Dynamic Bipartite Graph
#include <bits/stdc++.h>
using namespace std;

struct Edge { int u,v; };
struct RollbackDSU {
    vector<int> p, sz, xr;
    struct Change { int b, a, oldSizeA, oldBad; };
    vector<Change> hist;
    int bad=0;
    RollbackDSU(int n):p(n),sz(n,1),xr(n,0){iota(p.begin(),p.end(),0);}
    pair<int,int> find(int x){
        int z=0;
        while(p[x]!=x){z^=xr[x];x=p[x];}
        return {x,z};
    }
    int snapshot(){return (int)hist.size();}
    void unite(int u,int v){
        auto [a,x]=find(u); auto [b,y]=find(v);
        if(a==b){
            hist.push_back({-1,-1,0,bad});
            if((x^y)!=1) ++bad;
            return;
        }
        if(sz[a]<sz[b]){swap(a,b);swap(x,y);}
        hist.push_back({b,a,sz[a],bad});
        p[b]=a; xr[b]=x^y^1; sz[a]+=sz[b];
    }
    void rollback(int s){
        while((int)hist.size()>s){
            auto c=hist.back();hist.pop_back();
            bad=c.oldBad;
            if(c.b!=-1){p[c.b]=c.b;xr[c.b]=0;sz[c.a]=c.oldSizeA;}
        }
    }
};

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,q;cin>>n>>q;
    vector<vector<Edge>> seg(4*q);
    auto add=[&](auto&& self,int node,int l,int r,int ql,int qr,Edge e)->void{
        if(ql>=r||qr<=l)return;
        if(ql<=l&&r<=qr){seg[node].push_back(e);return;}
        int mid=(l+r)/2;
        self(self,node*2,l,mid,ql,qr,e);
        self(self,node*2+1,mid,r,ql,qr,e);
    };
    map<pair<int,int>,int> active;
    for(int i=0;i<q;++i){
        int u,v;cin>>u>>v;--u;--v;
        if(u>v)swap(u,v);
        auto key=make_pair(u,v);
        auto it=active.find(key);
        if(it==active.end()) active[key]=i;
        else { add(add,1,0,q,it->second,i,{u,v}); active.erase(it); }
    }
    for(auto [e,l]:active)add(add,1,0,q,l,q,{e.first,e.second});

    RollbackDSU dsu(n);
    vector<string> ans(q);
    auto dfs=[&](auto&& self,int node,int l,int r)->void{
        int snap=dsu.snapshot();
        for(auto e:seg[node])dsu.unite(e.u,e.v);
        if(r-l==1) ans[l]=(dsu.bad==0?"YES":"NO");
        else{
            int mid=(l+r)/2;
            self(self,node*2,l,mid);
            self(self,node*2+1,mid,r);
        }
        dsu.rollback(snap);
    };
    dfs(dfs,1,0,q);
    for(auto &s:ans)cout<<s<<'\n';
}
