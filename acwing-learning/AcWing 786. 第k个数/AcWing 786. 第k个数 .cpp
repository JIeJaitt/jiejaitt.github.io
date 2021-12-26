#include <iostream>

using namespace std;

const int N=100000+10;
int q[N];

int quick_sort(int q[],int l,int r,int k)
{
    if(l>=r) return q[l];
    
    int i=l-1,j=r+1,x=q[l+r>>1];
    while(i<j)
    {
        do i++;while(q[i]<x);
        do j--;while(q[j]>x);
        if(i<j) swap(q[i],q[j]);
    }
    if(j-l+1>=k) return quick_sort(q,l,j,k);
    else return quick_sort(q,j+1,r,k-(j-l+1));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n,k;cin>>n>>k;
    for(int i=0;i<n;i++) cin>>q[i];
    cout<<quick_sort(q,0,n-1,k)<<endl;
    
    return 0;
}