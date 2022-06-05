---
title: LeetCode 933. 最近的请求次数
---
## 最近的请求次数 

写一个 `RecentCounter` 类来计算特定时间范围内最近的请求。请你实现 `RecentCounter` 类：

- `RecentCounter()` 初始化计数器，请求数为 0 。

- `int ping(int t)` 在时间 `t` 添加一个新请求，其中 `t` 表示以毫秒为单位的某个时间，并返回过去 `3000` 毫秒内发生的所有请求数（包括新请求）。确切地说，返回在 `[t-3000, t]` 内发生的请求数。

**保证** 每次对 `ping` 的调用都使用比之前更大的 `t` 值。

## Number of Recent Calls

You have a `RecentCounter` class which counts the number of recent requests within a certain time frame. Implement the `RecentCounter` class:

- `RecentCounter()` Initializes the counter with zero recent requests.
- `int ping(int t)` Adds a new request at time `t`, where `t` represents some time in milliseconds, and returns the number of requests that has happened in the past `3000` milliseconds (including the new request). Specifically, return the number of requests that have happened in the inclusive range `[t - 3000, t]`.

It is **guaranteed** that every call to `ping` uses a strictly larger value of `t` than the previous call.

<!-- more -->

```bash
Input
["RecentCounter", "ping", "ping", "ping", "ping"]
[[], [1], [100], [3001], [3002]]
Output
[null, 1, 2, 3, 3]

Explanation
RecentCounter recentCounter = new RecentCounter();
recentCounter.ping(1);     // requests = [1], range is [-2999,1], return 1
recentCounter.ping(100);   // requests = [1, 100], range is [-2900,100], return 2
recentCounter.ping(3001);  // requests = [1, 100, 3001], range is [1,3001], return 3
recentCounter.ping(3002);  // requests = [1, 100, 3001, 3002], range is [2,3002], return 3
```



这个题目说简单不简单，说难不难，属于那种理解了题意就很容易做出来的题目。题目标签是「简单/设计/队列/数据流」。

这个题是按照时序（或者是时间轴）给我们很多请求然后这题的话是对每一个标记来了之后我们要去查询一下以这个标记为右端点的长度是三千的闭区间中一共有几个标记。其实就是滑动窗口换了一种说法，也就是说我们的一个窗口长度为三千的窗口会从前往后一直滑，然后每一次问这个窗口里有多少个点。维护滑动窗口我们可以用队列来做简单一点，因为队列可以天然的维护一个滑动窗口,由于每次收到的请求的时间都比之前的大，因此从队首到队尾的时间值是单调递增的。每次新来一个数，插入队头，然后队尾元素如果出了这个窗口的话，就弹出就好了。然后每次返回队列里面元素的个数即可。换言之，当在时间 `t` 收到请求时，为了求出 `[t-3000,t]` 内发生的请求数，我们可以不断从队首弹出早于 `t-3000` 的时间。循环结束后队列的长度就是 `[t-3000,t]` 内发生的请求数。

然后我们看这题的这个代码怎么写：

```cpp
class RecentCounter {
public:
    queue<int> q;
    
    RecentCounter() {
        
    }
    
    int ping(int t) {
        q.push(t);
        while(t-q.front()>3000) q.pop();
        return q.size();
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
```






