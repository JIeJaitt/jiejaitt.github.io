---
title: LeetCode 668. 乘法表中第k小的数
---

## 乘法表中第k小的数

几乎每一个人都用 乘法表。但是你能在乘法表中快速找到第`k`小的数字吗？给定高度`m` 、宽度`n` 的一张 `m * n`的乘法表，以及正整数`k`，你需要返回表中第`k` 小的数字。`m` 和 `n` 的范围在 [1, 30000] 之间。`k` 的范围在 [1, m * n] 之间。相关标签：数学, 二分查找。

## Kth Smallest Number in Multiplication Table

Nearly everyone has used the Multiplication Table. The multiplication table of size `m x n`$(1 <= m, n <= 3 * 10^4)$ is an integer matrix `mat` where `mat[i][j] == i * j` (**1-indexed**). Given three integers `m`, `n`, and `k`, return *the* `kth` *smallest element in the* `m x n` *multiplication table*. Related Topics: Math, Binary Search.

<!-- more -->

```bash
Input: m = 3, n = 3, k = 5
Output: 3
Explanation: The 5th smallest number is 3.
1	2	3
2	4	6
3	6	9
```

```bash
Input: m = 2, n = 3, k = 6
Output: 6
Explanation: The 6th smallest number is 6.
1	2	3
2	4	6
```

这题是给我们一个乘法表，题目对乘法表的描述给了一个链接，但是这个题目给的这个链接其实有点不太合适，因为他的链接里面的乘法表是从零开始的，然后这个题目乘法表的描述是从一开始的。

然后我们一个n✖️m的乘法表里面包含的元素应该是n✖️m个，然后我们需要去返回里面的第k小数。这题可以用二分来做，n和m都是在三万之间因此n✖️m是八亿多，没有爆int，int的最大范围是二十亿。关键是二分完怎么判断，我们每次二分一个mid，看下mid是不是答案。怎么判断mid是不是答案呢？我们要看的第k小数怎么来判断呢？其实第k小数就是说小于等于它的元素数量小于等于的数量。

比如说我们二分判断一下mid是不是第k小数，那么第k小数需要满足什么条件呢？第k小数应该满足小于等于它的元素数量小于等于的数量。比如说第k小数是x，小于等于x的数量应该是大于等于k的，注意不仅可以大于k而且可以等于k因为里面可能会有相同元素。那么我们应该找的就是满足小于等于x的数量大于等于k的所有x的里面最小的一个，这个就是我们的第k小数。那么找这个什么满足目录条件，满足什么大于等于条件的最小的一个数，这一看就可以用二分来做。

所以每次可以二分一个mid，然后判断一下小于等于mid的元素是不是大于等于k。如果小于等于mid的数量大于等于k的话，说明我们的答案要不是mid要不就是比mid小，所以我们去左边暴搜就可以了。否则如果小于等于mid的元素是小于k的话，说明我们的答案在右边去右边搜就可以了。那么怎么求小于等于mid的元素数量呢？我们可以枚举一下，比如可以枚举一下第一个数i，然后看一下i乘以多少，比如i乘以x小于等于mid的话，i乘以多少个x小于等于mid呢？i乘以多少个x是小于等于mid呢？

那么我们直接看一下这个x的最大值是多少就可以了，x满足小于等于mid/i同时x需要满足小于等于m。所以x每次的最大值min{m,mid/i},那么对于每个i都可以求一个这个值，那么相加起来就可以知道一共有多少个数小于等于mid了。

每次判断的话是$O(N)$的，所以整个算法的时间复杂度就是$O(Nlog N)$的

然后我们来看一下代码怎么写：

```cpp
class Solution {
public:
    int get(int m,int n,int mid) {
        int res=0;
        // 然后我们枚举一下第一个数
        for(int i=1;i<=n;i++) {
            res+=min(m,mid/i);
        }
        return res;
    }

    int findKthNumber(int m, int n, int k) {
        // 二分板子
        // 我们二分的时候最小值是从1开始，最大值是从n*m开始
        int l=1,r=n*m;
        // 二分
        while(l<r) {
            // 求下中点
            int mid=l+r>>1;
            // 判断一下小于等于mid的元素有多少个
            // 如果大于k个的话，说明答案在左边
            if(get(m,n,mid)>=k) r=mid;
            // 否则，答案在右边
            else l=mid+1;
        }
        return r;
    }
};
```

