---
layout:     post
title:		"计算机图形学2017年春季作业一"
subtitle:    "使用opengl制作移动的小人"
date:	    2017-04-01 12:00:00
author:	   "slientuill-余沛然"
header-img: "img/post-bg-nextgen-web-pwa.jpg"
header-mask: 0.3
catalog:    true
tags:
    - 图形学
    - c++
    - moving man
---

> 


### 代码
  [Demo Code → ](https://slientuill.github.io/movingman.cpp)
### 简单思路
 - 1 - 首先，使用opengl提供的连线函数，对于设定好的长方体八个顶点的矩阵数据进行逐一连线（drawcube函数），形成构建小人所需的基本部件（头部，躯干，肩部，四肢）
 - 2 - 使用gltranslate函数对各个部位进行摆放，形成小人的雏形，期间，使用pushmatrix和popmatrix函数，将各个部位隔离开来，同时，记得所有的translate函数rotate的函数要在drawcube方法前调用，否则摆放的位置将会形成错乱，需要注意的一点是小人的大臂和小臂属于同一结构，虽然使用了两个长方体，但中间不使用pop和push将其隔离，并且在后续的移动函数中，可以通过大臂来带动小臂旋转
 - 3 - 使用move函数和selfrotate函数来形成小人的移动以及手臂和腿的旋转
 	- move：通过times的叠加，使得translate函数中x和y轴的参变量逐步增大，在所有的部件中调用（大小臂只调用一次）实现小人的整体移动
	- selfrotate：通过times的叠加，使得rotate函数中的rotateangle参数在逐步增大，并在达到临界值时反向，以达到回旋的效果， 其中小人的左半部和右半部分别使用两个参数相反的函数（selfrotateR和selfrotateL）从而实现正确的步姿
### 简单演示
  [外部网页 → ](http://v.youku.com/v_show/id_XMjY4OTczNzk0MA==.html?spm=a2hzp.8253869.0.0&from=y1.7-2#paction)
<video src="https://slientuill.github.io/movie2.mp4" autostart="true" loop="true" width="800" height="400"></video>
<embed src='http://player.youku.com/player.php/sid/XMjY4OTczNzk0MA==/v.swf' allowFullScreen='true' quality='high' width='480' height='400' align='middle' allowScriptAccess='always' type='application/x-shockwave-flash'></embed>

<iframe height=498 width=510 src='http://player.youku.com/embed/XMjY4OTczNzk0MA==' frameborder=0></iframe>

