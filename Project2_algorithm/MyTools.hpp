#pragma once

//��������,Ƕ���еĺ���ģ�壬Ҫ�����ڵ��ú���֮ǰ
template <class T>
void Swap(T& a, T& b);

//1.ð������
template <class T>
void Bubble_Sort(T arr[], int len, bool reverse = false);  //����Ĭ��falseΪ����,����ʱ��ҪĬ��ֵ,�����ظ�����


//2.ѡ������
template <typename T>
void Select_Sort(T* arr, int len, bool (*pFun)(T, T));

//3.��������
template <typename T>
void Insert_Sort(T* arr, int len, bool reverse = false); //Ĭ������

//4.ϣ�������ǲ��������Ż�
template <typename T>
void Shell_Sort(T* arr, int size, bool reverse = false); //Ĭ������

//5.��������_1
template <typename T>
void Quick_Sort(T* arr, int begin, int end, bool reverse = false); //Ĭ������

//��������_1�ݹ��������
template  <typename T>
int partition(T arr[], int begin, int end, bool reverse); //ģ������,������÷�������ʱδ����


//5.��������_2
template <typename T>
void Quick_Sort_2(T* arr, int size, bool reverse = false);

//��������_2�ݹ��������
template  <typename T>
void _Quick_Sort_2(T arr[], int begin, int end, bool reverse);


//6.��������(ֻ���÷Ǹ�����,����Ҫģ�廯)
void Radix_Sort(int arr[], int size, bool reverse = false); //Ĭ������


//7.�鲢������ں���
template  <typename T>
void Merge_Sort(T arr[], int size, bool reverse = false);

//�ݹ��ֺ���
template  <typename T>
void _Merge(T arr[], int left, int right, bool reverse);

//2·�鲢���򣬽��������� arr[low,mid] �� arr[mid+1,high]�鲢Ϊһ���µ���������
template  <typename T>
void _Merge_In_Arr(T arr[], int left, int mid, int right, bool reverse);


//���ַ�����,����Ŀ��ֵ�±꣬����[low,high]
template  <typename T>
T Binary_Search(T arr[], int len, T target);//(��������,���ظ�Ԫ������)


//��̬������ģ��
template <class T> class MyArr;

//ѭ��������ģ��
template <class T> class MyQueue;

//���νṹ - ���� - ���ͱ�� - ģ����
template<typename T> class CMyTree_List;

//���νṹ - ˳����
template<typename T> class CMyTree_Arr;

//�ѽṹ - ���� - ��ģ��
template<typename T> class CMyHeap;


//��������
template <class T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}


//1.ð������
template <class T>
void Bubble_Sort(T arr[], int len, bool reverse)  //Ĭ��falseΪ��������
{
	T tempVal;//��ʱ������ѭ���ⶨ�壬�����ظ������������
	bool flag;
	for (int i = 1; i < len; ++i) //i��ʾ��i������ÿ��ѡ�����ֵ�����������
	{
		flag = false;//����ð�������Ƿ��������ı��
		for (int j = 0; j < len - i; ++j)
		{
			if (arr[j] > arr[j + 1] && reverse == false) //��С����
			{
				Swap(arr[j], arr[j + 1]);//����
				flag = true;
			}

			if (arr[j] < arr[j + 1] && reverse == true)  //����
			{
				Swap(arr[j], arr[j + 1]);
				flag = true;
			}
		}
		if (flag == false)//���˱���������������˵�����Ѿ�����
			return;
	}
}



//2.ѡ������
template <typename T>
void Select_Sort(T* arr, int len, bool (*pFun)(T, T))
{
	T temp(0), min(0);
	for (int i = 0; i < len - 1; ++i)//i��ʾ��i��������Ҫn-2��
	{
		min = i;//����i��Ϊ��ǰ��Сֵ���±�
		for (int j = i + 1; j < len; ++j)//ѡ�����Сֵ���±꣬��min����
		{
			//if (arr[min] > arr[j])
			//	min = j;
			if (pFun(arr[min], arr[j]))
			{
				min = j;
			}
		}
		if (min != i)//��min�����ı�
		{
			Swap(arr[i], arr[min]);//������Сֵ�±�Ԫ�ص�ֵ
		}
	}
}

template <typename T>
bool isMax(T a, T b)  //����
{
	return a > b;
}

template <typename T>
bool isMin(T a, T b)  //����
{
	return a < b;
}

//3.��������
template <typename T>
void Insert_Sort(T* arr, int len, bool reverse) //reverse = false,Ĭ������
{
	T temp(0);
	int j(0);
	//���ѭ�� ����������
	for (int i = 1; i < len; ++i)//�±�i=0Ԫ����Ϊ���򣬲�����ֵ���±��1��ʼ
	{
		if (reverse == false)//��С����
		{
			if (arr[i] < arr[i - 1])//��ǰ��Ԫ�� ���� ��ǰԪ��ʱ������Ҫ����
			{
				temp = arr[i];//������������������
				//��������С����������Ԫ�أ���Ҫǰ�ƣ�ֱ����������Ԫ��ʱ���루���ֲ���ǰ�������
				for (j = i - 1; j >= 0 && temp < arr[j]; j -= 1)//jΪ���򲿷ֵ��±꣬j��iǰ
				{
					arr[j + 1] = arr[j];//�������ݺ��ƣ��ճ�λ��
				}
			}
		}
		else //reverse == true �Ӵ�С
		{
			if (arr[i] > arr[i - 1])//��ǰ��Ԫ�� С�� ��ǰԪ��ʱ������Ҫ����
			{
				temp = arr[i];//������������������
				for (j = i - 1; j >= 0 && temp > arr[j]; j -= 1)
				{
					arr[j + 1] = arr[j];
				}
			}
		}
		arr[j + 1] = temp;//j�ĺ�һ����Ǵ�����Ԫ�ص��±�
	}
}

//4.ϣ�������ǲ��������Ż�
template <typename T>
void Shell_Sort(T* arr, int size, bool reverse)
{
	T temp;
	int j, i;
	//�������� ���������[1 2 3 4 1 2 3 4],�����ͬ���飬��Ӧ�±����ֵ = ������4
	int jump = size >> 1;//������ҲΪ����,ֱ�Ӳ��������в���Ϊ1
	while (jump > 0)
	{
		//���ѭ�� ����������
		for (i = jump; i < size; ++i)//ѭ��������������ļ��ٶ�����
		{
			temp = arr[i];//������������������
			if (reverse == false)//��С����
			{
				//jΪ���򲿷ֵ��±꣬j��iǰ�����ڲ���λ��
				//��tempС������Ԫ�أ�����ǰ�ƣ�ֱ����������Ԫ��arr[j]��������̱�������
				for (j = i - jump; j >= 0 && temp < arr[j]; j -= jump)
				{
					arr[j + jump] = arr[j];//�������ݺ��ƣ��ճ�λ��
				}
			}
			else //reverse == true �Ӵ�С
			{
				for (j = i - jump; j >= 0 && temp > arr[j]; j -= jump)
				{
					arr[j + jump] = arr[j];
				}
			}
			arr[j + jump] = temp;//j�ĺ�һ����Ǵ�����Ԫ�ص��±�
		}
		jump >>= 1;//ÿ�������꣬�������,ֱ�����jump=1(ÿ��ֻ��1��Ԫ��)
	}
}

//5.��������_1
template <typename T>
void Quick_Sort(T* arr, int begin, int end, bool reverse)  //�������򣨵ݹ飩,Ĭ������
{
	if (begin < end)//�ݹ���������
	{
		int pivot = partition(arr, begin, end, reverse); //��������Ļ�׼�±�
		Quick_Sort(arr, begin, pivot-1, reverse);//�������
		Quick_Sort(arr, pivot + 1, end, reverse);//�����ұ�
	}
}

//ָ�뽻��������ߴ��ڻ�׼��Ԫ�غ��ұ�С�ڻ�׼��Ԫ�ؽ���
template  <typename T>
int partition(T arr[], int low, int high, bool reverse)  //��������
{
	T pivot = arr[low];//���赱ǰ������Ԫ��Ϊ��׼����ʼ���л���
	//low��ߵ�Ԫ�� < ��׼pivot , high�ұߵ�Ԫ�ض�Ҫ >= pivot
	while (low < high) //ѭ���������� low >= high
	{	
		if (reverse == false)//����,Ĭ��
		{
			while (arr[high] >= pivot && low < high)
				--high;
			arr[low] = arr[high]; //�ѱȻ�׼С��Ԫ�� �ƶ������
			while (arr[low] <= pivot && low < high)
				++low;
			arr[high] = arr[low]; //�ѱȻ�׼���Ԫ�� �ƶ����Ҷ�
		}

		if (reverse == true)//����
		{
			while (arr[high] <= pivot && low < high)
				--high;
			arr[low] = arr[high]; //�ѱȻ�׼���Ԫ�� �ƶ������

			while (arr[low] >= pivot && low < high)
				++low;
			arr[high] = arr[low]; //�ѱȻ�׼С��Ԫ�� �ƶ����Ҷ�
		}
	}
	arr[low] = low;//��׼Ԫ�ش�ŵ�����λ��
	return low;	//���ػ�׼�����±�
}


//5.��������_2
template <typename T>
void Quick_Sort_2(T* arr, int size, bool reverse)  //�������򣨵ݹ飩,Ĭ������
{
	_Quick_Sort_2(arr, 0, size - 1, reverse);
}

template  <typename T>
void _Quick_Sort_2(T arr[], int begin, int end, bool reverse)  //��������
{
	T pivot = arr[begin]; //��ʼ��arr[low]Ϊ���
	//��������Ϊ [low + 1 , high] 
	int left = begin + 1; //С�α�
	int right = end;	  //���α�

	//�ݹ�������� - ��������ֻ��1��Ԫ��
	if (begin >= end)
		return;
	//��ʽ���� - ������������
	while (left <= right) //��ǰ��
	{
		if (reverse == false) //����
		{
			while (arr[right] >= pivot && left <= right)
			{
				right--;//right���˴��ڱ�˵�ֵ������ͣס
			}
			while (arr[left] <= pivot && left <= right)
			{
				left++;//left����С�ڱ�˵�ֵ������ͣס
			}
		}
		else//����
		{
			while (arr[right] <= pivot && left <= right)
			{
				right--;
			}
			while (arr[left] >= pivot && left <= right)
			{
				left++;
			}
		}
		//left��right��ͣס
		if (left < right)//���仹û�����꣬���໥����
		{
			Swap(arr[left], arr[right]);
			left++;//���������������������α�����ƶ�һ��
			right--;
		}
	}
	//��left > high ������ѭ������ʱrightָ���ֵС�ڱ�ˣ�leftָ��ֵ���ڱ��
	//�� arr[high]���˽���������ʹ�� ���б���[��� < ��� < �ұ�]�ĸ�ʽ
	arr[begin] = arr[right];
	arr[right] = pivot;
	//���һ�� �ݹ���������
	_Quick_Sort_2(arr, begin, right - 1, reverse);
	_Quick_Sort_2(arr, right + 1, end, reverse);
}


//7.�鲢������ں���
template  <typename T>
void Merge_Sort(T arr[], int size, bool reverse)
{
	_Merge(arr, 0, size - 1, reverse);
}

template  <typename T>
void _Merge(T arr[], int left, int right, bool reverse)//�ݹ��ֺ���
{
	//�ݹ��������
	if (left >= right)//����һ��Ԫ��
		return;
	int mid = left + ((right - left) >> 1);//�۰���ң�( low + high )/2 ���ܻ�����ֵ���

	//�ݹ����
	_Merge(arr, left, mid, reverse);
	//�ݹ��ұ�
	_Merge(arr, mid + 1, right, reverse);

	//��·�鲢
	_Merge_In_Arr(arr, left, mid, right, reverse);
}

//������������ arr[low,mid] �� arr[mid+1,high]�鲢Ϊ�µ���������
template  <typename T>
void _Merge_In_Arr(T arr[], int left, int mid, int right, bool reverse)//�ϲ�����
{
	//׼�� �������� ������¼�±������ı���
	int length = right - left + 1;//Ԫ����
	T* pData = new T[length];
	//��ʼ��
	memset(pData, 0, sizeof(int) * length);

	//�����±���������
	int low, hig, index = 0;//��� �ұ� ��������
	low = left;//���
	hig = mid + 1;//�ұ�
	if (reverse == false) //����
	{
		//������䣨left, mid)	��	�ұߣ�mid + 1, high)
		while (low <= mid && hig <= right)//��ǰ��
		{
			//������������� �� arr[low]��С���ȹ鲢
			while (low <= mid && arr[low] <= arr[hig])
			{
				pData[index++] = arr[low++];
			}
			//������������� �� arr[hig]��С���ȹ鲢
			while (hig <= right && arr[low] > arr[hig])
			{
				pData[index++] = arr[hig++];
			}
		}
	}
	else //����
	{
		//������䣨left, mid)	��	�ұߣ�mid + 1, high)
		while (low <= mid && hig <= right)//��ǰ��
		{
			//������������� �� arr[hig]�ϴ��ȹ鲢
			while (hig <= right && arr[hig] >= arr[low])
			{
				pData[index++] = arr[hig++];
			}
			//������������� �� arr[low]�ϴ��ȹ鲢
			while (low <= mid && arr[low] > arr[hig])
			{
				pData[index++] = arr[low++];
			}
		}
	}
	//ѭ������ ������һ������Ϊ�գ� ʣ�µ�����ֱ�ӿ����ڴ�
	if (low <= mid)//�����ʣ
	{
		//�ڴ��ƶ����� ������ Ŀ�ĵصĵ�ַ  ��Դ�صĵ�ַ �ֽ���
		memmove(&pData[index], &arr[low], sizeof(int) * (mid - low + 1));
	}
	if (hig <= right)//�ұ���ʣ
	{
		memmove(&pData[index], &arr[hig], sizeof(int) * (right - hig + 1));
	}

	//���һ�����������������������ļ�¼ ��Ҫ������ԭ����
	memmove(&arr[left], pData, sizeof(int) * length);
	delete[] pData;
}



//6.��������(���÷Ǹ�����)
void Radix_Sort(int arr[], int size, bool reverse)
{
	if (size < 2)//Ԫ������С��2����������
		return;

	//1��׼��Ͱ��
	//int tempArr[size][10] = {};
	int** tempArr = new int* [size];
	for (int x = 0; x < size; ++x)
	{
		tempArr[x] = new int[10];
	}
	int i, j, num, index;
	//2.1��Ͱ�ӳ�ʼ��
	for (i = 0; i < size; i++) //��������������
	{
		for (j = 0; j < 10; j++) //0~9
		{
			//��ʼ����ֵһ���ǲ����������г��ֵ�ֵ
			tempArr[i][j] = -1;
		}
	}
	//2��ѭ��
	for (int n = 1; n <= 100; n *= 10) //n = 1��10��100 �ֱ��ʾ�� ʮ ��λ
	{
		//2.2��������Ͱ
		for (i = 0; i < size; ++i)
		{
			index = arr[i] / n % 10;//Ͱ�ӱ��,�����λ(��λ)��ʼ���ٴε�λ...������λ
			tempArr[i][index] = arr[i];
		}

		//2.3�����ݳ�Ͱ - ���ű���
		num = 0;//һ��Ҫ��ѭ���ڲ���ʼ��
		if (reverse == false)//�������ݳ�Ͱ�����Ͽ�ʼ���������϶��±�����ֱ������
		{
			for (i = 0; i < 10; ++i)//��
			{
				for (j = 0; j < size; ++j)//��
				{
					if (tempArr[j][i] != -1)
					{
						arr[num++] = tempArr[j][i]; //���ݳ�Ͱ��
						tempArr[j][i] = -1;	//����Ϊ-1���Ͳ����ٳ�ʼ��һ������Ͱ��
					}
					//����Ҫ else break
				}
			}
		}
		else	//�������ݳ�Ͱ�����¿�ʼ���������¶��ϱ�����ֱ������
		{
			for (i = 9; i >= 0; --i)//��
			{
				for (j = size - 1; j >=0; --j)//��
				{
					if (tempArr[j][i] != -1)
					{
						arr[num++] = tempArr[j][i]; //���ݳ�Ͱ��
						tempArr[j][i] = -1;	//����Ϊ-1���Ͳ����ٳ�ʼ��һ������Ͱ��
					}
					//����Ҫ else break
				}
			}
		}

	}

	for (int x = 0; x < size; ++x)
	{
		delete[] tempArr[x];
	}
	delete[] tempArr;

}



//(�������ظ�Ԫ������)���ֲ���,����Ŀ��ֵ�±� [low,high]
template  <typename T>
T Binary_Search(T arr[], int len, T target)
{
	int left = 0;
	int right = len - 1;//������˵��ܹ�ȡ��
	int mid;//��λ���±�
	while (left <= right)// ��left==right������[low, high]��Ȼ��Ч�������� <=
	{
		//��һ�� ȷ����λ��
		mid = left + ((right - left) >> 1);//��ͬ��(low + high)/2
		//�ڶ��� ��Ŀ��ֵ�Ƚ�,������λ��,����������С
		if (target < arr[mid])//target ��������
		{
			right = mid - 1;//������СΪ[low, middle - 1]
		}
		else if (target > arr[mid])// target ��������
		{
			left = mid + 1; //[middle + 1, high]
		}
		else //target == arr[mid],�ҵ�Ŀ��ֵ��ֱ�ӷ����±�
		{
			return mid;
		}
	}
	return -1;// δ�ҵ�Ŀ��ֵ
}


//��̬������ģ��
template <class T>
class MyArr				//��STL�е�vector
{
	T* pBuff;			//��̬������׵�ַ
	size_t	maxSize;	//��̬��������ĳ���
	size_t	len;		//��ǰ�����е�Ԫ�ظ���
public:
	MyArr();
	MyArr(int length);     //����ָ����С��̬����
	MyArr(MyArr const& other); //�ж��ڴ棬��д�������캯���������
	~MyArr();
public:
	MyArr& operator=(MyArr const& srcArr);//�ж��ڴ棬���ظ�ֵ��������ȿ��������������ڴ棩
public:
	void clear();							//�ͷŶ�̬�ڴ�
	void appendVal(T const& val);			//β���������
	void insert(size_t index, T const& val);//���±����Ԫ��
	void earse(size_t index);				//���±�ɾ��Ԫ��
	void addCapacity();						//���ݺ���
public:
	T const* getArrHead() const { return pBuff; }
	size_t getArrLen() const { return len; }
};

template <class T>
MyArr<T>::MyArr()
{
	pBuff = nullptr;
	maxSize = len = 0;
}

template <class T>
MyArr<T>::MyArr(int length)
{
	len = 0;
	maxSize = length;
	pBuff = new T[maxSize];
}

template <class T>
MyArr<T>::MyArr(MyArr const& other)
{
	*this = other;	//ͨ�����ظ�ֵ=�����,�򻯴���
	//maxSize = other.maxSize;
	//len = other.len;
	//pBuff = nullptr;
	//if (maxSize > 0)
	//{
	//	pBuff = new T[maxSize];
	//	memset(pBuff, 0, sizeof(T)* maxSize);
	//	for (size_t i = 0; i < len; ++i)
	//	{
	//		pBuff[i] = other.pBuff[i];
	//	}
	//}
}

template <class T>
MyArr<T>& MyArr<T>::operator=(MyArr const& srcArr)
{
	clear();//���ԭ�ڴ�
	maxSize = other.maxSize;
	len = other.len;
	pBuff = nullptr;
	if (maxSize > 0)
	{
		pBuff = new T[maxSize];
		memset(pBuff, 0, sizeof(T) * maxSize);
		for (size_t i = 0; i < len; ++i)
		{
			pBuff[i] = other.pBuff[i];
		}
	}
}

template <class T>
MyArr<T>::~MyArr()
{
	//if (pBuff)
	//	delete[] pBuff;
	//pBuff = nullptr;
	//maxSize = len = 0;
	clear();
}

template <class T>
void MyArr<T>::clear()
{
	if (pBuff)
		delete[] pBuff;
	pBuff = nullptr;
	maxSize = len = 0;
}

template <class T>
void MyArr<T>::addCapacity()
{
	maxSize = maxSize + ((maxSize >> 1) > 1 ? (maxSize >> 1) : 1);
	T* tempBuff = new T[maxSize];
	for (size_t i = 0; i < len; ++i)
		tempBuff[i] = pBuff[i];
	if (pBuff) delete[] pBuff;
	pBuff = tempBuff;
}

template <class T>
void MyArr<T>::appendVal(T const& val) //β������Ԫ��
{
	addCapacity();
	if (len >= maxSize)//��ʾ��ǰ�ռ�Ԫ�ط���,�Զ�����
	{
		addCapacity();
	}
	pBuff[len++] = val;
}

template <class T>
void MyArr<T>::insert(size_t index, T const& val)
{
	if (len >= maxSize)//��ʾ��ǰ�ռ�Ԫ�ط���
	{
		addCapacity();
	}
	for (size_t i = len - 1; i >= index; --i)//�Ӻ���ǰ��[index,len-1]Ԫ�����κ��Ƶ�[index+1,len]
	{
		pBuff[i + 1] = pBuff[i];
	}
	pBuff[index] = val;
	len++;
}

template <class T>
void MyArr<T>::earse(size_t index)
{
	if (index >= len || index < 0)
		throw "index exception";
	for (size_t i = index + 1; i < len; ++i)//��ǰ����[index+1,len-1]Ԫ������ǰ�Ƶ�[index,len-2]
	{
		pBuff[i - 1] = pBuff[i];
	}
	len--;
}


//ѭ������
template <typename T>
class MyQueue {
	T* que_arr;		 //��̬����,�洢MaxSize-1��Ԫ��, ��һ��λ�������ж϶���
	size_t front, rear; //��ͷ�±�,��β�±�(rearָ�����һ��Ԫ�ص���һλ�ã���ָ��Ԫ��)
	size_t size, maxSize;
public:
	MyQueue();
	MyQueue(size_t); //�Զ����С����
	MyQueue(MyQueue const& other);//�ж��ڴ棬��д�������캯���������
	~MyQueue();
public:
	MyQueue& operator = (MyQueue const& other); //�ж��ڴ棬���ظ�ֵ��������ȿ��������������ڴ������
public:
	void clear();			//�ͷŶ�̬�ڴ�
	void addCapacity();
	bool enQueue(T const&); //���
	bool deQueue();			//����
public:
	bool getFront(T&) const;
	bool getRear(T&) const;
	bool isEmpty()const { return rear == front; }//�ӿգ���ȼ��ɲ���ҪΪ0
	bool isFull()const { return (rear + 1) % maxSize == front; }//��������ͷָ���ڶ�β����һλ��
	size_t getSize() const { return size; }
	T const* getQue_arr() const { return que_arr; }  //��ȡ�����ڲ�������ָ��
};

template <typename T>
MyQueue<T>::MyQueue()	//Ĭ�Ϲ��캯��
{
	que_arr = nullptr;
	front = rear = 0;   //�ն��У�rear��front���
	maxSize = size = 0;
}

template <typename T>
MyQueue<T>::MyQueue(size_t Custom_size) //��ͨ���캯��
{
	front = rear = 0;
	size = 0;
	maxSize = Custom_size;		//�Զ����С
	que_arr = new T[maxSize];
}

template <typename T>
MyQueue<T>::MyQueue(MyQueue const& other)  //�������캯��
{
	*this = other;//ͨ�����ظ�ֵ=�����,�򻯴���
}

template <typename T>
MyQueue<T>& MyQueue<T>::operator = (MyQueue const& other)  //��ֵ���������
{
	clear();//�ڸ�ֵ֮ǰ,��ȷ���Լ��Ķ��ڴ���û������,����һ���ڴ�
	front = other.front;
	rear = other.rear;
	size = other.size;
	maxSize = other.maxSize;
	que_arr = nullptr;
	if (maxSize > 0)
	{
		que_arr = new T[maxSize];
		memset(que_arr, 0, sizeof(T) * maxSize);
		for (size_t i = 0; i < len; ++i)//����other��que_arr���е�����
		{
			que_arr[i] = other.que_arr[i];
		}
	}
}

template <typename T>
MyQueue<T>::~MyQueue()
{
	clear();
}

template <typename T>
void MyQueue<T>::clear()
{
	if (que_arr)
	{
		delete[] que_arr;
		que_arr = nullptr;
		front = rear = 0;
		maxSize = size = 0;
	}
}

template <class T>
void MyQueue<T>::addCapacity()
{
	maxSize = maxSize + ((maxSize >> 1) > 1 ? (maxSize >> 1) : 1);
	T* tempQueArr = new T[maxSize];
	for (size_t i = 0, j = front; i < size; ++i) //Ԫ�ظ���,ע��ѭ������Ԫ���±�
		tempQueArr[i] = que_arr[(i + j) % maxSize];
	if (que_arr) delete[] que_arr;
	que_arr = tempQueArr;
	front = 0;	//���ݺ�,���б����ı仯
	rear = size;
}

template <typename T>
bool MyQueue<T>::enQueue(T const& elem) //���
{
	if (isFull())//��ѭ������������������
	{
		addCapacity();
	}
	que_arr[rear] = elem;  //�ڶ�β��Ԫ�����
	rear = (rear + 1) % maxSize; //�±��ѭ��
	++size;
	return true;
}

template <typename T>
bool MyQueue<T>::deQueue() //��ͷԪ�س���
{
	if (isEmpty())	//����Ϊ�գ�û��Ԫ��
	{
		return false;
	}
	front = (front + 1) % maxSize;
	--size;
	return true;
}

template <typename T>
bool MyQueue<T>::getFront(T& elem) const
{
	if (isEmpty())
	{
		return false;
	}
	elem = que_arr[front];  //���ض�ͷԪ��
	return true;
}

template <typename T>
bool MyQueue<T>::getRear(T& elem) const
{
	if (isEmpty())
	{
		return false;
	}
	elem = que_arr[rear];  //���ض�βԪ��
	return true;
}

template<typename T>
struct TreeNode {
	//Բ�� - ������
	T data;
	//3���� - ���ָ��
	TreeNode* pParent;//�����ָ��
	TreeNode* pBrother;//�ֵܽ��ָ��
	TreeNode* pChild;//�ӽ��ָ��
};

//���νṹ - ���� - ���ͱ�� - ģ����
template<typename T>
class CMyTree_List {
	//�������� - ���������  ;����ʹ����Ҫ���� CMyTree_List<T>:: +   (�� TreeNode* ...)
	TreeNode* pRoot;//���ڵ�
public:
	//��Ա���� - �������� ��ɾ��� - ����
	CMyTree_List();
	~CMyTree_List();
public:
	void clear();//������������Ե������ã�Ҳ���Ը��������ã�
	bool find(T const& findData);//����
	//���� 3������ �� �������� �ο����� ���뷽��-�ֵ�/����
	void insert(T const& insertData, T const& findData, bool isChild);
	void deleteNode(T const& findData);
private:
	//˽�нӿ� - ������ʹ�õĺ���
	void _clear(TreeNode<T> *& root);//���
	//��Ϊ�漰�ݹ飬����ʧ��, ���������д������
	TreeNode<T>* _find(TreeNode<T>* root, T const& findData);
};

template<typename T>
CMyTree_List<T>::CMyTree_List()
{
	pRoot = nullptr;//����
}

template<typename T>
CMyTree_List<T>::~CMyTree_List()
{
	clear();
}

template<typename T>
void CMyTree_List<T>::clear()
{
	_clear(pRoot);//�Ͼ�ɱ��
}

template<typename T>
void CMyTree_List<T>::_clear(TreeNode<T> *& root) //����Ϊָ������ã���ֻ����һ��ָ�루ֵ���ݣ������ʵ�ε�pRootָ��û�б��޸ģ��ᵼ�¸��ڵ�ָ���Ǹ�Ұָ�롣
{
	if (root/* != nullptr*/)//�����������еݹ飬�����Զ�����
	{
		//�ȵݹ��ֵܣ��ٵݹ����
		_clear(root->pBrother);
		_clear(root->pChild);
		//�ݹ���� �� ����ɾ��
		delete root;
		root = nullptr;
	}
}

template<typename T>
bool CMyTree_List<T>::find(T const& findData)
{
	return (_find(pRoot, findData) != nullptr);
}

template<typename T>
TreeNode<T>* CMyTree_List<T>::_find(TreeNode<T>* root, T const& findData)
{
	//����������1���ҵõ���2���Ҳ�����
	if (root)//2���Ҳ�����
	{
		if (root->data == findData)//1���ҵõ���
		{
			return root;
		}
		//�ȵݹ��ֵ�
		TreeNode* pTemp = _find(root->pBrother, findData);
		if (pTemp)
			return pTemp;
		else//�����ֵܷ���ֻ�����ڶ��ӷ���
			return _find(root->pChild, findData);
	}
	else//�Ҳ������ͷ��ؿ�
		return nullptr;
}


template<typename T>
void CMyTree_List<T>::insert(T const& insertData, T const& findData, bool isChild)
{
	// Ҫ׼��һ�����
	TreeNode* tempInsertNode = new TreeNode;
	TreeNode*& tINode = tempInsertNode;//��ָ�������
	tINode->data = insertData;
	tINode->pParent = nullptr;
	tINode->pBrother = nullptr;
	tINode->pChild = nullptr;

	//��ʼ����
	if (pRoot)	//�ǿ�������
	{
		TreeNode* pFind = _find(pRoot, findData);	//��ȡ�ο���㣨����λ�ã�
		if (pFind)		//���ڲο��ڵ㣨����λ�ã�
		{
			if (isChild) //������ڵ�Ϊ���ӽڵ�
			{
				//���ӷ������
				if (pFind->pChild) //�Ѿ��ж���
				{
					//����С�Ķ��� - 5
					TreeNode* pTemp = pFind->pChild;
					while (pTemp->pBrother)
					{
						pTemp = pTemp->pBrother;
					}
					//�ҵ�����С�Ķ���
					pTemp->pBrother = tINode;
					tINode->pParent = pFind;
				}
				else	//û�ж���
				{
					//������ - 4
					pFind->pChild = tINode;
					tINode->pParent = pFind;
				}
			}
			else	//������ڵ�Ϊ�ֵܽڵ�
			{
				//�ֵܷ������ - 3
				TreeNode* pTemp = pFind;
				while (pTemp->pBrother)
				{
					pTemp = pTemp->pBrother;
				}
				//�ҵ�����С���ֵ�
				pTemp->pBrother = tINode;
				tINode->pParent = pFind->pParent;
			}
		}
		else	//�����ڲο���� - ��Ϊ��С�ĳ������ - 2
		{
			TreeNode* pTemp = pRoot;
			while (pTemp->pChild)
			{
				pTemp = pTemp->pChild;
			}
			//�ҵ�����С������
			pTemp->pChild = tINode;
			tINode->pParent = pTemp;
		}
	}
	else	//�������� - 1
	{
		pRoot = tINode;
	}
}


template<typename T>
void CMyTree_List<T>::deleteNode(T const& findData)
{
	TreeNode* pFind = _find(pRoot, findData);
	//����Ǹ��ڵ㣬ֱ�ӵ���clear
	if (pFind == pRoot)
	{
		clear();
		return;
	}
	if (pFind == nullptr)	//�Ҳ������
	{
		//cout << "û��������" << endl;
		return;
	}
	else
	{
		//���ҵ���㣬��ɾ����������
		_clear(pFind->pChild);
		//��ɾ�������� �������������
		//��ɾ���ڵ��ǳ���
		if (pFind == pFind->pParent->pChild)
		{
			//���ӻ���
			pFind->pParent->pChild = pFind->pBrother;
		}
		//��ɾ���ڵ㲻�ǳ���
		else
		{
			//�ȶ�λ����
			TreeNode* pTemp = pFind->pParent->pChild;
			//���ҵ� ��ǰ����ǰһ���ֵܽڵ�
			while (pTemp->pBrother != pFind)
			{
				pTemp = pTemp->pBrother;
			}
			//ͨ��ǰһ�����ָ��ָ����һ����ɾ����ǰ���
			pTemp->pBrother = pTemp->pBrother->pBrother;
		}
		delete pFind;//��ʱָ��������ùܸ���
	}
}




//���νṹ - ˳����
template<typename T>
class CMyTree_Arr {
private:
	T* pBuff;//��̬���飬���ڵ��±�Ϊ0
	size_t len;//����
	size_t Maxsize;//����
public:
	//���к�����Ա
	CMyTree_Arr();
	CMyTree_Arr(int n, T val = 0);
	CMyTree_Arr(CMyTree_Arr const& other); //�������캯���������
	~CMyTree_Arr();//�����ȫ������
	CMyTree_Arr& operator=(CMyTree_Arr const& other); //�ж�̬�ڴ棬���ظ�ֵ�����
public:
	void clear();//�����ȫ������
	void initTree(T arr[], size_t length);//��ʼ��һ����
public:
	bool find(T const& findVal)const;//���Һ���
	void AppendNode(T const& data);//β���������
	void PrintTree(); //������ 3�ַ�ʽ
	bool DeleteNode(int index, T& elem);//ɾ���ڵ�,����elem����ɾ��Ԫ��
public:
	bool isEmpty() const { return len == 0; }
	T getParentVal(int index)const;//��ȡ���ڵ�
	T GetLeftVal(int index) const; //��ȡ������
	T GetRightVal(int index) const;//��ȡ������
private:
	int _find(T const& findVal)const;//�����ò���
	void _PrintTree(int ArrIndex);//�ݹ���� - �±�
};

template<typename T>
CMyTree_Arr<T>::CMyTree_Arr()
{
	//����
	this->pBuff = nullptr;
	len = Maxsize = 0;
}

template<typename T>
CMyTree_Arr<T>::CMyTree_Arr(int n, T val)
{
	if (n < 0)
		throw "error";
	else if (n == 0)
	{
		this->pBuff = nullptr;
		len = Maxsize = 0;
	}
	else
	{
		pBuff = new T[n];
		len = Maxsize = n;
		memset(pBuff, val, sizeof(T) * len);
		//for (int i = 0; i < len; ++i)
		//	pBuff[i] = val;
	}
}

template<typename T>
CMyTree_Arr<T>::CMyTree_Arr(CMyTree_Arr const& other)
{
	*this = other;	//ͨ�����ظ�ֵ=�����,�򻯴���
}

template<typename T>
CMyTree_Arr<T>& CMyTree_Arr<T>::operator=(CMyTree_Arr const& other)//���ظ�ֵ�����
{
	clear();//���ԭ�ڴ�
	maxSize = other.maxSize;
	len = other.len;
	pBuff = nullptr;
	if (maxSize > 0)
	{
		pBuff = new T[maxSize];
		memset(pBuff, 0, sizeof(T) * maxSize);
		for (size_t i = 0; i < len; ++i)
		{
			pBuff[i] = other.pBuff[i];
		}
	}
}

template<typename T>
CMyTree_Arr<T>::~CMyTree_Arr()
{
	clear();
}

template<typename T>
void CMyTree_Arr<T>::clear()
{
	if (pBuff)//!=nullptr
	{
		delete[] pBuff;
	}
	pBuff = nullptr;
	len = Maxsize = 0;
}

template<typename T>
void CMyTree_Arr<T>::initTree(T arr[], size_t length)
{
	//����Ҫ�������
	clear();
	if (length > 0)
	{
		Maxsize = len = length;
		pBuff = new T[Maxsize];
		for (int i = 0; i < len; ++i)
			pBuff[i] = arr[i];
	}
}

template<typename T>
bool CMyTree_Arr<T>::find(T const& findVal)const //����
{
	return _find(findVal) != -1;
}

template<typename T>
int CMyTree_Arr<T>::_find(T const& findVal)const
{
	//���Ĳ�α��� - ����ĵ�������
	for (int i = 0; i < len; i++)
	{
		if (pBuff[i] == findVal)
			return i;
	}
	//�Ҳ����ͷ��ز����ڵ��±�
	return -1;
}

template<typename T>
void CMyTree_Arr<T>::AppendNode(T const& data)
{
	//�����β�� - ��Ҫ���ǵ�����
	if (len >= Maxsize)
	{
		//�뱶���ݷ�
		Maxsize += (Maxsize >> 1) > 1 ? (Maxsize >> 1) : 1;
		T* pTemp = new T[Maxsize];
		for (int i = 0; i < len; ++i)
			pTemp[i] = pBuff[i];
		if (pBuff)
			delete[] pBuff;
		pBuff = pTemp;//pBuffָ�����ڴ�ռ�
	}
	//���ݲ���
	pBuff[len++] = data;
}

template<typename T>
bool CMyTree_Arr<T>::DeleteNode(int index, T& elem)	//ɾ���ڵ�,����elem����Ԫ��
{
	if (index < 0 || index >= len)
		return false;
	elem = pBuff[index];
	pBuff[index] = pBuff[len - 1];//�ƶ����һ��Ҷ�ӽڵ㣬�ɾ��λ��
	len--; //���ȼ�һ
	return true;
}

template<typename T>
T CMyTree_Arr<T>::getParentVal(int index) const  //����index�ĸ��ڵ�����
{
	//if (len< =1) ����ֻ�� ���ڵ�û�и��ڵ�
	if (index > 0 && index < len && len > 1) //���ڵ��±�Ϊ0
	{
		return pBuff[(index - 1) >> 1];
	}
	else
		throw "error";
}

template<typename T>
T CMyTree_Arr<T>::GetLeftVal(int index) const  //����index������������
{
	if (2 * index + 1 >= len || index < 0)
		throw "out_range";
	return pBuff[2 * index + 1];
}

template<typename T>
T CMyTree_Arr<T>::GetRightVal(int index) const//��ȡ������
{
	if (2 * index + 2 >= len || index < 0)
		throw "out_range";
	return pBuff[2 * index + 2];

}

template<typename T>
void CMyTree_Arr<T>::PrintTree()
{
	_PrintTree(0);//�Ӹ��ڵ㿪ʼ
}
template<typename T>
void CMyTree_Arr<T>::_PrintTree(int ArrIndex)
{
	if (ArrIndex<(int)len && ArrIndex > -1)//����
	{
		//�������: ��- ������- ������
		cout << pBuff[ArrIndex] << '\t';
		_PrintTree(ArrIndex * 2 + 1);//�ݹ�������
		//��������������� -�� -������
		//cout << pBuff[ArrIndex] << '\t';
		_PrintTree(ArrIndex * 2 + 2);//�ݹ�������
		//���������������- ������- ��
	}
}



//�ѽṹ - ���� - ��ģ��
template<typename T>
class CMyHeap {
public:
	//���� - ˽��
	T* pBuff;//������
	size_t len;//������
	size_t MaxSize;//����

	//��Ϊ - ����
public:
	CMyHeap();
	~CMyHeap();
public:
	void clear();
	void AppEndNode(T const& srcData);//�������
	void DeleteNode();//ɾ������
	void initHeap(T arr[], size_t srcLen);//��ʼ��
	T GetTop() { return pBuff[0]; }//�򵥰�

};
template<typename T>
CMyHeap<T>::CMyHeap()
{
	pBuff = nullptr;
	len = MaxSize = 0;
}
template<typename T>
CMyHeap<T>::~CMyHeap()
{
	clear();
}
template<typename T>
void CMyHeap<T>::clear()
{
	if (pBuff)
		delete[] pBuff;
	pBuff = nullptr;
	len = MaxSize = 0;
}

template<typename T>
void CMyHeap<T>::AppEndNode(T const& srcData)
{
	//���� - ���ȿ�������
	if (len >= MaxSize)
	{
		MaxSize += (MaxSize >> 1) > 1 ? (MaxSize >> 1) : 1;
		T* pTemp = new T[MaxSize];
		for (size_t i = 0; i < len; i++)
			pTemp[i] = pBuff[i];
		if (pBuff)
			delete[] pBuff;
		pBuff = pTemp;
	}
	//������� - ���� - ���������һ��
	pBuff[len++] = srcData;
	//����ֵ �����±�
	int tempIndex = len - 1;//��ǰ�±� - ����
	int tempData = pBuff[tempIndex];//��ǰֵ
	//��ʼ����
	//�������� - �������Լ���ĸ��ڵ� - �����ڵ���
	while (tempIndex)//tempIndex == 0 - �����ڵ���
	{
		//��ȡ���ڵ���±�
		int ParentIndex = (tempIndex - 1) >> 1;
		//�Ƚ� - ��������
		if (pBuff[ParentIndex] < tempData)
		{
			pBuff[tempIndex] = pBuff[ParentIndex];//�� = ��
		}
		else
		{
			//�����˱��Լ����
			break;
		}
		//��������
		tempIndex = ParentIndex;
	}
	//��ѭ���ˣ����������һ�� - ����Ҫ�����롱
	pBuff[tempIndex] = tempData;
}

//ɾ������1��ÿ��ֻ��ɾ�����ڵ㣻2�������һ���ڵ��ƶ������ڵ㣻3���������ڵ��λ�ã�������� ��������ѵ�����
template<typename T>
void CMyHeap<T>::DeleteNode()
{
	if (len == 0)//�ն�
		return;
	//��������������ϣ�β��㸲�Ǹ��ڵ�
	if (len > 1)
		pBuff[0] = pBuff[len - 1];
	len--;//ɾ�������ȼ�һ
	//���µıȽϹ��� - ���������һ��
	bool isLeft;//����
	int tempIndex = 0;//������ڵ���±�
	T tempData = pBuff[0];//���浱ǰ���ڵ��ֵ

	//��ʼ����
	//�������� - ��Ҷ�ڵ��� - tempData������
	while (true)
	{
		//��ȡ�����������±�
		int left = tempIndex * 2 + 1;
		int right = tempIndex * 2 + 2;
		//���������Խ���� ˵����ǰ�ڵ���Ҷ�ڵ�
		if (left >= len)
			break;//��Ҷ�ڵ���
		//�޸Ŀ��أ��ͽϴ��������ȣ� - Ĭ�����
		isLeft = true;
		if (right<len && pBuff[right]>pBuff[left])//�������ϴ�
		{
			isLeft = false;//��������
		}
		//ȷ�����صķ���
		if (isLeft)
		{
			//���������Ƚϣ���������ֵ���ڻ������������ֵ������û����������
			if (tempData < pBuff[left])
			{
				//���ڵ��ֵС����������ֵ
				pBuff[tempIndex] = pBuff[left];//��������ֵ�ϸ�
				tempIndex = left;
			}
			else//tempData������
				break;
		}
		else
		{
			//���������Ƚ�
			if (tempData < pBuff[right])
			{
				//�Ȳ���������
				pBuff[tempIndex] = pBuff[right];//�����ϸ�
				tempIndex = right;
			}
			else//tempData������
				break;
		}
	}
	//ѭ������ - �������
	pBuff[tempIndex] = tempData;
}

template<typename T>
void CMyHeap<T>::initHeap(T arr[], size_t srcLen)
{
	//�������
	clear();
	if (srcLen == 0)
		return;
	//һ���Լ������е�Ԫ��
	len = MaxSize = srcLen;
	pBuff = new T[MaxSize];
	for (int i = 0; i < len; i++)
		pBuff[i] = arr[i];

	//�����һ��Ҷ�ӽ��ĸ��ڵ㿪ʼ
	for (int i = (len - 1 - 1) >> 1; i >= 0; i--)
	{
		//�ϸ�����
		bool isLeft;//����
		int tempIndex = i;
		T tempData = pBuff[tempIndex];

		//��ʼ����
		//�������� - ��Ҷ�ڵ��� - tempData������
		while (true)
		{
			//��ȡ�����������±�
			int left = tempIndex * 2 + 1;
			int right = tempIndex * 2 + 2;
			//���������Խ���� ˵������Ҷ�ڵ�
			if (left >= len)
				break;//��Ҷ�ڵ���
			//�޸Ŀ��� - Ĭ�����
			isLeft = true;
			if (right<len && pBuff[right]>pBuff[left])
			{
				isLeft = false;
			}
			//ȷ�����صķ���
			if (isLeft)
			{
				//���������Ƚ�
				if (tempData < pBuff[left])
				{
					//�Ȳ���������
					pBuff[tempIndex] = pBuff[left];//pBuff[low]�����ϸ�
					tempIndex = left;
				}
				else//tempData������
					break;
			}
			else
			{
				//���������Ƚ�
				if (tempData < pBuff[right])
				{
					//�Ȳ���������
					pBuff[tempIndex] = pBuff[right];//pBuff[high]�����ϸ�
					tempIndex = right;
				}
				else//tempData������
					break;
			}
		}
		//ѭ������ - �������
		pBuff[tempIndex] = tempData;
	}
}