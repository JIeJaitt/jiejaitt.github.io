#include <bits/stdc++.h>
using namespace std;
using gg=long long;
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  gg A,B;cin>>A>>B;
  gg ans=0;
  gg outlet=1;
  while(outlet<B)
  {
    --outlet;
    outlet+=A;
    ++ans;
  }
  cout<<ans<<endl;
  return 0;
}