# Distribution_V_to_P
**2018年华为软件挑战衍生出来的二维装箱问题**

对给定预测时间段内不同规格的虚拟机数量进行预测,最后根据预测结果把虚拟机部署到物理服务器上,使得服务器的资源利用率最大化。
我们只关注第二部分的装箱问题。
假设物理服务器的规格如下：
```
物理服务器CPU核数 内存大小(GB) 硬盘大小(GB)
56 128 1200
(备注:物理服务器资源信息包含硬盘大小,实际调度可不考虑硬盘容量。
CPU核数为不超过两位的整数,内存大小为不超过3位的整数,
硬盘大小为不超过4位的整数。1GB=1024MB)
```
虚拟机规格：
```
flavor1 1 1024
flavor2 1 2048
flavor3 1 4096
flavor4 2 2048
flavor5 2 4096
flavor6 2 8192
flavor7 4 4096
flavor8 4 8192
flavor9 4 16384
flavor10 8 8192
flavor11 8 16384
flavor12 8 32768
flavor13 16 16384
flavor14 16 32768
flavor15 16 65536
备注:flavor名称 CPU核数 内存大小(MB)

```

假设预测结果为：

```
232(总的虚拟机数量，以下为各种虚拟机的需求量)
flavor1 35
flavor2 39
flavor3 0
flavor4 15
flavor5 12
flavor6 3
flavor7 0
flavor8 73
flavor9 30
flavor10 1
flavor11 0
flavor12 19
flavor13 0
flavor14 5
flavor15 0

```


如何把这些虚拟机分配到物理虚拟机上以获得最大的效益，即更高的CPU|MEM利用率就是本程序所做的事情。
本程序采用遗传算法来获取最优解。由于时间有限，本人所写的算法有待改进，在处理大量数据时可能会崩溃掉，有待改进。
```
一个可行的方案是

18(总的物理服务器个数)
物理服务器编号 所放置的虚拟机种类和个数 。。。
1 flavor12 1 flavor14 3 
2 flavor12 2 flavor14 2 
3 flavor12 4 
4 flavor12 4 
5 flavor12 4 
6 flavor12 4 
7 flavor8 1  flavor9 7  flavor10 1 
8 flavor9 8  
9 flavor9 8  
10 flavor8 2  flavor9 7  
11 flavor8 14 
12 flavor8 14 
13 flavor8 14 
14 flavor8 14 
15 flavor8 14 
16 flavor4 13 flavor5 12 flavor6 3  
17 flavor1 13 flavor2 39 flavor4 2  
18 flavor1 22 

```

参考文献：[虚拟机动态资源分配及放置算法的研究](http://www.docin.com/p-1048965913.html)
