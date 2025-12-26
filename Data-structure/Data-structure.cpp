#include <bits/stdc++.h>
#define MAX_VERTEX_NUM 10

typedef struct ArcCell
{
	int adj; //表示权
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{
	char vexs[MAX_VERTEX_NUM]; //存储顶点的数据类型
	AdjMatrix arcs;
	int vexnum, arcnum;
	int kind;
}MGraph;

typedef struct //辅助数组
{
	char adjvex; //顶点U集中顶点相连接的点
	int lowcost; //代价最小的边
}Closedge[MAX_VERTEX_NUM];

int LocateVex(MGraph G, char target)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (target == G.vexs[i])
			return i;
	}
	return -1;
}

void CreateGraph(MGraph* G)
{
	printf("输入顶点个数默认为5，请输入弧的个数\n");
	G->vexnum = 5; //五个城市，顶点数默认为5
	scanf("%d", &G->arcnum);
	getchar();
	printf("输入各城市的数据信息，按空格分隔\n");
	for (int i = 0; i < G->vexnum; i++)
	{
		scanf("%c", &G->vexs[i]);
		getchar();
	}
	for (int i = 0; i < G->vexnum; i++)
		for (int j = 0; j < G->vexnum; j++)
			G->arcs[i][j].adj = INT_MAX; //给图的边的权进行初始化，默认权为最大整数
	printf("每行输入两个城市的名称，和他们之间的权，以空格分隔\n");
	for (int i = 0; i < G->arcnum; i++)
	{
		char v1, v2;
		int adj;
		scanf("%c %c %d", &v1, &v2, &adj);
		getchar();
		int n = LocateVex(*G, v1);
		int m = LocateVex(*G, v2);
		G->arcs[n][m].adj = adj;
		G->arcs[m][n].adj = adj; //城市之间的距离无向
	}
	G->kind = 3; //构造的是网
}
int minimum(Closedge closedge,int n)
{
	int min = INT_MAX;
	int k = -1;
	for (int i = 0; i < n; i++)
	{
		if (closedge[i].lowcost > 0 && closedge[i].lowcost < min)
		{
			min = closedge[i].lowcost; //找到最小代价
			k = i; //记录最小代价对应的顶点下标
		}
	}
	return k;
}
void MiniSpanTree_PRIM(MGraph G, char u) //用普里姆算法从顶点u出发构建网G的最小生成树
{
	int k = LocateVex(G, u);
	int min = 0;
	Closedge closedge;
	for (int j = 0; j < G.vexnum; j++)
	{
		if (j != k)
			closedge[j] = { u,G.arcs[k][j].adj };
	}
	closedge[k].lowcost = 0; //初始下U集中仅有u一个顶点，顶点到自身的最小代价为0
	for (int i = 1; i < G.vexnum; i++) //继续向生成树上添加顶点
	{
		k = minimum(closedge, G.vexnum);
		min += closedge[k].lowcost;
		printf("%c %c\n",closedge[k].adjvex, G.vexs[k]);
		closedge[k].lowcost = 0;
		for (int j = 0; j < G.vexnum; j++)
		{
			if (G.arcs[k][j].adj < closedge[j].lowcost) //如果新并入的顶点到别的点的长度更短
				closedge[j] = { G.vexs[k],G.arcs[k][j].adj }; //更新最小代价
		}
	}
	printf("最小代价为%d\n", min);
}

int main()
{
	MGraph G;
	CreateGraph(&G);
	printf("已创建图！\n");
	printf("请输入要从哪个顶点构造最小生成树\n");
	char u;
	scanf("%c", &u);
	printf("最小生成树的路径为\n");
	MiniSpanTree_PRIM(G, u);
	return 0;
}