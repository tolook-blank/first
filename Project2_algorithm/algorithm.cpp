#include"MyTools.hpp"
#include<assert.h>
#include<iostream>

void BuildMaxHeap(int A[], int len);
void HeapAdjust(int A[], int k, int len);
void HeapSort(int A[], int len);
void Insert_Heap(int A[], int len, int target);

//��������ѣ����ڵ��±���Ϊ 0��
void BuildMaxHeap(int A[], int len)
{
	for (int i = (len - 1)/ 2; i >= 0; --i)//�Ӻ���ǰ�������з��ն˽ڵ㣬��i=[len/2 , 1]
		HeapAdjust(A, i, len);
}

//����kΪ�������� ����Ϊ�����
void HeapAdjust(int A[], int k, int len) //kΪ�ѵĸ��ڵ㣬lenΪ�ѵĴ�С
{
	int temp = A[k];// temp�ݴ������ĸ��ڵ� 
	for (int i = 2*k; i <= len - 1; i *= 2) //iָ�� ��kΪ���ڵ�� �������ڵ�( 2*k )
	{
		if (i < len && A[i] < A[i + 1]) ++i;//ȡkey����������ڵ��±�
		if (temp >= A[i]) break;//�������ѣ��� >= ���ң�
		else //�����ڵ�ֵ С�� �����ڵ�ֵ
		{
			A[k] = A[i];//��ֵ����������ڵ� ������ ���ڵ�λ����
			k = i; //ԭ���ڵ�λ�ã�СԪ�أ�������׹
		}
	}
	A[k] = temp; //temp�����ԭ���ڵ�ֵ ��������λ��
}

//���ڴ���ѵ� ������ �õ� ��������
void HeapSort(int A[], int len)
{
	BuildMaxHeap(A, len); //��ʼ���ѣ�A[0]Ϊ�Ѷ�Ԫ��
	for (int i = len - 1; i > 0; --i) //iָ��ѵ�Ԫ��,n-1�˵Ľ����ͽ��ѹ���
	{
		Swap(A[i], A[0]); //�ѶѶ��Ͷѵ�Ԫ�ؽ��н���,��ŵ�A[i]����ʱ iָ���Ԫ���Ѿ�����
		HeapAdjust(A, 0, i - 1);//��ʣ���i-1�� ������Ԫ�� �����ɶ�;ֱ��ֻʣ1��Ԫ��
	}
}

void Insert_Heap(int A[], int len, int target)
{
	int temp = A[++len] = target;//�½ڵ����ѵ�,��temp����
	int i;
	for (i = len-1; i > 0; --i)// 1. ���½ڵ��±�i=0��Ϊ���ڵ㣩����������
	{
		if (temp > A[i / 2])//�½ڵ�ֵ���ڸ��ڵ�ֵ�����ϸ�
		{
			A[i] = A[i / 2];//���ڵ�ֵ�³�
			i = i / 2;//���� �½ڵ���±꣬�����´��ϸ�	
		}
		else break; // 2. ���½ڵ�ֵС�ڸ��ڵ�ֵ������ѵ�������
	}
	A[i] = temp; //�½ڵ��������λ��
}





//1.ð��������򵥵Ľ�������  ��á����ƽ��ʱ�临�ӶȾ�ΪO��n^2)
//�ں����ⶨ�����飬ͨ���βδ��뺯�����ں������޸�����
void Bubblesort1(int array[], int len)
{
	for (int i = 1; i < len; ++i)
	{//���ƱȽ��ִΣ�һ�� n-1 ��
		for (int j = 0; j < len - i; ++j)
		{//�����������ŵ�Ԫ�ؽ��бȽ�
			if (array[j] > array[j + 1])
			{
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}


//1.n �Ż�ð������������������
//������Ҫ�������飬����һ������ָ��ĺ���
int* BubbleSort2(int arr[], int len)//�β�int* arr��int arr[]������
{
	if (arr == NULL || len < 2)
	{
		return arr;
	}
	//��¼���һ�ν�����λ��
	int lastExchangeIndex = 0;
	//�������еı߽�,ѭ��ֹͣ�߽�
	int sortBorder = len - 1;
	for (int i = 1; i < len; ++i)
	{
		bool isSorted = true;//�����ǣ�ÿ�ֳ�ʼ��������
		for (int j = 0; j < sortBorder; ++j)
		{

			if (arr[j] > arr[j + 1])
			{
				isSorted = false;//��Ԫ�ؽ�������������������
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


//4.ϣ�������ǲ��������Ż�
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


//���ַ�����Ԫ�ز����λ��
int* search_insert(int* arr, int len, int key)
{
	int left(0);
	int right = len - 1;
	int middle(0);
	if (key >= arr[right])//��key���ڵ����������ֵ�������ұ߲���
	{
		middle = right + 1;
	}
	else if (key <= arr[left])//С�ڵ�����Сֵ��������߲���
	{
		middle = 0;
	}
	else// ��key������ұյ������[left, right]
	{
		while (left <= right)
		{ // ��left==right������[left, right]��Ȼ��Ч�������� <=
			middle = left + ((right - left) / 2);// ��ֹ��� ��ͬ��(left + right)/2
			if (arr[middle] > key)
			{
				right = middle - 1; // key �������䣬����[left, middle - 1]
			}
			else if (arr[middle] < key)
			{
				left = middle + 1; // key �������䣬����[middle + 1, right]
			}
			else
			{ // arr[middle] == key
				break; // �������ҵ�Ŀ��ֵ����֪�±�middle
			}
		}
		middle = key <= arr[middle] ? middle : middle + 1;//��left>rightʱ�����ж�
	}
	int* ret = (int*)calloc(len + 1, sizeof(int));//ԭ��������
	assert(ret);

	for (int i = 0; i < middle; i++)//ǰ�벿�ֲ���
	{
		ret[i] = arr[i];
	}
	ret[middle] = key;//����key
	for (int i = middle; i < len; i++)//����λ�ü�����Ԫ��������һλ
	{
		ret[i + 1] = arr[i];
	}
	return ret;
}


//�����������
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

	//////ϣ������
	//std::cout << "Shell_Sort ����\n";
	//Shell_Sort<int>(arr, len); //����
	//printArray<int>(arr, len);

	//������(�������±� 0 ��ʼ����)
	std::cout << "HeapSort�󶥶� �����������У�\n";
	HeapSort(arr, len);
	printArray<int>(arr, len);

	//////��������
	//std::cout << "Insert_Sort ����\n";
	//Insert_Sort<int>(arr, len, true);//����
	//printArray(arr, len);
	

	
	////��������
	//std::cout << "Quick_Sort_2 ����\n";
	//Quick_Sort_2<int>(arr, len, true);//����
	//printArray(arr, len);
	
	////��������
	//Radix_Sort(arr, len ); //����
	//printArray(arr, len);
	//
	////�鲢����
	//Merge_Sort(arr, len , true); //����
	//printArray(arr, len);
	
	////ð������
	//Bubblesort1(arr, len);
	//BubbleSort2(arr, len);
	//for (int i = 0; i < 10; ++i)
	//{
	//	std::cout << arr[i]<<" ";
	//}
	//std::cout << "\n";
	// 
	////ѡ������
	//Select_Sort<int>(arr, 10, isMax); //����

	//Quick_Sort<int>(arr, 0, len - 1);//����
	//�����������в������ݣ���������������
	//int key(0);
	//int arr[10] = { -12, -8, -5, -1, 0, 6, 9, 12, 16, 21 };
	//int len = sizeof(arr) / sizeof(arr[0]);
	//printf("�����������ǰ��\n");
	//printArray(arr, len);
	//printf("��������������,����-1������\n");
	//while (key != -1)
	//{
	//	scanf("%d", &key);
	//	int* res = search_insert(arr, len, key);
	//	printf("������������\n");
	//	printArray(res, len + 1);
	//	free(res);
	//	printf("�������²������ݣ�\n");
	//}
	getchar();
	return 0;
}



//KMP�㷨���� �ַ���string haystack���Ƿ���ֹ��ַ���string needle
//class Solution {
//public:
//	void getNext(int* next, const string& s)//next[]ǰ׺��(�����ƣ���-1), sΪ�Ӵ�
//	{  //1.��ʼ��
//		int j = 0;		//jָ��ǰ׺ĩβ����j���� ����ǰ��׺�ĳ���
//		next[0] = j;    //next[j]���Ǽ�¼��j֮ǰ[0~j-1]���Ӵ��� ����ǰ��׺�ĳ���
// 
//		for (int i = 1; i < s.size(); ++i)
//		{				//iָ���׺ĩβ��i��1��ʼ
//     //2.ǰ��׺����ͬ���
//			while (j > 0 && s[i] != s[j])
//			{//ֱ������ǰ��׺����ͬ, Ϊ�������˵Ĺ��̣�ע����whileѭ����
//				j = next[j - 1];  //��ǰ����,��ǰһλj-1�� ǰ׺�����ֵ
//			}
//		//3.ǰ��׺��ͬ
//			if (s[i] == s[j])
//			{
//				++j;//ͬʱ����ƶ�i��j ������i++��forѭ����
//			}
//		//4.����next��ֵ��ֵ
//			next[i] = j;// ���µ�i��λ�õ�ǰ׺����j��ǰ׺�ĳ��ȣ�����next[i]
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
//			{// ��ƥ��
//				j = next[j - 1];// j Ѱ��֮ǰƥ���λ��
//			}
//			if (haystack[i] == needle[j])
//			{// ƥ�䣬j��iͬʱ����ƶ�
//				++j;// i++��forѭ����
//			}
//			if (j == needle.size())
//			{// �ı���s�������ģʽ��t,��ʱiָ��ģʽ��β��
////���ص�ǰ���ı���ƥ��ģʽ����λ��i ��ȥ (ģʽ���ĳ���-1)
//				return (i - needle.size() + 1);//�ɹ�������ģʽ�����ֵĵ�һ��λ�� (i��0��ʼ)
//			}
//		}
//		return -1;
//	}
//};