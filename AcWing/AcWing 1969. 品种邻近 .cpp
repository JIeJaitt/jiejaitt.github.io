#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;

int a[N];

int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    
    int n,k;cin>>n>>k;
    int res=-1;
    fill(a,a+1000010,-k);
    for (int i=1,id;i<=n;++i)
    {
        cin>>id;
        if(i-a[id]<=k) 
            res=max(res,id);
        a[id]=i;  
    }
    cout<<res<<endl;
    return 0;
}