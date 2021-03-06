---
layout:     post
title:		"计算机图形学2017年夏季作业-大作业"
subtitle:    "raytracing 光线跟踪"
date:	    2017-06-15 12:00:00
author:	   "slientuill-余沛然"
header-img: "img/post-bg-nextgen-web-pwa.jpg"
header-mask: 0.3
catalog:    true
tags:
- 图形学
- c++
- raytracing
---

> 



# 思路



**方式** 使用opencv库
- **1** ：引入opencv提供的三维向量类，并实现向量的点乘积；
``` cpp
typedef cv::Vec3d Vec3; 
static FLOAT operator*(const Vec3 &v1, const Vec3 &v2) { 
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]; 
}
```
- **2** ：定义光线：光线主要包含两个参数，光线发射点，光线方向 3；
```cpp
typedef Vec3 Vertex;//点
typedef Vec3 Vector;//方向
typedef std::pair<Vertex, Vector> Ray;//光线
```
- **3** ：定义物体，主要参数：反射系数，折射系数，折射指数，透明度
```cpp
#pragma once
#include "sdk.h"
namespace sdk {
class GeometricObject {
public:
    FLOAT reflection_coefficient,
          refraction_coefficient,
          refraction_index,
          transparency;
    virtual IntersectionPoint* ray_intersection_ptr(const Ray &ray) const = 0;
    GeometricObject(void);
    virtual ~GeometricObject(void) = 0;
};
}
```
- **4** ：定义物体子类，添加子类独有参数：位置P，大小（不同物体定义方式不同），法线n, 颜色RGB，与光线交互产生的行为。（例子为物体平面）
```cpp
#include "geometricobject.h"
namespace sdk {
class GOPlane :
    public GeometricObject
{
public:
    Vertex P;//位置
    Vector n;//法线向量
    BGRa bgra;//颜色
    IntersectionPoint* ray_intersection_ptr(const Ray &ray) const;//光线行为
    GOPlane(void);
    ~GOPlane(void);
};
```
- **5** ：具体描述特定物体（平面，球体，等）在光线场景中的行为，主要是是否与光线相交，以及与光线相交后的计算（例子为平面）

```cpp
#include "stdafx.h"
#include "GOPlane.h"
using namespace sdk;

IntersectionPoint* GOPlane::ray_intersection_ptr(const Ray &ray) const {
    const Vertex &Ro = ray.first;//获取光线起点
    const Vector &Rd = ray.second;//获取光线方向
//两个if用于判断物体与光线是否有交点
    FLOAT nRd = n * Rd;//法向量与光线夹角
    if (equal0(nRd))//法向量与光线垂直，光线与平面平行，不相交
        return NULL;
    FLOAT t = (n * (P - Ro)) / nRd;
    if (t < 0)//光线远离平面，不相交
        return NULL;
     //相交，则计算相交后的折射和反射行为
    IntersectionPoint *ip = new IntersectionPoint;
    ip->bgra = bgra;
    FLOAT rfi = nRd < 0 ? refraction_index : 1 / refraction_index;
    Vector I = Rd / sqrt(Rd * Rd),//单位光向量
           N = n / sqrt(n * n);//单位法向量
    FLOAT IN = I * N;//cosθ
    Vector R = I - 2 * IN * N,//i-2ncosθ
           T = I / rfi - (IN / rfi + sqrt(1 - (1 - IN * IN) / (rfi * rfi))) * N;
     //反射
    ip->t_vec.push_back(t * (1 - ZERO));
    ip->modulus_vec.push_back(reflection_coefficient);
    ip->direction_vec.push_back(R);
    //折射
    ip->t_vec.push_back(t * (1 + ZERO));
    ip->modulus_vec.push_back(refraction_coefficient);
    ip->direction_vec.push_back(T);
    //cerr << N << T << endl;
    return ip;
}
```
- **6** 定义Camera类，将3D图形投影到2d平面上

```cpp
#include "stdafx.h"
#include "Camera.h"
using namespace sdk;
BGRa Camera::recursion(int d, const Ray &ray) const {
    if (!d)
        return BGRa(0, 0, 0, 0);
    IntersectionPoint *res = scene->ray_intersection_ptr(ray);
    if (!res)
        return BGRa(0, 0, 0, 0);
    BGRa bgra(res->bgra);
    for (int i = 0; i < res->t_vec.size(); i++) {
        Vertex origion = ray.first + res->t_vec[i] * ray.second;
        bgra += res->modulus_vec[i] * recursion(d - 1, std::make_pair(origion, res->direction_vec[i]));
    }
    delete res;
    return bgra;
}
void Camera::get_image(const Vertex &O, const Rectangle &window, std::vector<std::vector<BGRa> > &image) const {
    int now = clock();

    int width = image.size(), height = image[0].size();
    Vector dx = window.x / width,
           dy = window.y / height;
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++) {
            Vertex P = window.P + x * dx + y * dy;
            image[x][y] = recursion(3, std::make_pair(P, P - O));
        }

    printf("time = %dms\n", clock() - now);
}

Camera::Camera(void) {
}
Camera::~Camera(void) {
}
```
- **7** 设定物体属性，将物体添加到场景中，需要说明的是，场景中的光源被设定为一个颜色纯白，完全不透明，完全不反射的一个球体
```cpp
sdk::GOSphere *light = new sdk::GOSphere;
    light->Pc = sdk::Vertex(0,100,700);
    light->reflection_coefficient = 0.0;
    light->r = 40;
    light->bgra = sdk::BGRa(255, 255, 255);//白色
    light->transparency = 0;//透明
    light->refraction_index = 1;
    light->refraction_coefficient = 0;
    camera->scene->geometric_object_ptr_vec.push_back(light);
```
# 效果展示
**说明：**
-场景中共有球体三个，平面三个，三个球体堆叠在一起，背后有两个法向量互相垂直，与视角平面成45°角的全反射无色平面，这5个物体下方是一个蓝色的平面
![example2](https://github.com/slientuill/slientuill.github.com/blob/master/img/%E6%95%88%E6%9E%9C%E5%9B%BE.jpg?raw=true)
-------------------
# 分析
**没有实现包围盒算法，使得光线必须遍历整个图像，运行出一个800X400的图至少需要两分钟，效率低下**






