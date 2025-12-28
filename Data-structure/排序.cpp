#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int Status;

typedef struct {
	int key;
}ElemType;

typedef struct //这里元素下标从0开始
{
	ElemType elem[MAXSIZE];
	int length;
}Sqlist;

Status InitList(Sqlist* L)
{
	L->length = 0;
	return 1;
}

Status SetListData(Sqlist* L, ElemType elem[], int length)
{
	L->length = length;
	for (int i = 0; i < length; i++)
	{
		L->elem[i] = elem[i];
	}
	return 1;
}

void PrintList(Sqlist L)
{
	printf("索引\t关键字\n");
	for (int i = 0; i < L.length; i++) {
		printf("%d\t%d\n", i, L.elem[i].key);
	}
}

void BiInsertionSort(Sqlist* L) //折半查找插入
{
	int high, low;
	for (int i = 1; i < L->length; i++)
	{
		high = i - 1; //从已排好序的部分查找需要插入的位置
		low = 0;
		ElemType temp = L->elem[i];
		while (low <= high)
		{
			int mid = (low + high) / 2; //折半
			if (temp.key < L->elem[mid].key) //如果小于中间值，更新上界
				high = mid - 1; //插入低半区
			else
				low = mid + 1; //如果大于等于中间值，则更新下界，插入高半区
		} //循环结果为low=high+1=插入位置
		for (int j = i - 1; j >= high + 1; j--) //
		{
			L->elem[j + 1] = L->elem[j]; //将数据右移

		}
		L->elem[high + 1] = temp; //插入元素
	}
}

void bubblesort(Sqlist* L) //冒泡排序
{
	//从elem[0]开始，比较elem[i]和elem[i+1]的关键字大小，比较到length-1
	//若elem[i].key>elem[i+1].key，则交换位置
	//第一趟比完后最后一个元素是序列中最大的元素

	//再从elem[0]开始，比较到length-2，此时elem[length-2]为次大的元素
	//以此类推
	int flag;
	for (int i = L->length - 1; i > 0; i--)
	{
		flag = 0;
		for (int j = 0; j < i; j++)
		{
			if (L->elem[j].key > L->elem[j + 1].key)
			{
				ElemType temp = L->elem[j];
				L->elem[j] = L->elem[j + 1];
				L->elem[j + 1] = temp;
				flag = 1;
			}
		}
		if (flag != 1) //如果没有发生交换，则说明列表有序，退出循环
			break;
	}
}

int Partition(Sqlist* L, int low, int high) { //Partition分隔，快速排序所用的分隔函数
	ElemType pivot = L->elem[low];
	int pivotkey = pivot.key; //枢轴
	while (low < high) { //结束条件为low=high
		while (low < high && L->elem[high].key >= pivotkey) //从右往左查找，不交换说明都比枢轴大
		{
			--high;
		}
		L->elem[low] = L->elem[high]; //找到比枢轴小的就退出循环，并将该元素放到左半部分
		while (low < high && L->elem[low].key <= pivotkey)
		{
			++low;
		}
		L->elem[high] = L->elem[low]; //同理，找到比枢轴大的就退出，放到右半部分
	}
	L->elem[low] = pivot; //此时中间位置放枢轴
	return low; //返回枢轴的位置
}

void QSort(Sqlist* L, int low, int high) {
	if (low < high) { //当列表长度大于1时才进入排序
		int pivotloc = Partition(L, low, high); //从low到high进行一次划分
		QSort(L, low, pivotloc - 1); //对左子列进行递归排序
		QSort(L, pivotloc + 1, high);//对右子列进行递归排序
	}
}

void QuickSort(Sqlist* L)
{
	QSort(L, 0, L->length - 1);
}

int SelectMinKey(Sqlist L, int Start) //查找最小的下标
{
	int minIndex = Start;
	for (int i = Start + 1; i < L.length; i++)
	{
		if (L.elem[i].key < L.elem[minIndex].key) {
			minIndex = i;
		}
	}
	return minIndex;
}

void SelectSort(Sqlist* L) //简单选择排序
{
	for (int i = 0; i < L->length - 1; i++)
	{
		int j = SelectMinKey(*L, i);
		if (i != j) //交换位置
		{
			ElemType temp = L->elem[j];
			L->elem[j] = L->elem[i];
			L->elem[i] = temp;
		}
	}
}

void HeapAdjust(ElemType elem[], int left, int right) //对堆的调整，大顶堆
{
	ElemType temp = elem[left]; //记录开始时的元素
	for (int j = 2 * left + 1; j < right; j = j * 2 + 1) //下标从0开始，所以左孩子为2*start+1，右孩子为2*start+2
	{
		if (j + 1 < right && elem[j].key < elem[j + 1].key) //判断j+1小于length是为了判断是否右孩子是否存在
			j++; //如果右孩子存在且右孩子更大，则选择右孩子
		if (temp.key >= elem[j].key)
			break; //如果根结点已经比左/右孩子大，说明该处即为插入的位置，退出循环
		elem[left] = elem[j]; //将结点位置往前调整
		left = j; //记录需要插入的位置
	}
	elem[left] = temp; //插入该元素
}

void HeapSort(Sqlist* L) //堆排序,时间复杂度为nlog2n
{
	int length = L->length;
	for (int i = L->length / 2 - 1; i >= 0; i--) //从最后一个非叶子结点进行调整
	{
		HeapAdjust(L->elem, i, length); //通过这个排序，得到一个大顶堆
	} //建立初始堆，保证根节点元素是最大的
	for (int i = length - 1; i > 0; i--)//堆排序过程
	{
		ElemType temp = L->elem[0];
		L->elem[0] = L->elem[i];
		L->elem[i] = temp; //将根节点元素放到数组末尾
		HeapAdjust(L->elem, 0, i); //再次进行堆调整，保证根节点元素是最大的
	} //这里即重复一个过程，不断将堆里的根节点元素放到末尾，再次调整使根节点最大，循环进行，就得到一个升序的数组
} //为什么一定要建立一个初始堆？因为要让第一个根节点元素是里面最大的，不然第一步将根节点元素放到数组末尾会出错

void Merge(ElemType SR[], ElemType TR[], int left, int mid, int right)
{
	int j, k; //归并，即对SR[]数组的两部分归并放入TR[]中，左半部分为left到mid，右半部分为mid+1到right
	for (j = mid + 1, k = left; left <= mid && j <= right; k++)
	{
		if (SR[left].key <= SR[j].key)
			TR[k] = SR[left++];
		else
			TR[k] = SR[j++];
	}
	while (left <= mid) //处理剩下的数，如果左半有剩余，则直接加入到数组末尾（子列归并有序无需排序）
	{
		TR[k++] = SR[left++];
	}
	while (j <= right) //右半有剩余的情况
	{
		TR[k++] = SR[j++];
	}
}

void Msort(ElemType SR[], ElemType TR1[], int start, int end)
{ //因为C语言中数组实际传递的都是指针，所以都是直接修改数组中的数
	//SR[]：原数组
	//TR1[]：目标数组，即排序后的数组
	if (start == end) { //如果数组当中只有一个数，直接复制到目标数组后返回
		TR1[start] = SR[start];
		return;
	}
	ElemType TR2[MAXSIZE]; //这是一个临时数组，用于存储递归过程的中间结果
	int mid = (start + end) / 2;
	Msort(SR, TR2, start, mid); //递归排序左半部分
	Msort(SR, TR2, mid + 1, end);
	Merge(TR2, TR1, start, mid, end);
	//以数组长度7为例，首先对[0,3]进行递归，分成[0,1][2,3],再分成[0,0],[1,1],[2,2],[3,3]
	//左半TR2[]={SR[0],SR[1]}，然后调用Merge(TR2,TR2（上一次传入的）,0,0,1)进行排序
	//右半TR2[]={SR[2],SR[3]}，调用Merge依旧修改上一次传入的TR2
	//再将这两部分的进行合并，每次都修改上一次传入的TR2
	//同理右半对[4,6]进行递归
	//最后TR2[0-3]升序,TR2[4-6]升序
	//最后一次归并传参为TR2[0-6],TR1[],0,3,6
	//Merge函数修改的是传入的第二个数组，即TR1[]
}

void MergeSort(Sqlist* L) //入口函数
{
	Msort(L->elem, L->elem, 0, L->length - 1);
}

int main()
{
	Sqlist L;
	InitList(&L);
	ElemType e[MAXSIZE];
	int n, choice;
	printf("请输入顺序表元素的个数\n");
	scanf("%d", &n);
	printf("请输入%d个整数(空格分隔)\n", n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &e[i].key);
	}
	SetListData(&L, e, n);
	while (1)
	{
		printf("请输入要进行的操作：0为重新设置顺序表，1为还原为上一次的顺序表，2为折半插入排序，3为冒泡排序，4为快速排序，5为简单选择排序，6为归并排序，7为堆排序，8为退出程序\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:
			printf("请输入顺序表元素的个数\n");
			scanf("%d", &n);
			printf("请输入%d个整数(空格分隔)\n", n);
			for (int i = 0; i < n; i++)
			{
				scanf("%d", &e[i].key);
			}
			SetListData(&L, e, n);
			break;
		case 1:
			SetListData(&L, e, n);
			printf("==================\n");
			printf("数据已还原为\n");
			PrintList(L);
			printf("==================\n");
			break;
		case 2:
			BiInsertionSort(&L);
			printf("===================\n");
			printf("折半插入排序的结果为\n");
			PrintList(L);
			printf("===================\n");
			break;
		case 3:
			bubblesort(&L);
			printf("===================\n");
			printf("冒泡排序的结果为\n");
			PrintList(L);
			printf("===================\n");
			break;
		case 4:
			QuickSort(&L);
			printf("===================\n");
			printf("快速排序的结果为\n");
			PrintList(L);
			printf("===================\n");
			break;
		case 5:
			SelectSort(&L);
			printf("===================\n");
			printf("简单选择排序的结果为\n");
			PrintList(L);
			printf("===================\n");
			break;
		case 6:
			MergeSort(&L);
			printf("===================\n");
			printf("归并排序的结果为\n");
			PrintList(L);
			printf("===================\n");
			break;
		case 7:
			HeapSort(&L);
			printf("===================\n");
			printf("堆排序的结果为\n");
			PrintList(L);
			printf("===================\n");
			break;
		case 8:
			return 0;
		default:
			printf("请输入范围内的整数\n");
			break;
		}
	}
}