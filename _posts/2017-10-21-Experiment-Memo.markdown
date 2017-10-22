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
WINDOWS64位下 Openssl配置  

[点击进入ActivePerl下载页](http://www.activestate.com/activeperl/downloads/)  
[点击进入OpenSSL下载页](http://www.openssl.org/source/)  
-1- 安装 Visual Studio，OPENSSL，ActivePerl  
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

1）配置属性——VC++目录——包含目录-新增"d:\openssl\inc32"

2）VC++目录——库目录-新增"d:\openssl\out32dll"

3）配置属性——链接器——输入——附加依赖项——libeay32.lib 和ssleay32.lib

4) 把上述两个lib丢到C:\windows\system32下

5) 配置管理器改为64位
#### 代码
```
#include <openssl/bio.h>

#include <openssl/err.h>
#include <openssl/ssl.h>
#include <openssl/des.h>
#include <openssl/applink.c>

#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")
//密钥为固定的8位
//加密内容8位补齐，补齐方式为：少1位补一个0x01,少2位补两个0x02,...
void des_ecb(const char *data,const char *key) {
	int right = 1;
	
	int data_len;//数据本身的长度
	int data_lack_len;//缺少的长度
	int data_full_len;//补齐后的长度
	unsigned char supply;//不足，补齐
	unsigned char *realData = NULL;//补齐后的明文
	unsigned char *encryData = NULL;//加密后的密文
	
	unsigned char in[8];
	unsigned char out[8];
	
	DES_key_schedule ks;

	//**************
	data_len = strlen(data);
	data_lack_len = data_len % 8;
	data_full_len = data_len + (8 - data_lack_len);
	supply = 8 - data_lack_len;
	realData = (unsigned char *)malloc(data_full_len);
	encryData = (unsigned char *)malloc(data_full_len);
	if (NULL == realData||NULL == encryData)
		right = 0;
	if (right) {
		int count;//加密所需要的次数
		int i;
		//补齐data的长度
		memset(realData, 0, data_full_len);
		memcpy(realData, data, data_len);
		memset(realData + data_len, supply, 8 - data_lack_len);
		DES_set_key_unchecked((const_DES_cblock*)key, &ks);
		printf("before encrypt:\n");
		for (i = 0; i < data_full_len; i++)
		{
			printf("0x%.2X ", *(realData + i));
		}
		printf("\n");
		/* 循环加密，每8字节一次 */
		count = data_full_len / 8;
		for (i = 0; i < count; i++) {
			memset(in, 0, 8);
			memset(out, 0, 8);
			memcpy(in, realData + 8 * i, 8);//每次拷贝8个字节到in中
			/* 加密 */
			DES_ecb_encrypt((const_DES_cblock*)in, (DES_cblock*)out, &ks, DES_ENCRYPT);
			//每次拷贝8个字节出来
			memcpy(encryData + 8 * i, out, 8);
		}
		printf("after encrypt :\n");
		for (i = 0; i < data_full_len; i++)
		{
			printf("0x%.2X ", *(encryData + i));
		}
		printf("\n");
	}
}

int main() {
	char *data = "i have not been encrypted yet";
	char *key = "2389342";//密钥必须为8位
	des_ecb(data,key);
	system("pause");
	return 0;
}
```
### 人机交互

