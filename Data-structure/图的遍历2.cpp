#include <bits/stdc++.h>
#define MAX_VERTEX_NUM 100
int visited[MAX_VERTEX_NUM] = { 0 };
typedef struct ArcCell
{
	int adj; //表示顶点间的邻接关系，1表示有边，0表示无边
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{
	char vexs[MAX_VERTEX_NUM]; //存储顶点的数据类型
	AdjMatrix arcs;
	int vexnum, arcnum;
	int kind;
}MGraph;

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
	printf("输入顶点个数，弧的个数，以空格分割\n");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	getchar();
	printf("输入各顶点的数据信息，按空格分隔\n");
	for (int i = 0; i < G->vexnum; i++)
	{
		scanf("%c", &G->vexs[i]);
		getchar();
	}
	for (int i = 0; i < G->vexnum; i++)
		for (int j = 0; j < G->vexnum; j++)
			G->arcs[i][j].adj = 0; //给图的弧进行初始化，默认每个顶点间无弧
	printf("每行输入一条弧连接的两个顶点的data，以空格分隔\n");
	for (int i = 0; i < G->arcnum; i++)
	{
		char v1, v2;
		scanf("%c %c", &v1, &v2);
		getchar();
		int n = LocateVex(*G, v1);
		int m = LocateVex(*G, v2);
		G->arcs[n][m].adj = 1;
		G->arcs[m][n].adj = 1; //无向图为对称矩阵，则v2到v1也要设为1表示有弧
	}
	G->kind = 0; //构造的是无向图
}

void DFS(MGraph* G, int v) //深度优先搜索
{
	printf("%c ", G->vexs[v]);
	visited[v] = 1;
	for (int i = 0; i < G->vexnum; i++)
	{
		if (visited[i] == 0 && G->arcs[v][i].adj == 1) //如果该顶点没有访问过且当前访问的顶点与该顶点有弧
		{
			DFS(G, i); //递归进行深度搜索
		}
	}
}

void BFS(MGraph* G, int v) //广度优先搜索
{
	int Quene[MAX_VERTEX_NUM]; //用数组和双指针模拟队列
	int front = 0, rear = 0; //rear++表示入队，front++表示出队
	printf("%c ", G->vexs[v]);
	visited[v] = 1;
	Quene[rear++] = v;
	while (rear > front) //如果队列不为空
	{
		int w = Quene[front]; //队头元素出队
		front++;
		for (int i = 0; i < G->vexnum; i++)
		{
			if (G->arcs[w][i].adj == 1 && visited[i] == 0) //如果队头元素和遍历的顶点之间有弧，且该顶点未访问过
			{
				visited[i] = 1;
				printf("%c ", G->vexs[i]);
				Quene[rear++] = i; //访问该顶点，且该顶点入队
			}
		}
	}
}

int main()
{
	MGraph G;
	CreateGraph(&G);
	printf("已创建图！\n");
	printf("请输入要进行深度搜索的初始顶点下标\n");
	int v;
	scanf("%d", &v);
	printf("进行深度搜索的路径为\n");
	DFS(&G, v);
	printf("\n");
	memset(visited, 0, sizeof(visited));
	printf("请输入要进行广度搜索的初始顶点下标\n");
	scanf("%d", &v);
	printf("进行广度搜索的路径为\n");
	BFS(&G, v);
	return 0;
}
