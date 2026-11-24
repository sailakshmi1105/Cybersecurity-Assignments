// Problem 06: Sherlock and the Bitwise Operations
#include <bits/stdc++.h>
using namespace std;
static const long long MOD = 1000000007LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin>>T;
    while(T--){
        string s; cin>>s;
        int n=s.size(), sum=0;
        for(char c:s) sum += c-'a';

        vector<long long> dp(sum+1,0), ndp(sum+1);
        dp[0]=1;
        for(int i=0;i<n;++i){
            fill(ndp.begin(),ndp.end(),0);
            for(int v=0;v<=sum;++v) if(dp[v]){
                for(int x=0;x<=25 && v+x<=sum;++x){
                    ndp[v+x]=(ndp[v+x]+dp[v])%MOD;
                }
            }
            dp.swap(ndp);
        }
        cout<<(dp[sum]-1+MOD)%MOD<<'\n';
    }
}
