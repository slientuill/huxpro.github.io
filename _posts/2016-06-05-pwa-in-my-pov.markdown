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
