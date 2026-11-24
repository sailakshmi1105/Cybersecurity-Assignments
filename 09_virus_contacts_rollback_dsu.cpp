// Problem 09: Virus Contacts
#include <bits/stdc++.h>
using namespace std;

struct Op { int type, x=0, y=0; };
struct Edge { int u,v; };
struct RollbackDSU {
    vector<int> p,sz;
    struct Change{int child,parent,oldSize;};
    vector<Change> hist;
    RollbackDSU(int n):p(n),sz(n,1){iota(p.begin(),p.end(),0);}
    int find(int x){while(p[x]!=x)x=p[x];return x;}
    int snapshot(){return hist.size();}
    void unite(int a,int b){
        a=find(a);b=find(b);
        if(a==b){hist.push_back({-1,-1,0});return;}
        if(sz[a]<sz[b])swap(a,b);
        hist.push_back({b,a,sz[a]});
        p[b]=a;sz[a]+=sz[b];
    }
    void rollback(int s){
        while((int)hist.size()>s){
            auto c=hist.back();hist.pop_back();
            if(c.child!=-1){p[c.child]=c.child;sz[c.parent]=c.oldSize;}
        }
    }
    int componentSize(int x){return sz[find(x)];}
};

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,q,k;cin>>n>>q>>k;
    vector<Op> ops(q);
    vector<int> dayAt(q);
    int day=0;
    vector<int> transition(q+1,-1);
    for(int i=0;i<q;++i){
        int t;cin>>t;ops[i].type=t;dayAt[i]=day;
        if(t==1){cin>>ops[i].x>>ops[i].y;--ops[i].x;--ops[i].y;}
        else if(t==2){cin>>ops[i].x;--ops[i].x;}
        else { ++day; transition[day]=i; }
    }

    vector<vector<Edge>> seg(4*q);
    auto add=[&](auto&& self,int node,int l,int r,int ql,int qr,Edge e)->void{
        if(ql>=r||qr<=l)return;
        if(ql<=l&&r<=qr){seg[node].push_back(e);return;}
        int mid=(l+r)/2;
        self(self,node*2,l,mid,ql,qr,e);
        self(self,node*2+1,mid,r,ql,qr,e);
    };

    for(int i=0;i<q;++i) if(ops[i].type==1){
        int expiryDay=dayAt[i]+k;
        int end=q;
        if(expiryDay<(int)transition.size() && transition[expiryDay]!=-1)
            end=transition[expiryDay];
        if(i<end)add(add,1,0,q,i,end,{ops[i].x,ops[i].y});
    }

    RollbackDSU dsu(n);
    vector<int> answer;
    auto dfs=[&](auto&& self,int node,int l,int r)->void{
        int snap=dsu.snapshot();
        for(auto e:seg[node])dsu.unite(e.u,e.v);
        if(r-l==1){
            if(ops[l].type==2)answer.push_back(dsu.componentSize(ops[l].x));
        }else{
            int mid=(l+r)/2;
            self(self,node*2,l,mid);
            self(self,node*2+1,mid,r);
        }
        dsu.rollback(snap);
    };
    if(q)dfs(dfs,1,0,q);
    for(int x:answer)cout<<x<<'\n';
}
