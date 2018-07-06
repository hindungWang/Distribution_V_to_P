#ifndef __ROUTE_H__
#define __ROUTE_H__

#include <stdlib.h>

struct Physical_server_info//物理服务器信息
{
	int CPU_num;//CPU总数
	int MEM_num;//内存总数
	int  HD;//硬盘总数
};
struct Virtual_server_info//虚拟机规格信息
{
	int type;//种类
	int CPU_num;//CPU数量
	int MEM_num;//内存数量
	int need = 0;//预测结果
};

struct Physical_server_storage_info
{
	int Virtual_server_name[16] = {0};//i是种类，对应的值是个数
};

struct info
{
	int cpu;
	int mem;
	int type;
};

struct B
{
	double cpu_rate;
	double mem_rate;
	int cpu;
	int mem;
	bool serie[1000];
};
Virtual_server_info * InitVserver();

void printpserver(Physical_server_storage_info *pssi,int NUM_Pserver);

Physical_server_storage_info * Distribution(Physical_server_info Pserver,Virtual_server_info *vserver,int type_num_flavor,int &NUM_Pserver,int Need_virtual_num,int CPU);


int genetic(Physical_server_storage_info *pssi,info *index,int Need_virtual_num, int block_num,Physical_server_info Pserver,const int FLAG,int &NUM_Pserver);


int *random(int N);

void Initchrosome(B** A,int block_num,info *index,const int N,const int CPU,const int MEM,int Need_virtual_num);

B *exchange(B *x,B *y, int f,int block_num,int Need_virtual_num,int CPU,int MEM,info *index);

void variation(B *x,int block_num,int Need_virtual_num,int CPU,int MEM,info *index,const int FLAG);


#endif
