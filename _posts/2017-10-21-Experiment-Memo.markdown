---
layout:     post
title:		"备忘"
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
-1- 下载安装 Visual Studio，OPENSSL，ActivePerl
-2- win+R 调出运行 输入cmd 回车 进入命令行
-3- 进入Visual studio\VC文件夹 
```
>vcvarshall.bat amd64
>cd ..
>cd ..
>cd openssl-1.0.2l
>perl Configure VC-WIN64A
> ms\do_win64a
> nmake -f ms\ntdll.mak
> cd out32dll
> ..\ms\test
```
显示多行 ....ok 即编译成功
### 人机交互

