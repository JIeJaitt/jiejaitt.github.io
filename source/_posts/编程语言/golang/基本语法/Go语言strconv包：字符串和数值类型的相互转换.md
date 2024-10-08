---
title: Go语言strconv包：字符串和数值类型的相互转换
excerpt: 本博客暂不显示摘要，请大家谅解
toc: true
abbrlink: c12d4784
date: 2021-08-31 21:50:58
categories: 编程语言
tags: 
    - Go
sticky:
---

在实际开发中我们往往需要对一些常用的数据类型进行转换，如 string、int、int64、float 等数据类型之间的转换，Go语言中的 strconv 包为我们提供了字符串和基本数据类型之间的转换功能。

strconv 包中常用的函数包括 Atoi()、Itia()、parse 系列函数、format 系列函数、append 系列函数等，下面就来分别介绍一下。

<!-- more -->

## string 与 int 类型之间的转换

字符串和整型之间的转换是我们平时编程中使用的最多的，下面就来介绍一下具体的操作。

#### Itoa()：整型转字符串

Itoa() 函数用于将 int 类型数据转换为对应的字符串类型，函数签名如下。

```go
func Itoa(i int) string
```

示例代码如下：

```go
func main() {
    num := 100
    str := strconv.Itoa(num)
    fmt.Printf("type:%T value:%#v\n", str, str)
}
```

运行结果如下所示：

```bash
type:string value:"100"
```

#### Atoi()：字符串转整型

Atoi() 函数用于将字符串类型的整数转换为 int 类型，函数签名如下。

```go
func Atoi(s string) (i int, err error)
```

通过函数签名可以看出 Atoi() 函数有两个返回值，i 为转换成功的整型，err 在转换成功是为空转换失败时为相应的错误信息。

示例代码如下：

```go
func main() {
    str1 := "110"
    str2 := "s100"
    num1, err := strconv.Atoi(str1)
    if err != nil {
        fmt.Printf("%v 转换失败！", str1)
    } else {
        fmt.Printf("type:%T value:%#v\n", num1, num1)
    }
    num2, err := strconv.Atoi(str2)
    if err != nil {
        fmt.Printf("%v 转换失败！", str2)
    } else {
        fmt.Printf("type:%T value:%#v\n", num2, num2)
    }
}
```

运行结果如下所示：

```bash
type:int value:110
s100 转换失败！
```

## Parse 系列函数

Parse 系列函数用于将字符串转换为指定类型的值，其中包括 ParseBool()、ParseFloat()、ParseInt()、ParseUint()。

#### ParseBool()

ParseBool() 函数用于将字符串转换为 bool 类型的值，它只能接受 1、0、t、f、T、F、true、false、True、False、TRUE、FALSE，其它的值均返回错误，函数签名如下。

```go
func ParseBool(str string) (value bool, err error)
```

示例代码如下：

```go
func main() {
    str1 := "110"
    boo1, err := strconv.ParseBool(str1)
    if err != nil {
        fmt.Printf("str1: %v\n", err)
    } else {
        fmt.Println(boo1)
    }
    str2 := "t"
    boo2, err := strconv.ParseBool(str2)
    if err != nil {
        fmt.Printf("str2: %v\n", err)
    } else {
        fmt.Println(boo2)
    }
}
```

运行结果如下：

```bash
str1: strconv.ParseBool: parsing "110": invalid syntax
true
```

#### ParseInt()

ParseInt() 函数用于返回字符串表示的整数值（可以包含正负号），函数签名如下：

```go
func ParseInt(s string, base int, bitSize int) (i int64, err error)
```

参数说明：

- base 指定进制，取值范围是 2 到 36。如果 base 为 0，则会从字符串前置判断，“0x”是 16 进制，“0”是 8 进制，否则是 10 进制。
- bitSize 指定结果必须能无溢出赋值的整数类型，0、8、16、32、64 分别代表 int、int8、int16、int32、int64。
- 返回的 err 是 *NumErr 类型的，如果语法有误，err.Error = ErrSyntax，如果结果超出类型范围 err.Error = ErrRange。


示例代码如下：



```go
func main() {
    str := "-11"
    num, err := strconv.ParseInt(str, 10, 0)
    if err != nil {
        fmt.Println(err)
    } else {
        fmt.Println(num)
    }
}
```

运行结果如下：

```bash
-11
```

#### ParseUnit()

ParseUint() 函数的功能类似于 ParseInt() 函数，但 ParseUint() 函数不接受正负号，用于无符号整型，函数签名如下：

```go
func ParseUint(s string, base int, bitSize int) (n uint64, err error)
```

示例代码如下：

```go
func main() {
    str := "11"
    num, err := strconv.ParseUint(str, 10, 0)
    if err != nil {
        fmt.Println(err)
    } else {
        fmt.Println(num)
    }
}
```

运行结果如下：

```bash
11
```

#### ParseFloat()

ParseFloat() 函数用于将一个表示浮点数的字符串转换为 float 类型，函数签名如下。

```go
func ParseFloat(s string, bitSize int) (f float64, err error)
```

参数说明：

- 如果 s 合乎语法规则，函数会返回最为接近 s 表示值的一个浮点数（使用 IEEE754 规范舍入）。
- bitSize 指定了返回值的类型，32 表示 float32，64 表示 float64；
- 返回值 err 是 *NumErr 类型的，如果语法有误 err.Error=ErrSyntax，如果返回值超出表示范围，返回值 f 为 ±Inf，err.Error= ErrRange。


示例代码如下：

```go
func main() {
    str := "3.1415926"
    num, err := strconv.ParseFloat(str, 64)
    if err != nil {
        fmt.Println(err)
    } else {
        fmt.Println(num)
    }
}
```

运行结果如下：

```bash
3.1415926
```

Parse 系列函数都有两个返回值，第一个返回值是转换后的值，第二个返回值为转化失败的错误信息。



## Format 系列函数

Format 系列函数实现了将给定类型数据格式化为字符串类型的功能，其中包括 FormatBool()、FormatInt()、FormatUint()、FormatFloat()。

#### FormatBool()

FormatBool() 函数可以一个 bool 类型的值转换为对应的字符串类型，函数签名如下。

```go
func FormatBool(b bool) string
```

示例代码如下：

```go
func main() {
    num := true
    str := strconv.FormatBool(num)
    fmt.Printf("type:%T,value:%v\n ", str, str)
}
```

运行结果如下：

```bash
type:string,value:true
```

#### FormatInt()

FormatInt() 函数用于将整型数据转换成指定进制并以字符串的形式返回，函数签名如下：

```go
func FormatInt(i int64, base int) string
```

其中，参数 i 必须是 int64 类型，参数 base 必须在 2 到 36 之间，返回结果中会使用小写字母 “a” 到“z”表示大于 10 的数字。

示例代码如下：

```go
func main() {
    var num int64 = 100
    str := strconv.FormatInt(num, 16)
    fmt.Printf("type:%T,value:%v\n ", str, str)
}
```

运行结果如下：

```bash
type:string,value:64
```

#### FormatUint()

FormatUint() 函数与 FormatInt() 函数的功能类似，但是参数 i 必须是无符号的 uint64 类型，函数签名如下。

```go
func FormatUint(i uint64, base int) string
```

示例代码如下：

```go
func main() {
    var num uint64 = 110
    str := strconv.FormatUint(num, 16)
    fmt.Printf("type:%T,value:%v\n ", str, str)
}
```

运行结果如下：

```bash
type:string,value:6e
```

#### FormatFloat()

FormatFloat() 函数用于将浮点数转换为字符串类型，函数签名如下：

```go
func FormatFloat(f float64, fmt byte, prec, bitSize int) string
```

参数说明：

- bitSize 表示参数 f 的来源类型（32 表示 float32、64 表示 float64），会据此进行舍入。
- fmt 表示格式，可以设置为“f”表示 -ddd.dddd、“b”表示 -ddddp±ddd，指数为二进制、“e”表示 -d.dddde±dd 十进制指数、“E”表示 -d.ddddE±dd 十进制指数、“g”表示指数很大时用“e”格式，否则“f”格式、“G”表示指数很大时用“E”格式，否则“f”格式。
- prec 控制精度（排除指数部分）：当参数 fmt 为“f”、“e”、“E”时，它表示小数点后的数字个数；当参数 fmt 为“g”、“G”时，它控制总的数字个数。如果 prec 为 -1，则代表使用最少数量的、但又必需的数字来表示 f。

示例代码如下：

```go
func main() {
    var num float64 = 3.1415926
    str := strconv.FormatFloat(num, 'E', -1, 64)
    fmt.Printf("type:%T,value:%v\n ", str, str)
}
```

运行结果如下：

```bash
type:string,value:3.1415926E+00
```

## Append 系列函数

Append 系列函数用于将指定类型转换成字符串后追加到一个切片中，其中包含 AppendBool()、AppendFloat()、AppendInt()、AppendUint()。

Append 系列函数和 Format 系列函数的使用方法类似，只不过是将转换后的结果追加到一个切片中。

示例代码如下：

```go
package main
import (
    "fmt"
    "strconv"
)
func main() {
    // 声明一个slice
    b10 := []byte("int (base 10):")
  
    // 将转换为10进制的string，追加到slice中
    b10 = strconv.AppendInt(b10, -42, 10)
    fmt.Println(string(b10))
    b16 := []byte("int (base 16):")
    b16 = strconv.AppendInt(b16, -42, 16)
    fmt.Println(string(b16))
}
```

运行结果如下：

```bash
int (base 10):-42
int (base 16):-2a
```