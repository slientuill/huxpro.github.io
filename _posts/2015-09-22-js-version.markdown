---
layout:     post
title:      "MicroPayment，Fast hashchain verification，V2G"
subtitle:   "论文还在缓慢更新中....."
date:       2015-09-22
author:     "slientuill"
header-img: "img/post-bg-js-version.jpg"
tags:
    - 区块链
    - hashchain
    - 快速哈希验证
---


<script language="javascript">
<!--
loopy();
function loopy() {
var sWord = prompt("输入正确密码才能登陆!","");
var password = "123456";
var isCancle = false;
while(sWord!=password){
 if(sWord==null){
  isCancle = true;
  break;
 }else{
  sWord = prompt("输入正确密码才能登陆!","");
 }
}
if(!isCancle){
 alert("AH...密码正确谢谢你的光临！");
}else{
 location.replace("about:blank");
 window.close();
}
}
//-->
</script>

Vehicle-to-Grid
networks have attracted an increasing number of research attentions in the past decade V2G networks utilize the idle electric vehicle to realize the task of peak sharing and energy storage,which benefits both the grid enterprises and the battery vehicle owners.
//Many had been done in solveing problems in V2G grid.
//V2G网络介绍
为了保护电动汽车拥有者的个人信息不被泄露，许多有关的研究建议使用电子货币：比特币或以太币来与电网进行电力交易，这些货币的非中心化的账户机制能够使得用户的个人信息能够很好的保护起来，然而，使用这些货币发起的交易无论交易金额多少，每次都需要支付一定量的额外费用，而电动汽车与电网之间通常都是频繁而金额微小的交易，如果简单的采用电子货币的支付方式，将会消耗大量的计算资源，浪费大量的结算货币
So far little has been done in micro payment
//
#### 基于哈希链验证的微支付
哈希链，最初在这个<lamport>论文中被提到，通过选取一个种子x0，并对这个种子不断进行哈希运算，所得到的链便是哈希链，链中的每一个值都由其前一个值进行哈希运算得到，也即 xi=hash(xi-1),由于哈希函数具有单向性，被给予xi-1的一方无法计算得到xi，保证了xi及以后的哈希值的安全性。
我们的微支付方案便基于该种原理，通过向收款方发送种子x0，并根据收款方提供的服务不断向其发送x1,x2,x3….等后续哈希值直到服务终止的方式，对收款方提供的服务数量进行计数，随后收款方可以根据他最后获得的xi的值，使用哈希函数计算i次得到x0，也即xi与x0之间的哈西距离i 获得得到既定报酬中的i份 
#### 具体方案
交易开始前，付款方和收款方协商决定哈希链的长度n，以及一次交易的额度m
交易开始时，由付款方选取种子x0，并通过哈希函数，生成哈希链x1,x2,x3….xn，并将x0发送给收款方，收款方确认以后便可以开始提供服务
收款方每提供一次服务，付款方便依照顺序向收款方发送一个哈希值x1,x2…xn直到服务结束
服务结束时，收款方使用最后得到的哈希值xi，对其循环进行哈希运算，直到第i次，计算得到x0，也即xi与x0之间的哈希距离为i，则收款方便得到(i/n)*m数量的报酬。
#### 快速哈希方案
 当哈希链的长度n越来越大的时候，循环使用哈希函数进行计算所需要的时间便会变得越来越无法忽视，为了节约运算资源，提升运算速度，我们提出了快速哈希验证的方案
原有的哈希验证方案，对于获得的xi需要一直不间断的进行哈希运算，加入每次哈希运算所需要的时间为t，则完成一次交易所进行的哈希计算的时间至少为i*t;在原有方案的基础上，我们加入了数字签名验证的方法，大大降低了哈希验证所需要的时间。
我们在原有的哈希链上，每隔固定的距离设置一个数字签名，使用收款方的公钥A，付款方的公钥B，当前位置与x0的距离i，当前位置的哈希值xi，使用付款方的私钥pkb建立一个签名sign,也即sign=(A,B,i,xi)pkb,并且每当发送到该位置时，改为发送xi和sign
在验证时，加入间隔为100的时候，不再需要验证i个哈希值，而是只需要验证小于100个哈希值和一个签名，从而降低了哈西验证的时间，假设一次签名档的验证时间为ts此时我们的验证时间为(i%100)*t+ts
 
图1，理论效率对比图

#### 智能合约的原理
* **建立合约**，由付款方将合约部署在区块链上，信息调用者将的地址（即付款方）被确认为付款方的地址。
* **初始化**，该函数仅能够被付款方调用，由其来设置该合约的参数：
	交付金额的大小，哈希链的根值，哈希链的长度，收款方的地址，交易最长等待时间
* **提款**，该函数仅能够被在初始化函数中确定的收款方地址调用，且如果调用时间超过交易等待时间，则该函数无法被任何人调用
收款方需要提供三个参数他最后一次获得的哈希值，他最后一次获得的签名值，他最后一次获得的i值；
函数根据i的值进行少于100次的哈希运算，并将得到的值与付款方的公钥，收款方的公钥，i一起进行哈希运算
将得到的值与签名复原出的值进行比较，一旦比对成功
则合约中i/哈希链长度*交易金额的货币将会被发送到收款方，其余的金额将会被退回给付款方
* **交易延迟解决方案**，该函数在当前时间超过交易等待时间之后可以被任何人调用，该函数将合约中的所有货币退还给付款方






#### 著作权声明



