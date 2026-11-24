// Problem 10: Interactive Hash Collision
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin>>n))return 0;
    int x=1;
    cout<<"? "<<n<<" "<<x<<endl;
    int c;
    if(!(cin>>c) || c==-1)return 0;

    int steps=n-c;
    int r;
    if(steps==0){
        r=x;
    }else{
        cout<<"? "<<steps<<" "<<x<<endl;
        if(!(cin>>r) || r==-1)return 0;
    }
    cout<<"! "<<c<<" "<<r<<endl;
    return 0;
}
