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
#### WINDOWS64位下 Openssl配置  
1. 下载安装或解压  
[点击进入ActivePerl下载页](http://www.activestate.com/activeperl/downloads/)  
[点击进入OpenSSL下载页](http://www.openssl.org/source/)  
[点击进入Visual Studio下载页](http://www.visualstudio.com/)

2. WIN+R 调出运行 输入cmd 回车 进入命令行界面 
进入Visual studio\VC 文件夹
比如我的：
```
>D:
>cd visualstudio
>cd VC
```
执行
```
>vcvarshall.bat amd64
```
**在当前窗口下** 进入openssl解压目录 逐个执行
```
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
#include <openssl/aes.h>  
#include <openssl/rand.h> 
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <openssl/des.h>
#include <openssl/applink.c>
#include <openssl/rc4.h> 

#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")
//加密内容8位补齐，补齐方式为：少1位补一个0x01,少2位补两个0x02,...
void des(const char *data,const char *key,int mod) {
	DES_cblock ivec = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
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
			switch (mod) {
			case 0:
				DES_ecb_encrypt((const_DES_cblock*)in, (DES_cblock*)out, &ks, DES_ENCRYPT);
				break;
			case 1:
				DES_ncbc_encrypt(in, out, 8, &ks, &ivec, DES_ENCRYPT);
				break;
			case 2:
				DES_cfb_encrypt(in, out, 8, 8, &ks, &ivec, DES_ENCRYPT);
				break;
			case 3:
				DES_ofb_encrypt(in, out, 8, 8, &ks, &ivec);
				break;
			}
			//每次拷贝8个字节出来
			memcpy(encryData + 8 * i, out, 8);
		}
		switch (mod) {
		case 0:
			printf("after DES_ECB encrypt :\n");
			break;
		case 1:
			printf("after DES_CBC encrypt :\n");
			break;
		case 2:
			printf("after DES_CFB encrypt :\n");
			break;
		case 3:
			printf("after DES_OFB encrypt :\n");
			break;
			
		}
		
		for (i = 0; i < data_full_len; i++)
		{
			printf("0x%.2X ", *(encryData + i));
		}
		printf("\n");
	}
}
void aes(const char *data) {
	int i = 0;
	unsigned char key[16];
	AES_KEY ks;
	
	unsigned char *encryData = NULL;
	unsigned char *iv = NULL;
	unsigned char *saved_iv = NULL;
	int nr_of_bits = 0;
	int nr_of_bytes = 0;
	int len = 16;
	//Zeror buffer.  
	encryData = (unsigned char *)malloc(len);
	iv = (unsigned char *)malloc(len);
	saved_iv = (unsigned char *)malloc(len);
	memset(encryData, 0, len);
	
	//随机生成key和初始向量 ，当然key也可以手动指定
	RAND_pseudo_bytes(key, len);
	RAND_pseudo_bytes(saved_iv, len);
	memcpy(iv, saved_iv, len);
	AES_set_encrypt_key(key, 128, &ks);
	AES_cbc_encrypt((unsigned char*)data,encryData,16,&ks,iv,AES_ENCRYPT);
	printf("after AES encrypt\n");
	for (i = 0; i< 16; i++)
	{
		printf("0x%.2X ", *(encryData + i));
	}
	printf("\n");
}
void rc4(const char *data,const char *key) {
	int i = 0;
   
	RC4_KEY ks;
	RC4_set_key(&ks, strlen(key), (const unsigned char*)key);
	int len = strlen(data);
	unsigned char *encryData=NULL; 
	encryData = (unsigned char *)malloc(len);
	memset(encryData, 0, len + 1);//初始为0  
	RC4(&ks, len, (const unsigned char*)data, encryData);//加密明文  
	printf("after RC4 encrypted\n");
	for (i = 0; i< len; i++)
	{
		printf("0x%.2X ", *(encryData + i));
	}
	printf("\n");
}
int main() {
	char *data = "i have not been encrypted yet";
    char *adata = "abcdefghigklmnop";//AES要求为16位
	char *deskey = "238a3420";//密钥为8位
	char *rc4key = "i am rc4 key";
	des(data, deskey, 0);
	des(data, deskey, 1);
	des(data, deskey, 2);
	des(data, deskey, 3);
	aes(adata);
	rc4(data,rc4key);
	system("pause");
	return 0;
}
```
#### 输出结果
![img](https://github.com/slientuill/slientuill.github.com/blob/master/img/%E4%BF%A1%E6%81%AF%E5%AE%89%E5%85%A8%E5%AE%9E%E9%AA%8C.PNG)
### 人机交互
### 网络攻防
[网上有现成的](http://blog.csdn.net/zengxyuyu/article/details/53150521?locationNum=1&fps=1)
注意 自己做的时候 计算的地址是不一样的 需要根据自己的情况 去写buffer+100的地址

