---
title: LeetCode 691. 贴纸拼词
---

## 贴纸拼词

我们有`n` $(n == stickers.length,1 <= n <= 50)$种不同的贴纸。每个贴纸上都有一个小写的英文单词。您想要拼写出给定的字符串 `target`$(1 <= target <= 15)$ ，方法是从收集的贴纸中切割单个字母并重新排列它们。如果你愿意，你可以多次使用每个贴纸，每个贴纸的数量是无限的。返回你需要拼出 `target` 的最小贴纸数量。如果任务不可能，则返回 `-1` 。**注意：**在所有的测试用例中，所有的单词都是从 `1000` 个最常见的美国英语单词中随机选择的，并且 `target` 被选择为两个随机单词的连接。`stickers[i]`$(1 <= stickers[i].length <= 10)$ 和 `target` 由小写英文单词组成。相关标签：位运算,动态规划,回溯,状态压缩。



## Stickers to Spell Word

We are given `n` different types of `stickers`. Each sticker has a lowercase English word on it. You would like to spell out the given string `target` by cutting individual letters from your collection of stickers and rearranging them. You can use each sticker more than once if you want, and you have infinite quantities of each sticker. Return *the minimum number of stickers that you need to spell out* `target`. If the task is impossible, return `-1`. **Note:** In all test cases, all words were chosen randomly from the `1000` most common US English words, and `target` was chosen as a concatenation of two random words. `stickers[i]` and `target` consist of lowercase English letters. Related Topics: Dynamic Programming, Backtracking, Bit Manipulation, Bitmask.

<!-- more -->

```bash
Input: stickers = ["with","example","science"], target = "thehat"
Output: 3
Explanation:
We can use 2 "with" stickers, and 1 "example" sticker.
After cutting and rearrange the letters of those stickers, we can form the target "thehat".
Also, this is the minimum number of stickers necessary to form the target string.
```

```bash
Input: stickers = ["notice","possible"], target = "basicbasic"
Output: -1
Explanation:
We cannot form the target "basicbasic" from cutting letters from the given stickers.
```



这题是一个非常经典的暴搜问题，它是说给我们一个字典然后字典里面的每个单词可以用任意多次，然后我们要用这个字典里面的单词拼凑出来一个给定的目标单词。所谓拼凑其实就是说我们从字典里面选择的单词所包含的所包含的所有字母完全覆盖目标值里面的字母。比如目标单词里面有两个t的话那么我们所选的所有单词总和加到一块至少要有两个t，以此类推。我们的数据范围非常小，目标单词的最大长度是十五，那也就是说我们最多只需要凑十五个字母，其实这一题是一个暴搜题，然后暴搜的时候我们需要加一些剪枝，如果直接暴搜的话肯定会超时。我们先需要确定这个搜索顺序，搜索顺序有很多种，我们这里采用每次枚举下一个单词选哪个，来了一个单词之后，我们用这个单词里的字母去填充我们当前的目标值里面的字母，填充完之后继续暴搜就可以了。然后我们搜的话可以发现会有很多种方案都会搜到同一种状态，然后我们未来需要多少单词的话其实只取决于当前这个状态是什么，我们当前的状态其实可以发现只取决于目标单词里面哪些字母已经被选出来了，所以我们当前状态用一个二进制state来表示，一共有十五个0和1，某一位是0的话表示这一位的字母还没有选出来，某一位是1的话表示 这一位的字母已经被选出来了。所以我们这里的话可以加一个记忆化，就是用一个数组来表示一下每种状态搜到的答案是多少，如果以后我们搜到之前计算过的状态的话，直接返回就可以了，不需要重复计算。这是一个很重要的剪枝，所以这一题是一个记忆化的搜索方式。



然后我们看代码怎么写：

```cpp
// 首先我们的N最大的话是十五个字母，所以我们的状态数量是二的十五次方
const int N=1<<15;
int f[N],g[N][26];

class Solution {
public:
const int INF=0x3f3f3f3f;
    int n;
    string tgt;
    vector<string> strs;

    int fill(int state,char c) {
        auto& v=g[state][c-'a'];
        if(v!=-1) return v;
        v=state;
        for(int i=0;i<n;i++) {
            if(!(state>>i&1) && tgt[i]==c) {
                v+=1<<i;
                break;
            }
        }
        return v;
    }

    int dfs(int state) {
        auto& v=f[state];
        if(v!=-1) return v;
        if(state==(1<<n)-1) return v=0;
        v=INF;
        for(auto& str:strs) {
            int cur=state;
            for(auto& c:str) {
                cur=fill(cur,c);
            }
            if(cur!=state) {
                v=min(v,dfs(cur)+1);
            }
        }
        return v;
    }

    int minStickers(vector<string>& stickers, string target) {
        memset(f,-1,sizeof f);
        memset(g,-1,sizeof g);
        strs=stickers;
        tgt=target;
        n=target.size();
        int res=dfs(0);
        if(res==INF) res= -1;
        return res;
    }
};
```







