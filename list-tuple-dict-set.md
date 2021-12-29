Python 序列（Sequence）是指按特定顺序依次排列的一组数据，它们可以占用一块连续的内存，也可以分散到多块内存中。Python 中的序列类型包括列表（list）、元组（tuple）、字典（dict）和集合（set）。<br />在 Python 编程中，我们既需要独立的变量来保存一份数据，也需要序列来保存大量数据。<br />列表（list）和元组（tuple）比较相似，它们都按顺序保存元素，所有的元素占用一块连续的内存，每个元素都有自己的索引，因此列表和元组的元素都可以通过索引（index）来访问。它们的区别在于：列表是可以修改的，而元组是不可修改的。<br />字典（dict）和集合（set）存储的数据都是无序的，每份元素占用不同的内存，其中字典元素以 key-value 的形式保存。<br />​<br />
<a name="Dq9gd"></a>
# 什么是序列，Python序列详解（包括序列类型和常用操作）
所谓序列，指的是一块可存放多个值的连续内存空间，这些值按一定顺序排列，可通过每个值所在位置的编号（称为索引）访问它们。

为了更形象的认识序列，可以将它看做是一家旅店，那么店中的每个房间就如同序列存储数据的一个个内存空间，每个房间所特有的房间号就相当于索引值。也就是说，通过房间号（索引）我们可以找到这家旅店（序列）中的每个房间（内存空间）。

在 Python中，序列类型包括字符串、列表、元组、集合和字典，这些序列支持以下几种通用的操作，但比较特殊的是，集合和字典不支持索引、切片、相加和相乘操作。<br />字符串也是一种常见的序列，它也可以直接通过索引访问字符串内的字符。<br />​<br />
<a name="GZ8h0"></a>
## 序列索引
序列中，每个元素都有属于自己的编号（索引）。从起始元素开始，索引值从 0 开始递增，如图 1 所示。

![](https://cdn.nlark.com/yuque/0/2021/gif/22765337/1640265728707-b52b2159-1693-4267-85b5-75b3103c3e78.gif#clientId=u047aa54b-0224-4&crop=0&crop=0&crop=1&crop=1&from=paste&id=u830a9f46&margin=%5Bobject%20Object%5D&originHeight=79&originWidth=600&originalType=url&ratio=1&rotation=0&showTitle=false&status=done&style=none&taskId=u4ff86455-e30e-4a41-8cfd-7a5bb045610&title=)<br />图 1 序列索引值示意图

除此之外，Python 还支持索引值是负数，此类索引是从右向左计数，换句话说，从最后一个元素开始计数，从索引值 -1 开始，如图 2 所示。

![](https://cdn.nlark.com/yuque/0/2021/gif/22765337/1640265728687-66c543d9-156d-4a17-b939-a09bfea39225.gif#clientId=u047aa54b-0224-4&crop=0&crop=0&crop=1&crop=1&from=paste&id=u38daf1d9&margin=%5Bobject%20Object%5D&originHeight=77&originWidth=600&originalType=url&ratio=1&rotation=0&showTitle=false&status=done&style=none&taskId=u651a71a6-43fd-45a1-ba5a-86dbb9c42ac&title=)<br />图 2 负值索引示意图<br />注意，在使用负值作为列序中各元素的索引值时，是从 -1 开始，而不是从 0 开始。<br />无论是采用正索引值，还是负索引值，都可以访问序列中的任何元素。以字符串为例，访问“C语言中文网”的首元素和尾元素，可以使用如下的代码：
```python
str="C语言中文网"
print(str[0],"==",str[-6])
print(str[5],"==",str[-1])
```
**​**

输出结果为：
```bash
C == C
网 == 网
```

















## Python dict字典详解
Python 字典（dict）是一种无序的、可变的序列，它的元素以“键值对（key-value）”的形式存储。相对地，列表（list）和元组（tuple）都是有序