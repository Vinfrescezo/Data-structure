//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#define NULLKEY -1
//typedef int Status;
//typedef int KeyType;
//int hashsize[] = { 7, 17, 31, 61, 127, 251, 509, 1021, 2039, 4093 }; //提前设置好对应的哈希函数大小
//int size = 0; //把哈希表的大小设置为全局变量了，方便调用
//
//struct ElemType //数据元素类型
//{
//	int key; //设关键字为整型
//};
//
//typedef struct
//{
//	ElemType* elem;
//	int count;
//	int sizeindex;
//}HashTable;
//
//Status InitHashTable(HashTable* H, int n) //初始化哈希表
//{
//	int index = 0;
//	while (hashsize[index] * 0.7 < n)
//	{
//		index++;
//	}
//	H->sizeindex = index;
//	H->count = 0;
//	size = hashsize[H->sizeindex];
//	H->elem = (ElemType*)malloc(size * sizeof(ElemType));
//	if (H->elem == NULL)
//	{
//		printf("内存分配失败，程序退出！\n");
//		exit(0);
//	}
//	for (int i = 0; i < size; i++)
//	{
//		H->elem[i].key = NULLKEY; //所有哈希地址上的元素都为空
//	}
//	return 1;
//}
//
//int Hash(KeyType K) //用除留余数法构造的哈希函数
//{
//	return K % size;
//}
//
//void collision(int* p)
//{
//	*p = (*p + 1) % size; //处理冲突的方式为线性探测再散列，其中增量为1
//}
//
//Status SearchHash(HashTable H, KeyType K, int& p, int& c) //在开放定址哈希表H中查找关键字为K的数据
//{
//	p = Hash(K); //p为待查数据在表中的位置，求其哈希地址
//	while (H.elem[p].key != NULLKEY && K != H.elem[p].key) //如果当前哈希地址不为空，则表明发生了冲突，继续查找
//	{
//		collision(&p); //处理冲突
//		c++;
//	}
//	if (K == H.elem[p].key)
//		return 1;
//	else
//		return 0;
//}
//
//Status RecreateHashTable(HashTable* H) //重建哈希表
//{
//	ElemType* oldElem = H->elem; //保留旧的元素
//	int oldSize = size;
//	H->sizeindex++;
//	size = hashsize[H->sizeindex];
//	H->elem = (ElemType*)malloc(size * sizeof(ElemType));
//	if (H->elem == NULL)
//	{
//		printf("内存分配失败，程序退出！\n");
//		exit(0);
//	}
//	for (int i = 0; i < size; i++) //初始化哈希地址上的元素为空
//	{
//		H->elem[i].key = NULLKEY;
//	}
//	for (int i = 0; i < oldSize; i++) //将原来的元素重新分配到新的哈希表中
//	{
//		if (oldElem[i].key != NULLKEY)
//		{
//			int p = Hash(oldElem[i].key); //因为表的容量改变了，所以整体对应的哈希地址也变了
//			while (H->elem[p].key != NULLKEY)
//			{
//				collision(&p);
//			}
//			H->elem[p] = oldElem[i];
//		}
//	}
//	return 1;
//}
//
//Status InsertHash(HashTable* H, ElemType e)
//{
//	int c = 0; //c为冲突次数，初始为0
//	int p; //p为待插入元素在表中的位置
//	if (SearchHash(*H, e.key, p, c) == 1)
//	{
//		printf("该元素在表中已存在，无法插入\n");
//		return 0;
//	}
//	else
//	{
//		H->elem[p] = e;
//		H->count++;
//		double loadFactor = (double)H->count / size;
//		if (loadFactor > 0.7) //要求装载因子不超过0.7
//		{
//			printf("装载因子超过0.7，重建哈希表\n");
//			RecreateHashTable(H);
//		}
//	}
//	return 1;
//}
//
//void DisplayKey(HashTable H) //输出关键词信息
//{
//	printf("索引\t关键字\n");
//	for (int i = 0; i < size; i++) {
//		if (H.elem[i].key != NULLKEY) {
//			printf("%d\t%d\n", i, H.elem[i].key);
//		}
//	}
//}
//
//void DisplayHashTable(HashTable H) { //输出哈希表信息
//	printf("========== 哈希表信息 ==========\n");
//	printf("当前容量：%d\n", size);
//	printf("元素个数：%d\n", H.count);
//	printf("装载因子：%.2f\n", (double)H.count / size);
//	printf("哈希表内容：\n");
//	DisplayKey(H);
//	printf("================================\n");
//}
//
//int main()
//{
//	HashTable H;
//	printf("请输入关键字序列的个数\n");
//	int n;
//	scanf("%d", &n);
//	InitHashTable(&H, n);
//	printf("请输入%d个无序关键字（整数）：\n", n);
//	for (int i = 0; i < n; i++)
//	{
//		KeyType key;
//		scanf("%d", &key);
//		ElemType e;
//		e.key = key;
//		InsertHash(&H, e);
//	}
//	DisplayHashTable(H);
//	while (1)
//	{
//		int choice;
//		KeyType key;
//		printf("请选择操作：\n");
//		printf("1. 查找关键字\n");
//		printf("2. 显示哈希表\n");
//		printf("3. 退出程序\n");
//		scanf("%d", &choice);
//		int p, c = 0;
//		switch (choice)
//		{
//		case 1:
//			printf("请输入关键字\n");
//			scanf("%d", &key);
//			c = 0;
//			if (SearchHash(H, key, p, c))
//			{
//				printf("查找成功，哈希地址为%d，查找次数为%d\n", p, c + 1); //查找次数为冲突次数+1
//			}
//			else
//			{
//				printf("查找失败，插入哈希表，并显示关键词序列\n");
//				ElemType e;
//				e.key = key;
//				InsertHash(&H, e);
//				DisplayKey(H);
//			}
//			break;
//		case 2:
//			DisplayHashTable(H);
//			break;
//		case 3:
//			return 0;
//		default:
//			printf("请重新输入正确的数\n");
//			break;
//		}
//	}
//}