---
layout:     post
title:		"计算机图形学2017年春季作业二"
subtitle:    "RayTracing： Phong shading and Gouraud shading"
date:	    2017-04-12 12:00:00
author:	   "slientuill-余沛然"
header-img: "img/post-bg-nextgen-web-pwa.jpg"
header-mask: 0.3
catalog:    true
tags:
- 图形学
- RayTracing
- Phong shading
- Gouraud shading
---

> 

### 实现原理
  对于Gouraud shading，opengl的默认光线投射方案便是Gouraud shading 这里仅说明代码的具体思路
  跟上一个实验一样，首先初始化各种参数
   * 清空颜色和深度缓冲，创建透视效果图
   * 将坐标原点移动到中心
   * 对模型视景矩阵操作
   * 重置当前指定的矩阵为单位矩阵
   * 转换视点
然后便是本实验的两个主要部分
**光线**
对于opengl支持的光线投射算法，即Gouraud shading 需要设置4个参数
  * position 光源的位置
  * ambient 环境光（光源经过多次反射后遗留的光线强度）
  * diffuse 漫反射
  * specular 镜面反射
设置完成后启用该光照并在后面的渲染中使用
 * glEnable(gl_light0)
 * glEnable(gl_lighting)
**材质**
人眼看到物体的原因，不是我们看到了物体，而是物体本身吸收了白光中的部分，并将剩余的部分反射出来，
不同材质的物体 反射光线的能力也不同，与光线的四个参数对应，材质同样有相对应的参数需要设置
* ambient
* diffuse
* specular
* emission
不同的是材质中多了一个参数
 * Shininess
表示材质的 属性
设置完成以后使用SolidShpere绘制一个球，不同于上一次的实验，这次opengl的物体除了要设置各个顶点的坐标，
还需要额外设置一个法线的参数用于完成光线反射的实现，而我们使用SolidShpere函数则**不需要指定法线**
**Phong shading**

