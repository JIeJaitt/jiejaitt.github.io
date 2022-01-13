#include <bits/stdc++.h>

using namespace std;

const int N=100000+10;
int m;
int stk[N],tt;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin>>m;
    while(m--)
    {
        string op;
        int x;
        
        cin>>op;
        if(op=="push") 
        {
            cin>>x;
            stk[++tt]=x;
        }
        else if(op=="pop") --tt;
        else if(op=="empty") cout<<(tt?"NO":"YES")<<endl;
        else cout<<stk[tt]<<endl;
    }
    return 0;
}