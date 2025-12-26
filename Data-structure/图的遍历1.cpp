//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#define MAX_VERTEX_NUM 100 //Vertex顶点数，定义最大定点数为100
//int visited[MAX_VERTEX_NUM] = { 0 };
//
//typedef struct ArcNode
//{
//	int adjvex; //该弧所指向的顶点位置
//	ArcNode* nextarc; //指向下一条弧的指针，arc即弧
//}ArcNode;
//
//typedef struct VNode
//{
//	char data; //顶点存储的信息
//	ArcNode* firstarc; //指向第一条依附该顶点的图
//}VNode, AdjList[MAX_VERTEX_NUM]; //AdjList即Adjacency List表示邻接表
//
//typedef struct
//{
//	AdjList vertices; //图要存顶点
//	int vexnum, arcnum; //顶点数和弧的个数
//	int kind; //图的种类无向或有向
//}ALGraph; //ALGraph即Adjacency List Graph，表示是邻接表表示的图
//
//int LocateVex(ALGraph G, char target)
//{
//	for (int i = 0; i < G.vexnum; i++)
//	{
//		if (target == G.vertices[i].data)
//			return i;
//	}
//	printf("未查找到数值为%c的顶点，程序退出", target);
//	exit(0);
//}
//
//void CreateGraph(ALGraph* G)
//{
//	printf("输入顶点个数，弧的个数，以空格分割\n");
//	scanf("%d%d", &G->vexnum, &G->arcnum);
//	getchar();
//	printf("输入各顶点的数据信息，按空格分隔\n");
//	for (int i = 0; i < G->vexnum; i++)
//	{
//		scanf("%c", &G->vertices[i].data);
//		getchar();
//		G->vertices[i].firstarc = NULL; //初始化时，所有顶点的第一条弧都设为空
//	}
//	G->kind = 0; //默认为无向图，kind=0，=1表示有向图
//	printf("每行输入一条弧连接的两个顶点的data，以空格分隔\n");
//	ArcNode* newArc;
//	for (int i = 0; i < G->arcnum; i++)
//	{
//		char v1, v2;
//		scanf("%c %c", &v1, &v2);
//		getchar();
//		int index1 = LocateVex(*G, v1); //第一步找到v1和v2对应顶点的位置
//		int index2 = LocateVex(*G, v2);
//		newArc = (ArcNode*)malloc(sizeof(ArcNode)); //第二步，采用头插法，先给新的弧分配内存
//		if (newArc == NULL)
//		{
//			printf("内存分配失败\n");
//			exit(0);
//		}
//		newArc->adjvex = index2; //该弧指向的结点位置为第二个顶点
//		newArc->nextarc = G->vertices[index1].firstarc; //将第一个顶点的第一条弧设为新弧的下一条弧
//		G->vertices[index1].firstarc = newArc; //新的弧插入到第一个顶点的第一条弧中
//		//即采用头插法，每一次新加入的弧都紧挨着顶点放入
//		newArc = (ArcNode*)malloc(sizeof(ArcNode)); //这里因为是无向图，还要将第二个顶点也插入指向第一个顶点的弧
//		if (newArc == NULL)
//		{
//			printf("内存分配失败\n");
//			exit(0);
//		}
//		newArc->adjvex = index1;
//		newArc->nextarc = G->vertices[index2].firstarc;
//		G->vertices[index2].firstarc = newArc;
//	}
//}
//
//void DFS(ALGraph* G, int v) //深度优先搜索
//{
//	if (v >= G->vexnum)
//	{
//		printf("不存在该顶点，搜索结束\n");
//		return;
//	}
//	printf("%c ", G->vertices[v].data);
//	visited[v] = 1;
//	ArcNode* p = G->vertices[v].firstarc;
//	while (p != NULL)
//	{
//		int w = p->adjvex;
//		if (!visited[w])
//		{
//			DFS(G, w);
//		}
//		p = p->nextarc;
//	}
//}
//
//void BFS(ALGraph* G, int v) //广度优先搜索
//{
//	if (v >= G->vexnum)
//	{
//		printf("不存在该顶点，搜索结束\n");
//		return;
//	}
//	int Quene[MAX_VERTEX_NUM]; //用数组和双指针模拟队列
//	int front = 0, rear = 0; //rear++表示出队，front++表示入队
//	printf("%c ", G->vertices[v].data);
//	visited[v] = 1;
//	Quene[rear++] = v;
//	while (rear > front)
//	{
//		int w = Quene[front];
//		front++;
//		ArcNode* p = G->vertices[w].firstarc;
//		while (p != NULL)
//		{
//			int u = p->adjvex;
//			if (!visited[u])
//			{
//				visited[u] = 1;
//				printf("%c ", G->vertices[u].data);
//				Quene[rear++] = u;
//			}
//			p = p->nextarc;
//		}
//	}
//}
//
//int main()
//{
//	ALGraph G;
//	CreateGraph(&G);
//	printf("已创建图！\n");
//	printf("请输入要进行深度搜索的初始顶点下标\n");
//	int v;
//	scanf("%d", &v);
//	printf("进行深度搜索的路径为\n");
//	DFS(&G, v);
//	printf("\n");
//	memset(visited, 0, sizeof(visited));
//	printf("请输入要进行广度搜索的初始顶点下标\n");
//	scanf("%d", &v);
//	printf("进行广度搜索的路径为\n");
//	BFS(&G, v);
//	return 0;
//}
