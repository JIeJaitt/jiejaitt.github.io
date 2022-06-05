---
title: LeetCode 953. 验证外星语词典
---

## 验证外星语词典

某种外星语也使用英文小写字母，但可能顺序 `order` $(order.length == 26)$不同。字母表的顺序（`order`）是一些小写字母的排列。给定一组用外星语书写的单词 `words`$(1 <= words.length <= 100,1 <= words[i].length <= 20)$，以及其字母表的顺序 `order`，只有当给定的单词在这种外星语中按字典序排列时，返回 `true`；否则，返回 `false`。在 `words[i]` 和 `order` 中的所有字符都是英文小写字母。相关标签：数组,哈希表,字符串。

## Verifying an Alien Dictionary

In an alien language, surprisingly, they also use English lowercase letters, but possibly in a different `order`. The `order` of the alphabet is some permutation of lowercase letters. Given a sequence of `words` written in the alien language, and the `order` of the alphabet, return `true` if and only if the given `words` are sorted lexicographically in this alien language. All characters in `words[i]` and `order` are English lowercase letters. Related Topics: Array, Hash Table, String.

<!-- more -->

```bash
Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
Output: true
Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.
```

```bash
Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
Output: false
Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1], hence the sequence is unsorted.
```

```bash
Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
Output: false
Explanation: The first three characters "app" match, and the second string is shorter (in size.) According to lexicographical rules "apple" > "app", because 'l' > '∅', where '∅' is defined as the blank character which is less than any other character (More info).
```

这个题是一个简单的模拟题，它是让我们判断words这堆字符串是不是有序的。只不过这里在比较字典序的时候不是按照我们英文字母的顺序，而是它给定我们的一个26个英文字母的顺序，我们需要按照这个顺序来判断，那么这里我们直接模拟就可以了。

当我们结束的时候有一个边界情况，就是可能第一个串还没有遍历完，第二个串已经遍历结束了的情况。如果是这样的话，就是前面这一段都相等，然后a多了一段，那么其实a的字典序应该是比b要大的，那么这个的话也是矛盾的，也需要返回false。

复杂度分析：时间复杂度$O(m×n)$，其中 m 为字符串数组的长度，n 为数组中字符串的平均长度，每个字符串需要前一个字符串进行比较，因此时间复杂度为 $O(m×n)$。空间复杂度$O(C)$。其中 C 表示字母表的长度，需要存储字母表 `order` 每个字符的字典序索引，题目中给定的字母表的长度为 $C=26$。

```cpp
class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        // 首先我们开一个哈希表用来存储每一个字母的位置下标
        unordered_map<char,int> p;
        // 然后枚举一下所有的字母，第order[i]的字母次序是i
        for(int i=0;i<order.size();i++) p[order[i]]=i;
        // 然后我们从前往后判断一下所有的单词是不是有序的就可以了
        // 其实就是判断一下下一个字符串的字典序是不是大于等于上一个字符串
        for(int i=1;i<words.size();i++) {
            // 用a来表示我们i-1个串，用b来表示我们当前的串
            auto &a =words[i-1],&b=words[i];
            // x表示第一个串，y表示第二个串
            int x=0,y=0;
            // 枚举一下当前两个串的字典序是不是有序的
            // 当我们的x没有枚举完第一个串的时候并且当y没有枚举完第二个串的时候
            while(x<a.size()&&y<b.size()) {
                // 然后每次判断一下如果我们发现了a[x]的次序是大于b[y]的次序的话
                // 说明是逆序
                if(p[a[x]]>p[b[y]]) return false;
                // 否则我们发现a[x]的次序已经小于b[y]的次序了，表示字典序已经找出来了
                if(p[a[x]]<p[b[y]]) break;
                // 否则x，y往后加
                x++;y++;
            }
            // 当我们结束的时候有一个边界情况
            // 就是前面这一段都相等，然后a多了一段，那么其实a的字典序应该是比b要大的
            if(x<a.size()&&y==b.size()) return false;
        }
        return true;
    }
};
```



```go
func isAlienSorted(words []string, order string) bool {
    index := [26]int{}
    for i, c := range order {
        index[c-'a'] = i
    }
next:
    for i := 1; i < len(words); i++ {
        for j := 0; j < len(words[i-1]) && j < len(words[i]); j++ {
            pre, cur := index[words[i-1][j]-'a'], index[words[i][j]-'a']
            if pre > cur {
                return false
            }
            if pre < cur {
                continue next
            }
        }
        if len(words[i-1]) > len(words[i]) {
            return false
        }
    }
    return true
}
```



