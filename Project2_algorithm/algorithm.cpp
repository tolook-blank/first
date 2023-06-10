#include"MyTools.hpp"
#include<assert.h>
#include<iostream>

void BuildMaxHeap(int A[], int len);
void HeapAdjust(int A[], int k, int len);
void HeapSort(int A[], int len);
void Insert_Heap(int A[], int len, int target);

//建立大根堆（根节点下标设为 0）
void BuildMaxHeap(int A[], int len)
{
	for (int i = (len - 1)/ 2; i >= 0; --i)//从后向前调整所有非终端节点，从i=[len/2 , 1]
		HeapAdjust(A, i, len);
}

//将以k为根的子树 调整为大根堆
void HeapAdjust(int A[], int k, int len) //k为堆的根节点，len为堆的大小
{
	int temp = A[k];// temp暂存子树的根节点 
	for (int i = 2*k; i <= len - 1; i *= 2) //i指向 以k为根节点的 左子树节点( 2*k )
	{
		if (i < len && A[i] < A[i + 1]) ++i;//取key更大的子树节点下标
		if (temp >= A[i]) break;//满足大根堆（根 >= 左，右）
		else //若根节点值 小于 子树节点值
		{
			A[k] = A[i];//把值更大的子树节点 调整到 根节点位置上
			k = i; //原根节点位置（小元素）不断下坠
		}
	}
	A[k] = temp; //temp保存的原根节点值 放入最终位置
}

//基于大根堆的 堆排序 得到 递增序列
void HeapSort(int A[], int len)
{
	BuildMaxHeap(A, len); //初始建堆，A[0]为堆顶元素
	for (int i = len - 1; i > 0; --i) //i指向堆底元素,n-1趟的交换和建堆过程
	{
		Swap(A[i], A[0]); //把堆顶和堆底元素进行交换,存放到A[i]，此时 i指向的元素已经有序
		HeapAdjust(A, 0, i - 1);//把剩余的i-1个 待排序元素 调整成堆;直到只剩1个元素
	}
}

void Insert_Heap(int A[], int len, int target)
{
	int temp = A[++len] = target;//新节点插入堆底,用temp保存
	int i;
	for (i = len-1; i > 0; --i)// 1. 当新节点下标i=0（为根节点），调整结束
	{
		if (temp > A[i / 2])//新节点值大于父节点值，则上浮
		{
			A[i] = A[i / 2];//父节点值下沉
			i = i / 2;//更新 新节点的下标，便于下次上浮	
		}
		else break; // 2. 若新节点值小于父节点值，大根堆调整结束
	}
	A[i] = temp; //新节点放入最终位置
}





//1.冒泡排序（最简单的交换排序）  最好、最坏、平均时间复杂度均为O（n^2)
//在函数外定义数组，通过形参传入函数，在函数内修改数组
void Bubblesort1(int array[], int len)
{
	for (int i = 1; i < len; ++i)
	{//控制比较轮次，一共 n-1 趟
		for (int j = 0; j < len - i; ++j)
		{//控制两个挨着的元素进行比较
			if (array[j] > array[j + 1])
			{
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}


//1.n 优化冒泡排序函数，升序排序
//函数需要返回数组，声明一个返回指针的函数
int* BubbleSort2(int arr[], int len)//形参int* arr，int arr[]都可以
{
	if (arr == NULL || len < 2)
	{
		return arr;
	}
	//记录最后一次交换的位置
	int lastExchangeIndex = 0;
	//无序数列的边界,循环停止边界
	int sortBorder = len - 1;
	for (int i = 1; i < len; ++i)
	{
		bool isSorted = true;//有序标记，每轮初始假设有序
		for (int j = 0; j < sortBorder; ++j)
		{

			if (arr[j] > arr[j + 1])
			{
				isSorted = false;//有元素交换，还不是有序数组
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				lastExchangeIndex = j;
			}
		}
		sortBorder = lastExchangeIndex;
		if (isSorted)
		{
			break;
		}
	}
	return arr;
}


//4.希尔排序是插入排序优化
//void Shell_Sort(int* a, int n)
//{
//	int gap = n;
//	while (gap > 1)
//	{
//		gap = gap / 3 + 1;
//		for (int i = 0; i < n - gap; i++)
//		{
//			int end = i;
//			int temp = a[end + gap];
//			while (end >= 0)
//			{
//				if (temp > a[end])
//				{
//					a[end + gap] = a[end];
//					end -= gap;
//				}
//				else
//				{
//					break;
//				}
//			}
//			a[end + gap] = temp;
//		}
//	}
//}


//二分法查找元素插入的位置
int* search_insert(int* arr, int len, int key)
{
	int left(0);
	int right = len - 1;
	int middle(0);
	if (key >= arr[right])//若key大于等于数组最大值，在最右边插入
	{
		middle = right + 1;
	}
	else if (key <= arr[left])//小于等于最小值，在最左边插入
	{
		middle = 0;
	}
	else// 若key在左闭右闭的区间里，[left, right]
	{
		while (left <= right)
		{ // 当left==right，区间[left, right]依然有效，所以用 <=
			middle = left + ((right - left) / 2);// 防止溢出 等同于(left + right)/2
			if (arr[middle] > key)
			{
				right = middle - 1; // key 在左区间，所以[left, middle - 1]
			}
			else if (arr[middle] < key)
			{
				left = middle + 1; // key 在右区间，所以[middle + 1, right]
			}
			else
			{ // arr[middle] == key
				break; // 数组中找到目标值，已知下标middle
			}
		}
		middle = key <= arr[middle] ? middle : middle + 1;//当left>right时，做判断
	}
	int* ret = (int*)calloc(len + 1, sizeof(int));//原数组扩容
	assert(ret);

	for (int i = 0; i < middle; i++)//前半部分不变
	{
		ret[i] = arr[i];
	}
	ret[middle] = key;//插入key
	for (int i = middle; i < len; i++)//插入位置及后面元素往后移一位
	{
		ret[i + 1] = arr[i];
	}
	return ret;
}


//遍历数组输出
template <class T>
void printArray(T* arr, int len)
{
	for (int i = 0; i < len; ++i)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << "\n\n";
}



int main()
{
	int arr[10] = { 1, 7, 4, 2, 5, 9, 6, 3, 8, 10 };
	int len = sizeof(arr) / sizeof(arr[0]);

	printArray<int>(arr, len);

	//////希尔排序
	//std::cout << "Shell_Sort 升序：\n";
	//Shell_Sort<int>(arr, len); //升序
	//printArray<int>(arr, len);

	//堆排序(从数组下标 0 开始排序)
	std::cout << "HeapSort大顶堆 输入升序序列：\n";
	HeapSort(arr, len);
	printArray<int>(arr, len);

	//////插入排序
	//std::cout << "Insert_Sort 降序：\n";
	//Insert_Sort<int>(arr, len, true);//降序
	//printArray(arr, len);
	

	
	////快速排序
	//std::cout << "Quick_Sort_2 降序：\n";
	//Quick_Sort_2<int>(arr, len, true);//降序
	//printArray(arr, len);
	
	////基数排序
	//Radix_Sort(arr, len ); //升序
	//printArray(arr, len);
	//
	////归并排序
	//Merge_Sort(arr, len , true); //降序
	//printArray(arr, len);
	
	////冒泡排序
	//Bubblesort1(arr, len);
	//BubbleSort2(arr, len);
	//for (int i = 0; i < 10; ++i)
	//{
	//	std::cout << arr[i]<<" ";
	//}
	//std::cout << "\n";
	// 
	////选择排序
	//Select_Sort<int>(arr, 10, isMax); //升序

	//Quick_Sort<int>(arr, 0, len - 1);//升序
	//在有序数组中插入数据，并保存数组有序
	//int key(0);
	//int arr[10] = { -12, -8, -5, -1, 0, 6, 9, 12, 16, 21 };
	//int len = sizeof(arr) / sizeof(arr[0]);
	//printf("有序数组插入前：\n");
	//printArray(arr, len);
	//printf("请输入插入的数字,输入-1结束：\n");
	//while (key != -1)
	//{
	//	scanf("%d", &key);
	//	int* res = search_insert(arr, len, key);
	//	printf("有序数组插入后：\n");
	//	printArray(res, len + 1);
	//	free(res);
	//	printf("数组重新插入数据：\n");
	//}
	getchar();
	return 0;
}



//KMP算法查找 字符串string haystack中是否出现过字符串string needle
//class Solution {
//public:
//	void getNext(int* next, const string& s)//next[]前缀表，(不右移，不-1), s为子串
//	{  //1.初始化
//		int j = 0;		//j指向前缀末尾，且j代表 最长相等前后缀的长度
//		next[0] = j;    //next[j]就是记录着j之前[0~j-1]的子串的 最长相等前后缀的长度
// 
//		for (int i = 1; i < s.size(); ++i)
//		{				//i指向后缀末尾，i从1开始
//     //2.前后缀不相同情况
//			while (j > 0 && s[i] != s[j])
//			{//直到遇见前后缀不相同, 为连续回退的过程，注意用while循环，
//				j = next[j - 1];  //向前回退,看前一位j-1的 前缀表的数值
//			}
//		//3.前后缀相同
//			if (s[i] == s[j])
//			{
//				++j;//同时向后移动i和j ，其中i++在for循环中
//			}
//		//4.更新next数值的值
//			next[i] = j;// 更新第i个位置的前缀表，将j（前缀的长度）赋给next[i]
//		}
//	}
// 
//	int strStr(string haystack, string needle)
//	{
//		if (needle.size() == 0)
//		{
//			return 0;
//		}
//		int next[needle.size()];
//		getNext(next, needle);
//		int j = 0;
//		for (int i = 0; i < haystack.size(); ++i)
//		{
//			while (j > 0 && haystack[i] != needle[j])
//			{// 不匹配
//				j = next[j - 1];// j 寻找之前匹配的位置
//			}
//			if (haystack[i] == needle[j])
//			{// 匹配，j和i同时向后移动
//				++j;// i++在for循环里
//			}
//			if (j == needle.size())
//			{// 文本串s里出现了模式串t,此时i指向模式串尾部
////返回当前在文本串匹配模式串的位置i 减去 (模式串的长度-1)
//				return (i - needle.size() + 1);//成功，返回模式串出现的第一个位置 (i从0开始)
//			}
//		}
//		return -1;
//	}
//};