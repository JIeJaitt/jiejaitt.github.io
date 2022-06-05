---
title: LeetCode 812. 最大三角形面积
---

## 最大三角形面积

给定包含多个点的集合$(3 <= points.length <= 50,-50 <= points[i][j] <= 50)$，从其中取三个点组成三角形，返回能组成的最大三角形的面积。不存在重复的点。结果误差值在 `10^-6` 以内都认为是正确答案。相关标签：几何,数组,数学。



## Largest Triangle Area

Given an array of points on the **X-Y** plane `points` where `points[i] = [xi, yi]`, return *the area of the largest triangle that can be formed by any three different points*. Answers within `10^(-5)` of the actual answer will be accepted. All the given points are **unique**. Related Topics: Array, Math, Geometry.

<!-- more -->

```bash
Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
Output: 2.00000
Explanation: The five points are shown in the above figure. The red triangle is the largest.
```

```bash
Input: points = [[1,0],[0,0],[0,1]]
Output: 0.50000
```



最大三角形的面积，其实求三角形的面积有很多种方法，那么在计算机里面一般比较常用的是叉积，就是我们高中学的叉积。如何求一个三角形的面积呢？比如一个三角形的两个点$(x_1,y_1),(x_2,y_2)$,那么这个三角形的有向面积应该是两个向量的叉积。叉积公式还记得嘛？就是$x_1y_2-x_2y_1$。这个面积是有向面积，就是如果说我们第二个点在第一个点的逆时针方向，那么这个面积是正的，否则这个面积是负的。

那么这题的话我们直接去枚举就可以了。它是给我们很多点然后求由这很多个点构成的三角形的面积的最大值。我们可以随便遍历一下所有三个点的组合，所有三个点的组合$a,b,c$，然后我们求面积的时候其实就是求一下c这个点减去a这个点得到的向量叉乘上b这个点减去a这个点得到的向量，也就是说我们其实求的是ac和ab两个向量围成的面积，最后注意要取绝对值就可以了。

用叉积来求的话大家会发现算法的精度更高一点，当然也可以用海伦公式，海伦公式也是可以用的，但是海伦公式的话大家可以发现会有开根号的一个操作，那么开根号的操作精度就会稍微低一些，所以一般计算机里面用的比较多的还是叉积公式，叉积公式不涉及到开根号只涉及到了乘法和减法，运算量是比较小的。所以它是一个精度非常高而且运行效率比较快的一个算法。叉积其实是计算几何的一个用的比较多的非常基本的概念。

复杂度分析：时间复杂度$O(n^3)$,其中$n$是数组$points$的长度。三重循环需要$O(n^3)$。空间复杂度$O(1)$。

然后我们来看一下代码怎么写：

```cpp
class Solution {
public:
    // 首先我们先写好差积公式
    int cross(int x1,int y1,int x2,int y2) {
        return x1*y2-x2*y1;
    }
    // 然后我们需要求的应该是三个点围成的面积
    int area(vector<int>& a,vector<int>& b,vector<int>& c) {
        return cross(b[0]-a[0],b[1]-a[1],c[0]-a[0],c[1]-a[1]);
    }

    double largestTriangleArea(vector<vector<int>>& points) {
        // 这里是枚举所有三个点的组合
        int res=0;
        for(auto& a:points) 
            for(auto& b:points) 
                for(auto& c:points)
                    // 这里记得取一个绝对值，因为我们三角形这个面积不一定是正还是负
                    res=max(res,abs(area(a,b,c)));
        // 这里我们实际上求的是一个平行四边形的面积，所以最后面积要记得除以2.0
        // 两个整数做除法的话其实是取整那么就跟这个题目的要求不一样了
        return res/2.0;
    }
};
```







