#include "Distribution.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <time.h>
using namespace std;
int main()
{
	int Need_virtual_num = 0;
	int NUM_Pserver = 0;
	int CPU = 1;
	Virtual_server_info *vserver = InitVserver();
	Physical_server_info Pserver;
	Pserver.CPU_num = 56;
	Pserver.MEM_num = 128*1024;
	int i;
	for(i = 0;i < 15; ++i)
	{
		Need_virtual_num += vserver[i].need;
	}

	Physical_server_storage_info *pssi = NULL;
	//进行分配
	pssi = Distribution(Pserver, vserver,15,NUM_Pserver,Need_virtual_num,CPU);

	//printpserver(pssi,NUM_Pserver);

	return 0;
}

Virtual_server_info * InitVserver()
{
	Virtual_server_info *vserver = (Virtual_server_info *)malloc(16 * sizeof(Virtual_server_info));
	vserver[0].type = 1;
	vserver[0].CPU_num = 1;
	vserver[0].MEM_num = 1024;

	vserver[1].type = 2;
	vserver[1].CPU_num = 1;
	vserver[1].MEM_num = 2048;

	vserver[2].type = 3;
	vserver[2].CPU_num = 1;
	vserver[2].MEM_num = 4096;

	vserver[3].type = 4;
	vserver[3].CPU_num = 2;
	vserver[3].MEM_num = 2048;

	vserver[4].type = 5;
	vserver[4].CPU_num = 2;
	vserver[4].MEM_num = 4096;

	vserver[5].type = 6;
	vserver[5].CPU_num = 2;
	vserver[5].MEM_num = 8192;

	vserver[6].type = 7;
	vserver[6].CPU_num = 4;
	vserver[6].MEM_num = 4096;

	vserver[7].type = 8;
	vserver[7].CPU_num = 4;
	vserver[7].MEM_num = 8192;

	vserver[8].type = 9;
	vserver[8].CPU_num = 4;
	vserver[8].MEM_num = 16384;

	vserver[9].type = 10;
	vserver[9].CPU_num = 8;
	vserver[9].MEM_num = 8192;

	vserver[10].type = 11;
	vserver[10].CPU_num = 8;
	vserver[10].MEM_num = 16384;

	vserver[11].type = 12;
	vserver[11].CPU_num = 8;
	vserver[11].MEM_num = 32768;

	vserver[12].type = 13;
	vserver[12].CPU_num = 16;
	vserver[12].MEM_num = 16384;

	vserver[13].type = 14;
	vserver[13].CPU_num = 16;
	vserver[13].MEM_num = 32768;

	vserver[14].type = 15;
	vserver[14].CPU_num = 16;
	vserver[14].MEM_num = 65536;

	int i = 0;
	for(i = 0;i < 16;++i)
	{
		vserver[i].need = 100;
	}

	/*vserver[9].need = 46;
	vserver[1].need = 35;
	vserver[2].need = 39;
	vserver[4].need = 16;
	vserver[14].need = 4;*/
 	return vserver;
}


Physical_server_storage_info * Distribution(Physical_server_info Pserver,Virtual_server_info *vserver,int type_num_flavor,int &NUM_Pserver,int Need_virtual_num,int CPU)
{
	if(Need_virtual_num)
	{
		Physical_server_storage_info *pssi = (Physical_server_storage_info *)malloc(Need_virtual_num * sizeof(Physical_server_storage_info));
		Physical_server_info Pbak = Pserver;
		int *chromosome = (int *)malloc((Need_virtual_num + 1) * sizeof(int));
		memset(chromosome, 0, sizeof(chromosome));
		memset(pssi, 0, sizeof(Physical_server_storage_info));
		int i,j,flag = 1,k = 1;
		printf("Pserver:\n");
		printf("CPU:%d\tMEM:%d\n", Pserver.CPU_num, Pserver.MEM_num);
		printf("vserver:\n");
		for(i = 0;i < type_num_flavor;++i)
		{
			printf("Type:%d\tCPU:%d\tMEM:%d\tNeed:%d\n", vserver[i].type, vserver[i].CPU_num,vserver[i].MEM_num,vserver[i].need);
		}

		info *index = (info *)malloc((Need_virtual_num + 1) * sizeof(info));
		memset(index, 0, sizeof(index));
		int cpu = 0;
		int mem = 0;
		int block = 0;
		int s1 = 0, s2 = 0, s3 = 0;
		for(i = type_num_flavor - 1;i >= 0;--i)
		{
			if(vserver[i].need > 0)
			{
				for(j = 1;j <= vserver[i].need; ++j)
				{
					index[k].cpu = vserver[i].CPU_num;
					index[k].mem = vserver[i].MEM_num;
					index[k].type = vserver[i].type;
					cpu += index[k].cpu;
					mem += index[k].mem;
					k++;
				}
			}
		}
		s1 = cpu / Pserver.CPU_num + 1;
		s2 = mem / Pserver.MEM_num + 1;
		block = s1 > s2 ? s1 : s2;

		if(s1 > s2)
		{
			s3 = cpu % Pserver.CPU_num;
		}
		else
		{
			s3 = cpu % Pserver.MEM_num;
		}
		if(s3 == 0)
		{
			block -= 1;
		}
		int s = genetic(pssi,index,Need_virtual_num, block, Pserver, CPU ,NUM_Pserver);
		printf("%d\n", s);
		printf("%d\n", Need_virtual_num);
		printf("%d\n", block);
		if(s < Need_virtual_num)
		{
			do
			{
				block += 1;
				s = genetic(pssi,index,Need_virtual_num, block, Pserver,CPU,NUM_Pserver);
				//printf("%d\n", block);
				//printf("%d\n", s);
			}while (s < Need_virtual_num);
		}
		return pssi;

	}
	else
	{
		NUM_Pserver = 0;
		return NULL;
	}

}


void printpserver(Physical_server_storage_info *pssi,int NUM_Pserver)
{
	int i,j;
	printf("Need Pserver NUM:%d\n", NUM_Pserver);
	for(i = 1;i <= NUM_Pserver;++i)
	{
		printf("%d :\n", i);
		for(j = 1;j < 16;++j)
		{
			printf("%d ", pssi[i].Virtual_server_name[j]);
		}
		printf("\n");
	}

}

int genetic(Physical_server_storage_info *pssi,info *index,int Need_virtual_num, int block_num,Physical_server_info Pserver,const int FLAG,int &NUM_Pserver)
{
	const int N = 4;//种群大小
	const int CPU = Pserver.CPU_num;
	const int MEM = Pserver.MEM_num;
	int i, j, k;
	//随机产生染色体
	B **A = (B **)malloc((N+1) * sizeof(B *));
	for(i = 0;i <= N;++i)
	{
		A[i] = (B *)malloc((block_num+1) * sizeof(B));
	}
	memset(A,0,sizeof(A));

	Initchrosome(A,block_num,index,N,CPU,MEM,Need_virtual_num);//随机生成4条染色体
	int ran1,ran2,ran3;
	srand((unsigned)time(NULL));


	/*for(i = 1;i <= N;++i)
	{
		printf("N:%d\n", i);
		for(j = 1;j <= block_num;++j)
		{
			printf("block_num:%d  ", j);
			printf("cpu:%d--mem:%d\n", A[i][j].cpu,A[i][j].mem);
			//printf("cpu_rate:%f--mem_rate:%f\n", A[i][j].cpu_rate,A[i][j].mem_rate);
		}
	}*/
	if(FLAG == 1)
	{
		for(k = 0;k < 50;++k)//100代
		{
			ran1 = rand() % N + 1;
			ran2 = rand() % N + 1;
			ran3 = rand() % N + 1;
			for(i = 1;i <= block_num;++i)
			{

				if(A[ran1][i].cpu_rate > A[ran2][i].cpu_rate && A[ran1][i].mem_rate > 0)//按生存率选着父代优秀的基因，染色体A[ran1]的优秀基因A[ran1][i]插入染色体A[ran2]
				{
					exchange(A[ran1],A[ran2],i,block_num,Need_virtual_num,CPU,MEM,index);//交叉互换
				}
			}
			variation(A[ran3], block_num,Need_virtual_num,CPU,MEM,index,FLAG);//变异
		}
	}
	else
	{
		for(k = 0;k < 50;++k)//100代
		{
			ran1 = rand() % N + 1;
			ran2 = rand() % N + 1;
			ran3 = rand() % N + 1;
			for(i = 1;i <= block_num;++i)
			{
				if(A[ran1][i].cpu_rate > 0 && A[ran1][i].mem_rate > A[ran2][i].mem_rate)//按生存率选着父代优秀的基因，染色体A[ran1]的优秀基因A[ran1][i]插入染色体A[ran2]
				{
					exchange(A[ran1],A[ran2],i,block_num,Need_virtual_num,CPU,MEM,index);//交叉互换
				}
			}
			variation(A[ran3], block_num,Need_virtual_num,CPU,MEM,index,FLAG);//变异
		}
	}



	/*for(i = 1;i <= N;++i)
	{
		printf("N:%d\n", i);
		for(j = 1;j <= block_num;++j)
		{
			printf("block_num:%d  ", j);
			printf("cpu:%d--mem:%d\n", A[i][j].cpu,A[i][j].mem);
			//printf("cpu_rate:%f--mem_rate:%f\n", A[i][j].cpu_rate,A[i][j].mem_rate);
		}
	}*/

	for(i = 1;i <= block_num;++i)
	{
		for(j = 1;j < 16;++j)
		{
			pssi[i].Virtual_server_name[j] = 0;
		}

	}

	for(i = 1;i <= block_num;++i)
	{
		for(j = 1;j <= Need_virtual_num;++j)
		{
			//printf("%d", A[1][i].serie[j]);
			if(A[1][i].serie[j])
			{
				pssi[i].Virtual_server_name[index[j].type]++;
			}
		}
		//printf("\n");
	}


	/*for(i = 1;i <= block_num;++i)
	{
		for(j = 1;j < 16;++j)
		{
			printf("%d ", pssi[i].Virtual_server_name[j]);
		}
		printf("\n");
	}*/

	int s = 0;
	for(i = 1;i <= block_num;++i)
	{
		for(j = 1;j < 16;++j)
		{
			s += pssi[i].Virtual_server_name[j];
		}
	}
	NUM_Pserver = block_num;
	return s;
}
int *random(int N)//生成1--N
{
	int *re = (int *)malloc((N+1) * sizeof(int));
	memset(re, 0, sizeof(re));
	int temp;
	int r;
	int i;
	for(i = 1;i <= N;++i)
	{
		re[i] = i;
	}
	for(i = 1;i <= N;++i)
	{
		r = rand()%N + 1;
		temp = re[i];
		re[i] = re[r];
		re[r] = temp;
	}
	return re;
}
void Initchrosome(B** A,int block_num,info *index,const int N,const int CPU,const int MEM,int Need_virtual_num)
{
	int i,j,k,l;
	int * p = (int *)malloc((block_num+1) * sizeof(int));
	memset(p,0,sizeof(p));

	int *r = NULL;
	for(i = 1;i <= N;++i)//初始化每个盒子的总CPU和MEM
	{
		for(j = 1;j <= block_num;++j)
		{
			A[i][j].cpu = CPU;
			A[i][j].mem = MEM;
		}
	}

	for(i = 1;i <= N;++i)
	{

		for(j = 1;j <= block_num;++j)
		{
			p[j] = rand() % Need_virtual_num + 1;
		}

		sort(p,p+block_num+1);
		p[0] = 0;
		p[block_num] = Need_virtual_num;

		r = random(Need_virtual_num);
		for(j = 1;j <= block_num;++j)
		{
			for(k = p[j];k < p[j+1];++k)//随机生成断点
			{
				if(A[i][j].cpu >= index[r[k]].cpu && A[i][j].mem >= index[r[k]].mem)
				{
					A[i][j].serie[r[k]] = true;
					A[i][j].cpu -= index[r[k]].cpu;
					A[i][j].mem -= index[r[k]].mem;
					A[i][j].cpu_rate =1- 1.0*A[i][j].cpu/CPU;
					A[i][j].mem_rate =1 - 1.0*A[i][j].mem/MEM;
				}
			}
		}
	}


}
B *exchange(B *x,B *y, int f,int block_num,int Need_virtual_num,int CPU,int MEM,info *index)//交叉互换函数
{

	int *bit = (int *)malloc((Need_virtual_num + 1) * sizeof(int));
	memset(bit, 0, sizeof(bit));
	bool *flag = (bool *)malloc((Need_virtual_num+1)*sizeof(bool));
	memset(flag,0,sizeof(flag));

	int i,j,k;
	for(i = 1;i <= block_num; ++i)
	{
		for(j = 1;j <= Need_virtual_num;++j)
		{
			if(y[i].serie[j])
			{
				bit[j] = i;//记录虚拟机所在的物理机
			}
		}
	}

	for(i = 1;i <= Need_virtual_num;++i)
	{
		if(x[f].serie[i])
		{
			if(y[f].serie[i])//去掉有相同的物品的物理机
			{
				y[bit[i]].cpu = CPU;
				y[bit[i]].mem = MEM;
				y[bit[i]].cpu_rate = 0;
				y[bit[i]].mem_rate = 0;
				for(k = 1;k <= Need_virtual_num;++k)
				{
					y[bit[i]].serie[k] = 0;
				}
			}
			else
			{
				if(y[f].cpu >= index[i].cpu && y[f].mem >= index[i].mem)
				{
					y[f].serie[i] = 1;
					y[f].cpu -= index[i].cpu;
					y[f].mem -= index[i].mem;
				}
			}
		}
	}
	if(y[f].cpu <= 0)
	{
		y[f].cpu_rate = 1;
	}
	else
	{
		y[f].cpu_rate =1- 1.0*y[f].cpu/CPU;
	}
	if(y[f].mem <= 0)
	{
		y[f].mem_rate = 1;
	}
	else
	{
		y[f].mem_rate =1 - 1.0*y[f].mem/MEM;
	}
	for(i = 1;i<=block_num;++i)
	{
		for(j = 1;j <= Need_virtual_num;++j)
		{
			if(y[i].serie[j])
			{
				flag[j] = 1;
			}
		}
	}
	for(j = 1;j <= Need_virtual_num;++j)
	{
		if(flag[j] == 0)
		{
			for(i = 1;i <= block_num;++i)
			{
				if(y[i].cpu >= index[j].cpu && y[i].mem >= index[j].mem)
				{
					y[i].cpu -= index[j].cpu;
					y[i].mem -= index[j].mem;
					y[i].cpu_rate = 1- 1.0*y[i].cpu/CPU;
					y[i].mem_rate = 1 - 1.0*y[i].mem/MEM;
					y[i].serie[j] = 1;
					break;
				}
			}
		}
	}
}
void variation(B *x,int block_num,int Need_virtual_num,int CPU,int MEM,info *index, const int FLAG)//变异函数
{
	bool *flag = (bool *)malloc((Need_virtual_num+1)*sizeof(bool));//需要修改
	memset(flag,0,sizeof(flag));
	int i,j,k;
	for(i = 1;i <= block_num;++i)
	{
			x[i].cpu = CPU;
			x[i].mem = MEM;
			x[i].cpu_rate = 0;
			x[i].mem_rate = 0;
			for(k = 1;k <= Need_virtual_num;++k)
			{
				x[i].serie[k] = 0;
			}
	}

	for(i = 1;i<=block_num;++i)//记录flavor所在的盒子
	{
		for(j = 1;j <= Need_virtual_num;++j)
		{
			if(x[i].serie[j])
			{
				flag[j] = 1;
			}
		}
	}

	for(j = 1;j <= Need_virtual_num;++j)//对每个盒子按FFD重新填装
	{
		if(flag[j] == 0)
		{
			for(i = 1;i <= block_num;++i)
			{
				if(x[i].cpu >= index[j].cpu && x[i].mem >= index[j].mem)
				{
					x[i].cpu -= index[j].cpu;
					x[i].mem -= index[j].mem;
					x[i].cpu_rate = 1- 1.0*x[i].cpu/CPU;
					x[i].mem_rate = 1 - 1.0*x[i].mem/MEM;
					x[i].serie[j] = 1;
					flag[j] == 1;
					break;
				}
				/*else
				{
					for(k = Need_virtual_num;k >= 0;--k)
					{
						if(flag[k] == 0)
						{
							if(x[i].cpu >= index[k].cpu && x[k].mem >= index[k].mem)
							{
								x[i].cpu -= index[k].cpu;
								x[i].mem -= index[k].mem;
								x[i].cpu_rate = 1- 1.0*x[i].cpu/CPU;
								x[i].mem_rate = 1 - 1.0*x[i].mem/MEM;
								x[i].serie[j] = 1;
								flag[k] == 1;
								break;
							}
						}
					}
				}*/
			}
		}
	}
}
