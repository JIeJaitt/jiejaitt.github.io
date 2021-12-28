#include <stdio.h>

int Sum(int n)
{
  int s=0;
  while(n!=0) {
    s+=n%10;
    n/=10;
  }
  return s;
}

int main()
{
    int n;scanf("%d",&n);
    int num,ck/*check*/,count;
    int arr[]={2,3,4,5,6,7,8,9};
    
    while(n--)
    {
      scanf("%d",&num);
      int s=Sum(num*arr[0]);
      for(int i=1;i<8;i++)
      {
        int ck=Sum(num*arr[i]);
        count=i;
        if(ck!=s) break;
      }
      if(count==7) puts("yes");
      else puts("no");
    }
    return 0;
}