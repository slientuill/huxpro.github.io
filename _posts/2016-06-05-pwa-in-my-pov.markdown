---
layout:     post
title:		"啊呀golang真的是有意思啊"
subtitle:    "过go指南写的作业"
date:	    2017-07-25 19:00:00
author:	   "slientuill-余沛然"
header-img: "img/post-bg-nextgen-web-pwa.jpg"
header-mask: 0.3
catalog:    true
tags:
    - Go
    - slice
    - map
---

> 

### 练习：循环和函数
作为练习函数和循环的简单途径，用牛顿法实现开方函数。

在这个例子中，牛顿法是通过选择一个初始点 z 然后重复这一过程求 Sqrt(x) 的近似值：


为了做到这个，只需要重复计算 10 次，并且观察不同的值（1，2，3，……）是如何逐步逼近结果的。 然后，修改循环条件，使得当值停止改变（或改变非常小）的时候退出循环。观察迭代次数是否变化。结果与 math.Sqrt 接近吗？

提示：定义并初始化一个浮点值，向其提供一个浮点语法或使用转换：

z := float64(1)
z := 1.0
```
package main

import (
	"fmt"
	"math"
)

func Sqrt(x float64) float64{
	z:=1.0
	for {
	  temp:=z
	  z=z-(z*z-x)/2*z
	  //fmt.Println(z)
	  //fmt.Println(temp-z)
		if temp-z<0.0001&&temp-z>-0.0001{
			return z
		}
		
	}
}

func main() {
	fmt.Println(Sqrt(2))
	fmt.Println(math.Sqrt(2))
	//Sqrt(2)
}
```

###  练习：slice
题目 实现 Pic 。它返回一个长度为 dy 的 slice，其中每个元素是一个长度为 dx 且元素类型为8位无符号整数的 slice。当你运行这个程序时， 它会将每个整数作为对应像素的灰度值（好吧，其实是蓝度）并显示这个 slice 所对应的图像。

计算每个像素的灰度值的方法由你决定；几个有意思的选择包括 (x+y)/2、x*y 和 x^y 。

（需要使用循环来分配 [][]uint8 中的每个 []uint8 。）

（使用 uint8(intValue) 来在类型之间进行转换。）
代码
```
package main

import "golang.org/x/tour/pic"

func Pic(dx, dy int) [][]uint8 {
    // 外层slice
    a := make([][]uint8, dy)
    for x := range a {
        // 里层slice
        b := make([]uint8, dx)
        for y := range b {
            // 给里层slice每个元素赋值
            b[y] = uint8((x+y)/2)
        }
        // 给外层slice每个元素赋值
        a[x] = b
    }
    return a
}

func main() {
	pic.Show(Pic)
}

```
### 练习：map
题目 实现 WordCount。它应当返回一个含有 s 中每个 “词” 个数的 map。函数 wc.Test 针对这个函数执行一个测试用例，并输出成功还是失败。
代码
```
package main

import (
	"golang.org/x/tour/wc"
	//"fmt"
	"strings"
)

func WordCount(s string) map[string]int {
	m:=make (map[string]int)
	a:=strings.Fields(s)
	for i:=0;i<len(a);i++{
	 	if _,ok:= m[a[i]];!ok{
		      m[a[i]]=1	
		} else {
			m[a[i]]++
		}
	}
	return m;
}

func main() {
	wc.Test(WordCount)
	
}
```
### 练习：斐波纳契闭包
现在来通过函数做些有趣的事情。

实现一个 fibonacci 函数，返回一个函数（一个闭包）可以返回连续的斐波纳契数。
```
package main

import "fmt"

// fibonacci 函数会返回一个返回 int 的函数。
func fibonacci() func() int {
	 sum, sum1:= 0, 1 
	 return func() int {
		 temp:=sum
		 sum,sum1=sum1,(sum + sum1)
        return temp
    }
}

func main() {
	f := fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Println(f())
	}
}
```

### 练习：Stringers
让 IPAddr 类型实现 fmt.Stringer 以便用点分格式输出地址。

例如，IPAddr{1, 2, 3, 4} 应当输出 "1.2.3.4"。
```
package main

import "fmt"

type IPAddr [4]byte

// TODO: Add a "String() string" method to IPAddr.
func (i IPAddr) String() string{
	return fmt.Sprintf("%d.%d.%d.%d",i[0],i[1],i[2],i[3])
}

func main() {
	addrs := map[string]IPAddr{
		"loopback":  {127, 0, 0, 1},
		"googleDNS": {8, 8, 8, 8},
	}
	for n, a := range addrs {
		fmt.Printf("%v: %v\n", n, a)
	}
}
```

### 练习：错误
从先前的练习中复制 Sqrt 函数，并修改使其返回 error 值。

由于不支持复数，当 Sqrt 接收到一个负数时，应当返回一个非 nil 的错误值。

创建一个新类型

type ErrNegativeSqrt float64
为其实现

func (e ErrNegativeSqrt) Error() string
使其成为一个 error， 该方法就可以让 ErrNegativeSqrt(-2).Error() 返回 `"cannot Sqrt negative number: -2"`。

*注意：* 在 Error 方法内调用 fmt.Sprint(e) 将会让程序陷入死循环。可以通过先转换 e 来避免这个问题：fmt.Sprint(float64(e))。请思考这是为什么呢？

修改 Sqrt 函数，使其接受一个负数时，返回 ErrNegativeSqrt 值。
```
package main

import (
	"fmt"
)
type ErrNegativeSqrt float64
func (e ErrNegativeSqrt) Error() string{
  return fmt.Sprintf("cannot Sqrt negative number:%v",float64(e))
}
func Sqrt(x float64) (float64, error) {
	if x<0{
		return 0,ErrNegativeSqrt(x)
	} else{  z:=1.0
	for {
	  temp:=z
	  z=z-(z*z-x)/2*z
	  //fmt.Println(z)
	  //fmt.Println(temp-z)
		if temp-z<0.0001&&temp-z>-0.0001{
			return z,nil
		}
		
	}
	
	}

	
}

func main() {
	fmt.Println(Sqrt(2))
	fmt.Println(Sqrt(-2))
}
```
### 练习：rot13Reader
一个常见模式是 io.Reader 包裹另一个 io.Reader，然后通过某种形式修改数据流。

例如，gzip.NewReader 函数接受 io.Reader（压缩的数据流）并且返回同样实现了 io.Reader 的 *gzip.Reader（解压缩后的数据流）。

编写一个实现了 io.Reader 的 rot13Reader， 并从一个 io.Reader 读取， 利用 rot13 代换密码对数据流进行修改。

已经帮你构造了 rot13Reader 类型。 通过实现 Read 方法使其匹配 io.Reader。
```
package main

import (
	"io"
	"os"
	"strings"
)

type rot13Reader struct {
	r io.Reader
}
func rot13(b byte) byte {
    switch {
    case 'A' <= b && b <= 'M':
        b = b + 13
    case 'M' < b && b <= 'Z':
        b = b - 13
    case 'a' <= b && b <= 'm':
        b = b + 13
    case 'm' < b && b <= 'z':
        b = b - 13
    }
    return b
}
// 重写Read方法
func (mr rot13Reader) Read(b []byte) (int, error) {
    n, e := mr.r.Read(b)
    for i := 0; i < n; i++ {
        b[i] = rot13(b[i])
    }
    return n, e
}

func main() {
	s := strings.NewReader("Lbh penpxrq gur pbqr!")
	r := rot13Reader{s}
	io.Copy(os.Stdout, &r)
}
```
