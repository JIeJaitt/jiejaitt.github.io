// 第一代版本
#include <iostream>

using namespace std;

int main() {
    int n,count=0;
    cin>>n;
    while(n!=1) {
        if(n%2!=0) n=3*n+1;
        n=n/2;
        count++;
    }
    cout<<count;
    return 0;
}

// 第二代版本
#include <bits/stdc++.h>
using namespace std;
using gg = long long;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    gg ni, ans = 0;
    cin >> ni;
    for (; ni != 1; ++ans) {
        if (ni % 2 == 1) {
            ni = 3 * ni + 1;
        }
        ni /= 2;
    }
    cout << ans;
    return 0;
}