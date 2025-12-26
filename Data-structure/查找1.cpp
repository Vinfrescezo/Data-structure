//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//typedef struct BiTNode //二叉排序树
//{
//	int data;
//	BiTNode* lchild, * rchild;
//}BiTNode, * BiTree;
//
//int SearchBST(BiTree T, int key, BiTree f, BiTree* p) //在根指针T所指二叉排序树中递归地查找其关键字等于key的数据
//{													  //查找成功则返回p所指数据元素的结点，并返回1，否则表明查找不成功
//	if (T == NULL) //返回指针p所指查找路径上访问的最后一个结点，并返回函数值为0
//	{
//		*p = f; //指针f指向当前访问的结点的双亲，其初始调用值为NULL
//		return 0;
//	}
//	else if (key == T->data)
//	{
//		*p = T;
//		return 1;
//	}
//	else if (key > T->data) //如果查找的树大于目前的数，则在左子树中查找
//		return SearchBST(T->lchild, key, T, p);
//	else //否则在右子树中查找
//		return SearchBST(T->rchild, key, T, p);
//}
//int InsertBST(BiTree& T, int e)
//{
//	BiTree p;
//	if (SearchBST(T, e, NULL, &p) == 0)
//	{
//		BiTree s = (BiTree)malloc(sizeof(BiTNode));
//		s->data = e;
//		s->lchild = s->rchild = NULL;
//		if (p == NULL)
//			T = s;
//		else if (e > p->data) //如果插入的数据大于结点
//			p->lchild = s; //插入s为p的左孩子
//		else
//			p->rchild = s; //反之插入s为p的右孩子
//		return 1;
//	}
//	return 0;
//}
//
//void Inorder(BiTree T)
//{
//	if (T == NULL) //结点为空时返回
//	{
//		return;
//	}
//	Inorder(T->lchild); //中序访问左子树
//	printf("%d ", T->data); //输出根结点
//	Inorder(T->rchild); //中序访问右子树
//}
//
//int main()
//{
//	BiTree T = NULL;
//	int n, e;
//	printf("请输入关键字的个数\n");
//	scanf("%d", &n);
//	printf("请输入%d个关键字，按空格分隔\n", n);
//	for (int i = 0; i < n; i++)
//	{
//		scanf("%d", &e);
//		getchar();
//		InsertBST(T, e);
//	}
//	printf("构造的二叉排序树的中序遍历结果为\n");
//	Inorder(T);
//	printf("\n");
//	while (1)
//	{
//		printf("请输入要查找的数据\n");
//		if (scanf("%d", &e) != 1)
//			break;
//		BiTree p;
//		if (SearchBST(T, e, NULL, &p) == 1)
//		{
//			printf("已查找到该数据\n");
//		}
//		else
//		{
//			printf("未查找到该数据，将该数据插入到排序树中\n");
//			InsertBST(T, e);
//			printf("插入后中序遍历的结果为\n");
//			Inorder(T);
//			printf("\n");
//		}
//	}
//}