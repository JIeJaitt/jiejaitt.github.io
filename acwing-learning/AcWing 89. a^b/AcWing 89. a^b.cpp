#include <iostream>

using namespace std;
using gg=long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int a,b,p;
    cin>>a>>b>>p;
    
    int res=1%p;
    while(b)
    {
        if(b&1) res=(gg)res*a%p;
        a=(gg)a*a%p;
        b>>=1;
        
    }
    cout<<res<<endl;
    return 0;
}