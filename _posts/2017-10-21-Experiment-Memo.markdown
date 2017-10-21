---
layout:     post
title:		"2017年秋季实验课"
subtitle:    "Experiment"
date:	    2017-10-21 19:00:00
author:	   "slientuill-余沛然"
header-img: "img/post-bg-nextgen-web-pwa.jpg"
header-mask: 0.3
catalog:    true
tags:
- 人机交互
- 信息安全
- WEB技术
- 网络攻防
---

> 

### 信息安全
WINDOWS64下 OPENSSL配置  

[ActivePerl](http://www.activestate.com/activeperl/downloads/)  
[OpenSSL](http://www.openssl.org/source/)  
-1- 下载安装 Visual Studio，OPENSSL，ActivePerl  
-2- win+R 调出运行 输入cmd 回车 进入命令行  
-3- 进入Visual studio\VC文件夹 
```
>vcvarshall.bat amd64
>cd openssl-1.0.2l
>perl Configure VC-WIN64A
>ms\do_win64a
>nmake -f ms\ntdll.mak
>cd out32dll
>..\ms\test
```
显示多行 ....ok 即编译成功
#### 使用OpenSSL  
1. 新建一个工程  
2. 设置目录参数  
右击工程名——属性——

1）配置属性——VC++目录——在include目录中新增"d:\openssl_lib\include"(存放编译后的库文件的目录中)；

2）VC++目录——"Library files"选择中新增目录"d:\openssl_lib\lib"。

3）配置属性——链接器——输入——附加依赖项——libeay32.lib 和ssleay32.lib

4)把上述两个lib丢到

5)配置管理器改为64位
### 人机交互

