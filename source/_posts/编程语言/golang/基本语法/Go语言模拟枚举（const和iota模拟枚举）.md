---
title: Go语言模拟枚举（const和iota模拟枚举）
toc: true
abbrlink: 647cb4a1
date: 2021-08-31 21:46:00
categories: 编程语言
tags: 
    - Go
sticky:
---

Go语言现阶段没有枚举类型，但是可以使用 const 常量配合Go语言常量中的 iota 来模拟枚举类型，请看下面的代码：

<!-- more -->

```go
type Weapon int

const (
     Arrow Weapon = iota    // 开始生成枚举值, 默认为0
     Shuriken
     SniperRifle
     Rifle
     Blower
)

// 输出所有枚举值
fmt.Println(Arrow, Shuriken, SniperRifle, Rifle, Blower)

// 使用枚举类型并赋初值
var weapon Weapon = Blower
fmt.Println(weapon)
```

代码输出如下：

```bash
0 1 2 3 4
4
```

代码说明如下：
第 1 行中，将 int 定义为 Weapon 类型，就像枚举类型的本质是一个 int 类型一样。当然，某些情况下，如果需要 int32 和 int64 的枚举，也是可以的。

第 4 行中，将常量 Arrow 的类型标识为 Weapon，这样标识后，const 下方的常量可以使用 Weapon 作为默认类型。该行使用 iota 进行常量值自动生成，iota 的起始值为 0，一般情况下也是建议枚举从 0 开始，让每个枚举类型都有一个空值，方便业务和逻辑的灵活使用。

一个 const 声明内的每一行常量声明，将会自动套用前面的 iota 格式，并自动增加，类似于电子表格中单元格自动填充的效果，只需要建立好单元格之间的变化关系，拖动右下方的小点就可以自动生成单元格的值。

当然，iota 不仅可以生成每次增加 1 的枚举值。还可以利用 iota 来做一些强大的枚举常量值生成器。下面的代码可以方便的生成标志位常量：

```go
const (
    FlagNone = 1 << iota
    FlagRed
    FlagGreen
    FlagBlue
)

fmt.Printf("%d %d %d\n", FlagRed, FlagGreen, FlagBlue)
fmt.Printf("%b %b %b\n", FlagRed, FlagGreen, FlagBlue)
```

代码输出如下：

```bash
2 4 8
10 100 1000
```

在代码中编写一些标志位时，我们往往手动编写常量值，常量值特别多时，很容易重复或者写错，因此，使用 ioto 自动生成更加方便。

代码说明如下：

- 第 2 行中 iota 使用了一个移位操作，每次将上一次的值左移一位（二进制位），以得出每一位的常量值。
- 第 8 行，将 3 个枚举按照常量输出，分别输出 2、4、8，都是将 1 每次左移一位的结果。
- 第 9 行，将枚举值按二进制格式输出，可以清晰地看到每一位的变化。

## 将枚举值转换为字符串

枚举在 C# 中是一个独立的类型，可以通过枚举值获取该值对应的字符串。例如，C# 中 Week 枚举值 Monday 为 1，那么可以通过 Week.Monday.ToString() 函数获得 Monday 字符串。

Go语言中也可以实现这一功能，代码如下所示：

转换字符串：

```go
package main

import "fmt"

// 声明芯片类型
type ChipType int

const (
    None ChipType = iota
    CPU    // 中央处理器
    GPU    // 图形处理器
)

func (c ChipType) String() string {
    switch c {
    case None:
        return "None"
    case CPU:
        return "CPU"
    case GPU:
        return "GPU"
    }

    return "N/A"
}

func main() {

    // 输出CPU的值并以整型格式显示
    fmt.Printf("%s %d", CPU, CPU)
}
```

运行结果：

```bash
CPU 1
```

代码说明如下：

- 第 6 行，将 int 声明为 ChipType 芯片类型。
- 第 9 行，将 const 里定义的常量值设为 ChipType 类型，且从 0 开始，每行值加 1。
- 第 14 行，定义 ChipType 类型的方法 String()，返回值为字符串类型。
- 第 15～22 行，使用 switch 语句判断当前的 ChitType 类型的值，返回对应的字符串。
- 第 30 行，按整型的格式输出 CPU 的值。


String() 方法的 ChipType 在使用上和普通的常量没有区别。当这个类型需要显示为字符串时，Go语言会自动寻找 String() 方法并进行调用。