class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> din(n+1),dout(n+1);
        for(auto p:trust) {
            int a=p[0],b=p[1];
            din[b]++;
            dout[a]++;
        }
        
        for(int i=1;i<=n;i++) 
            if(!dout[i] && din[i]==n-1)
                return i;
        return -1;
    }
};