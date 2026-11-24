// Problem 05: Spy Syndrome 2
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int nxt[26];
    int word = -1;
    Node() { fill(nxt, nxt+26, -1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin>>n;
    string t; cin>>t;
    int m; cin>>m;
    vector<string> words(m);
    vector<Node> trie(1);
    for(int id=0;id<m;++id){
        cin>>words[id];
        string s=words[id];
        for(char &c:s) c=tolower((unsigned char)c);
        reverse(s.begin(),s.end());
        int v=0;
        for(char c:s){
            int z=c-'a';
            if(trie[v].nxt[z]==-1){
                trie[v].nxt[z]=(int)trie.size();
                trie.emplace_back();
            }
            v=trie[v].nxt[z];
        }
        trie[v].word=id;
    }

    vector<int> prev(n+1,-1), chosen(n+1,-1);
    prev[0]=0;
    for(int i=0;i<n;++i) if(prev[i]!=-1){
        int v=0;
        for(int j=i;j<n;++j){
            int z=t[j]-'a';
            if(trie[v].nxt[z]==-1) break;
            v=trie[v].nxt[z];
            if(trie[v].word!=-1 && prev[j+1]==-1){
                prev[j+1]=i;
                chosen[j+1]=trie[v].word;
            }
        }
    }

    vector<string> ans;
    for(int p=n;p>0;){
        int id=chosen[p];
        ans.push_back(words[id]);
        p=prev[p];
    }
    reverse(ans.begin(),ans.end());
    for(int i=0;i<(int)ans.size();++i){
        if(i) cout<<' ';
        cout<<ans[i];
    }
    cout<<'\n';
}
