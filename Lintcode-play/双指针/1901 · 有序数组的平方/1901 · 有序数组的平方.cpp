// 暴力排序
// （1）
class Solution {
public:
    /**
     * @param A: The array A.
     * @return: The array of the squares.
     */
    vector<int> SquareArray(vector<int> &A) {
        // write your code here
        int n=A.size();

        for(int i=0;i<n;i++)
            A[i]=A[i]*A[i];
	     // A[i]=pow(A[i],2); 但是*比pow函数更快，所以推荐手敲
        sort(A.begin(),A.end());
        return A;
    }
};

// （2）
class Solution {
public:
    /**
     * @param A: The array A.
     * @return: The array of the squares.
     */
    vector<int> SquareArray(vector<int> &A) {
        // write your code here
        for (auto iter = A.begin(); iter != A.end(); iter++){
            *iter = *iter * *iter;
        }
        sort(A.begin(), A.end());
        return A;
    }
};

