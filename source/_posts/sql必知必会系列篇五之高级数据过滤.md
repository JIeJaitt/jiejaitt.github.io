---
title: sql必知必会系列篇五之高级数据过滤
---


这一课讲授如何组合**WHERE**子句以建立功能更强、更高级的搜索条件。我们还将学习如何使用**NOT**和**IN**操作符。

<!-- more -->

## 组合WHERE子句
篇四介绍的所有**WHERE**子句在过滤数据时使用的都是单一的条件。为了进行更强的过滤控制，**SQL**允许给出多个**WHERE**子句。这些子句有两种使用方式，即以**AND**子句或**OR**子句的方式使用。

> 操作符（operator）
用来联结或改变WHERE子句中的子句的关键字，也称为逻辑操作符（logical operator）。

### AND操作符
要通过不止一个列进行过滤，可以使用AND操作符给WHERE子句附加条件。下面的代码给出了一个例子：

输入▼
```sql
SELECT prod_id, prod_price, prod_name
FROM Products
WHERE vend_id = 'DLL01' AND prod_price
<= 4;
```
分析▼
此**SQL**语句检索由供应商**DLL01**制造且价格小于等于**4**美元的所有品的名称和价格。这条**SELECT**语句中的**WHERE**子句包含两个条件，用**AND**关键字联结在一起。**AND**指示**DBMS**只返回满足所有给定条件的行。如果某个产品由供应商**DLL01**制造，但价格高于**4**美元，则不检索它。类似地，如果产品价格小于**4**美元，但不是由指定供应商制造的也不被检索。这条**SQL**语句产生的输出如下：

```bash
+---------+------------+---------------------+
| prod_id | prod_price | prod_name           |
+---------+------------+---------------------+
| BNBG01  |       3.49 | Fish bean bag toy   |
| BNBG02  |       3.49 | Bird bean bag toy   |
| BNBG03  |       3.49 | Rabbit bean bag toy |
+---------+------------+---------------------+
```

> **AND**
用在**WHERE**子句中的关键字，用来指示检索满足所有给定条件的行。

这个例子只包含一个**AND**子句，因此最多有两个过滤条件。可以增加多个过滤条件，每个条件间都要使用**AND**关键字。

> 说明：没有**ORDER BY**子句
为了节省空间，也为了减少你的输入，我在很多例子里省略了**ORDER BY**子句。因此，你的输出完全有可能与书上的输出不一致。虽然返回行的数量总是对的，但它们的顺序可能不同。当然，如果你愿意也可以加上一个**ORDER BY**子句，它应该放在**WHERE**子句之后。



### OR操作符
**OR**操作符与**AND**操作符正好相反，它指示**DBMS**检索匹配任一条件的行。事实上，许多**DBMS**在**OR WHERE**子句的第一个条件得到满足的情况下，就不再计算第二个条件了（在第一个条件满足时，不管第二个条件是否满足，相应的行都将被检索出来）。

请看如下的**SELECT**语句：

输入▼

```sql
SELECT prod_name, prod_price
FROM Products
WHERE vend_id = 'DLL01' OR vend_id ='BRS01';
```
分析▼
此**SQL**语句检索由任一个指定供应商制造的所有产品的产品名和价格。**OR**操作符告诉**DBMS**匹配任一条件而不是同时匹配两个条件。如果这里使用的是**AND**操作符，则没有数据返回（因为会创建没有匹配行的**WHERE**子句）。这条**SQL**语句产生的输出如下：

```bash
+---------------------+------------+
| prod_name           | prod_price |
+---------------------+------------+
| 8 inch teddy bear   |       5.99 |
| 12 inch teddy bear  |       8.99 |
| 18 inch teddy bear  |      11.99 |
| Fish bean bag toy   |       3.49 |
| Bird bean bag toy   |       3.49 |
| Rabbit bean bag toy |       3.49 |
| Raggedy Ann         |       4.99 |
+---------------------+------------+
```

> **OR**
**WHERE**子句中使用的关键字，用来表示检索匹配任一给定条件的行。

### 求值顺序
**WHERE**子句可以包含任意数目的**AND**和**OR**操作符。允许两者结合以进行复杂、高级的过滤。

但是，组合**AND**和**OR**会带来了一个有趣的问题。为了说明这个问题，来看一个例子。假如需要列出价格为**10**美元及以上，且由**DLL01**或**BRS01**制造的所有产品。下面的**SELECT**语句使用组合的**AND**和**OR**操作建立了一个**WHERE**子句：

输入▼
```sql
SELECT prod_name, prod_price
FROM Products
WHERE vend_id = 'DLL01' OR vend_id = 'BRS01'
AND prod_price >= 10;
```
输出▼

```bash
+---------------------+------------+
| prod_name           | prod_price |
+---------------------+------------+
| 18 inch teddy bear  |      11.99 |
| Fish bean bag toy   |       3.49 |
| Bird bean bag toy   |       3.49 |
| Rabbit bean bag toy |       3.49 |
| Raggedy Ann         |       4.99 |
+---------------------+------------+
```
分析▼
请看上面的结果。返回的行中有**4**行价格小于**10**美元，显然，返回的行未按预期的进行过滤。为什么会这样呢？原因在于求值的顺序。**SQL**（像多数语言一样）在处理OR操作符前，优先处理**AND**操作符。当**SQL**看到上述**WHERE**子句时，它理解为：由供应商**BRS01**制造的价格为**10**美元以上的所有产品，以及由供应商**DLL01**制造的所有产品，而不管其价格如何。换句话说，由于**AND**在求值过程中优先级更高，操作符被错误地组合了。

此问题的解决方法是使用圆括号对操作符进行明确分组。请看下面**SELECT**
语句及输出：

```sql
SELECT prod_name, prod_price
FROM Products
WHERE (vend_id = 'DLL01' OR vend_id = 'BRS01')
AND prod_price >= 10;
```
输出▼
```bash
+--------------------+------------+
| prod_name          | prod_price |
+--------------------+------------+
| 18 inch teddy bear |      11.99 |
+--------------------+------------+
```
分析▼
这条**SELECT**语句与前一条的唯一差别是，将前两个条件用圆括号括了起来。因为圆括号具有比**AND**或**OR**操作符更高的求值顺序，所以**DBMS**首先过滤圆括号内的**OR**条件。这时，**SQL**语句变成了选择由供应商**DLL01**或**BRS01**制造的且价格在**10**美元及以上的所有产品，这正是我们希望的结果。

> 提示：在**WHERE**子句中使用圆括号
任何时候使用具有**AND**和**OR**操作符的**WHERE**子句，都应该使用圆括号明确地分组操作符。不要过分依赖默认求值顺序，即使它确实如你希望的那样。使用圆括号没有什么坏处，它能消除歧义。

## IN操作符
**IN**操作符用来指定条件范围，范围中的每个条件都可以进行匹配。**IN**取一组由逗号分隔、括在圆括号中的合法值。下面的例子说明了这个操作符：

输入▼

```sql
SELECT prod_name, prod_price
FROM Products
WHERE vend_id IN ( 'DLL01', 'BRS01' )
ORDER BY prod_name;
```
输出▼

```bash
+---------------------+------------+
| prod_name           | prod_price |
+---------------------+------------+
| 12 inch teddy bear  |       8.99 |
| 18 inch teddy bear  |      11.99 |
| 8 inch teddy bear   |       5.99 |
| Bird bean bag toy   |       3.49 |
| Fish bean bag toy   |       3.49 |
| Rabbit bean bag toy |       3.49 |
| Raggedy Ann         |       4.99 |
+---------------------+------------+
```
分析▼
此**SELECT**语句检索由供应商**DLL01**和**BRS01**制造的所有产品。**IN**操作符后跟由逗号分隔的合法值，这些值必须括在圆括号中。

你可能会猜测**IN**操作符完成了与**OR**相同的功能，恭喜你猜对了！下面的**SQL**语句完成与上面的例子相同的工作：

输入▼

```sql
SELECT prod_name, prod_price
FROM Products
WHERE vend_id = 'DLL01' OR vend_id ='BRS01'
ORDER BY prod_name;
```
输出▼

```bash
+---------------------+------------+
| prod_name           | prod_price |
+---------------------+------------+
| 12 inch teddy bear  |       8.99 |
| 18 inch teddy bear  |      11.99 |
| 8 inch teddy bear   |       5.99 |
| Bird bean bag toy   |       3.49 |
| Fish bean bag toy   |       3.49 |
| Rabbit bean bag toy |       3.49 |
| Raggedy Ann         |       4.99 |
+---------------------+------------+
```
为什么要使用**IN**操作符？其优点为：

- 在有很多合法选项时，**IN**操作符的语法更清楚，更直观。
- 在与其他**AND**和**OR**操作符组合使用**IN**时，求值顺序更容易管理。
- **IN**操作符一般比一组**OR**操作符执行得更快（在上面这个合法选项很少的例子中，你看不出性能差异）。
- **IN**的最大优点是可以包含其他**SELECT**语句，能够更动态地建立
**WHERE**子句。篇11会对此进行详细介绍。

> **IN**
**WHERE**子句中用来指定要匹配值的清单的关键字，功能与**OR**相当。

## NOT操作符
**WHERE**子句中的**NOT**操作符有且只有一个功能，那就是否定其后所跟的任何条件。因为**NOT**从不单独使用（它总是与其他操作符一起使用），所以它的语法与其他操作符有所不同。**NOT**关键字可以用在要过滤的列前，而不仅是在其后。

> **NOT**
**WHERE**子句中用来否定其后条件的关键字。

下面的例子说明**NOT**的用法。为了列出除**DLL01**之外的所有供应商制造的产品，可编写如下的代码：

输入▼

```sql
SELECT prod_name
FROM Products
WHERE NOT vend_id = 'DLL01'
ORDER BY prod_name;
```
输出▼

```bash
+--------------------+
| prod_name          |
+--------------------+
| 12 inch teddy bear |
| 18 inch teddy bear |
| 8 inch teddy bear  |
| King doll          |
| Queen doll         |
+--------------------+
```
分析▼
这里的**NOT**否定跟在其后的条件，因此，**DBMS**不是匹配**vend_id**为**DLL01**，而是匹配非**DLL01**之外的所有东西。

上面的例子也可以使用 <> 操作符来完成，如下所示：

输入▼

```sql
SELECT prod_name
FROM Products
WHERE vend_id <> 'DLL01'
ORDER BY prod_name;
```
输出▼

```bash
+--------------------+
| prod_name          |
+--------------------+
| 12 inch teddy bear |
| 18 inch teddy bear |
| 8 inch teddy bear  |
| King doll          |
| Queen doll         |
+--------------------+
```
分析▼
为什么使用**NOT**？对于这里的这种简单的**WHERE**子句，使用**NOT**确实没有什么优势。但在更复杂的子句中，**NOT**是非常有用的。例如，在与**IN**操作符联合使用时，**NOT**可以非常简单地找出与条件列表不匹配的行。

> 说明： **MariaDB** 中的 **NOT**
> **MariaDB** 支持使用 **NOT** 否 定 **IN** 、 **BETWEEN** 和 **EXISTS** 子句。大多数 **DBMS** 允许使用 **NOT**否定任何条件。

## 小结
本文讲授如何用 **AND** 和 **OR** 操作符组合成 **WHERE** 子句，还讲授了如何明确地管理求值顺序，如何使用 **IN** 和 **NOT** 操作符。

