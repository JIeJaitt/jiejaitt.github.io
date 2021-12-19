class Solution {
    public int findJudge(int n, int[][] trust) {
        int[] din=new int [n+1],dout=new int[n+1];
        for(int[] p:trust) {
            int a=p[0],b=p[1];
            ++din[b];
            ++dout[a];
        }
        
        for(int i=1;i<=n;i++) {
            if(din[i]==n-1&&dout[i]==0 /*dout[i]==0*/) {
                return i;
            }
        }
        return -1;
    }
}