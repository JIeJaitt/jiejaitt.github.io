---
title: LeetCode 944. 删列造序
---

## 删列造序

给你由 `n` 个小写字母字符串组成的数组 `strs`，其中每个字符串长度相等。这些字符串可以每个一行，排成一个网格。例如，`strs = ["abc", "bce", "cae"]` 可以排列为：

```bash
abc
bce
cae
```

你需要找出并删除 **不是按字典序升序排列的** 列。在上面的例子（下标从 0 开始）中，列 0（`'a'`, `'b'`, `'c'`）和列 2（`'c'`, `'e'`, `'e'`）都是按升序排列的，而列 1（`'b'`, `'c'`, `'a'`）不是，所以要删除列 1 。返回你需要删除的列数。

## Delete Columns to Make Sorted

You are given an array of `n` strings `strs`, all of the same length. The strings can be arranged such that there is one on each line, making a grid. For example, `strs = ["abc", "bce", "cae"]` can be arranged as:

```bash
abc
bce
cae
```

You want to **delete** the columns that are **not sorted lexicographically**. In the above example (0-indexed), columns 0 (`'a'`, `'b'`, `'c'`) and 2 (`'c'`, `'e'`, `'e'`) are sorted while column 1 (`'b'`, `'c'`, `'a'`) is not, so you would delete column 1. Return *the number of columns that you will delete*.

<!-- more -->

```bash
Input: strs = ["cba","daf","ghi"]
Output: 1
Explanation: The grid looks as follows:
  cba
  daf
  ghi
Columns 0 and 2 are sorted, but column 1 is not, so you only need to delete 1 column.
```

```bash
Input: strs = ["a","b"]
Output: 0
Explanation: The grid looks as follows:
  a
  b
Column 0 is the only column and is sorted, so you will not delete any columns.
```

```bash
Input: strs = ["zyx","wvu","tsr"]
Output: 3
Explanation: The grid looks as follows:
  zyx
  wvu
  tsr
All 3 columns are not sorted, so you will delete all 3.
```

- `n == strs.length`
- `1 <= n <= 100`
- `1 <= strs[i].length <= 1000`
- `strs[i]` 由小写英文字母组成 / `strs[i]` consists of lowercase English letters.



 这个题的话是给我们一个矩阵，然后让我们判断一下不是单调递增的然后输出列数，所以这个题目直接模拟一遍就可以了，然后是代码怎么写：

```cpp
class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        // n的话代表列数，m的话代表行数
        int n=strs.size(),m=strs[0].size();
        // 定义一下答案
        int res=0;
        // 然后我们枚举一下所有列
        for(int i=0;i<m;i++) {
            // 然后判断一下它是不是递增的
            bool flag=true;
            // 从这一层第一行开始
            for(int j=1;j<n;j++) {
                // 如果我们发现第j行第i列是小于第j-1行第i列
                if(strs[j][i]<strs[j-1][i])
                    // 说明它不是单调递增的
                    flag=false;
                // 然后我们判断一下如果flag是true的话，说明这一行是单调递增的
                // 反之则不是单调递增的
                // 这题是问我们有多少列不是单调递增的
            }
            if(!flag) res++;
        }
        return res;
    }
};
```

```go
func minDeletionSize(strs []string) int {
    res:=0
    n,m:=len(strs),len(strs[0])
    for i:=0;i<m;i++ {
        for j:=1;j<n;j++ {
            if strs[j][i]<strs[j-1][i] {
                res++
                break
            }
        }
    }
    return res
}
```



