#pragma once

//交换函数,嵌套中的函数模板，要声明在调用函数之前
template <class T>
void Swap(T& a, T& b);

//1.冒泡排序
template <class T>
void Bubble_Sort(T arr[], int len, bool reverse = false);  //声明默认false为升序,定义时不要默认值,避免重复定义


//2.选择排序
template <typename T>
void Select_Sort(T* arr, int len, bool (*pFun)(T, T));

//3.插入排序
template <typename T>
void Insert_Sort(T* arr, int len, bool reverse = false); //默认升序

//4.希尔排序是插入排序优化
template <typename T>
void Shell_Sort(T* arr, int size, bool reverse = false); //默认升序

//5.快速排序_1
template <typename T>
void Quick_Sort(T* arr, int begin, int end, bool reverse = false); //默认升序

//快速排序_1递归分区函数
template  <typename T>
int partition(T arr[], int begin, int end, bool reverse); //模板声明,避免调用分区函数时未定义


//5.快速排序_2
template <typename T>
void Quick_Sort_2(T* arr, int size, bool reverse = false);

//快速排序_2递归分区函数
template  <typename T>
void _Quick_Sort_2(T arr[], int begin, int end, bool reverse);


//6.基数排序(只适用非负整数,不需要模板化)
void Radix_Sort(int arr[], int size, bool reverse = false); //默认升序


//7.归并排序入口函数
template  <typename T>
void Merge_Sort(T arr[], int size, bool reverse = false);

//递归拆分函数
template  <typename T>
void _Merge(T arr[], int left, int right, bool reverse);

//2路归并排序，将有序序列 arr[low,mid] 和 arr[mid+1,high]归并为一个新的有序序列
template  <typename T>
void _Merge_In_Arr(T arr[], int left, int mid, int right, bool reverse);


//二分法查找,返回目标值下标，区间[low,high]
template  <typename T>
T Binary_Search(T arr[], int len, T target);//(适用有序,无重复元素数组)


//动态数组类模板
template <class T> class MyArr;

//循环队列类模板
template <class T> class MyQueue;

//树形结构 - 容器 - 泛型编程 - 模板类
template<typename T> class CMyTree_List;

//树形结构 - 顺序树
template<typename T> class CMyTree_Arr;

//堆结构 - 容器 - 类模板
template<typename T> class CMyHeap;


//交换函数
template <class T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}


//1.冒泡排序
template <class T>
void Bubble_Sort(T arr[], int len, bool reverse)  //默认false为升序排列
{
	T tempVal;//临时变量在循环外定义，避免重复定义变量操作
	bool flag;
	for (int i = 1; i < len; ++i) //i表示第i趟排序，每趟选出最大值放在序列最后
	{
		flag = false;//本趟冒泡排序是否发生交换的标记
		for (int j = 0; j < len - i; ++j)
		{
			if (arr[j] > arr[j + 1] && reverse == false) //从小到大
			{
				Swap(arr[j], arr[j + 1]);//交换
				flag = true;
			}

			if (arr[j] < arr[j + 1] && reverse == true)  //降序
			{
				Swap(arr[j], arr[j + 1]);
				flag = true;
			}
		}
		if (flag == false)//本趟遍历不发生交换，说明表已经有序
			return;
	}
}



//2.选择排序
template <typename T>
void Select_Sort(T* arr, int len, bool (*pFun)(T, T))
{
	T temp(0), min(0);
	for (int i = 0; i < len - 1; ++i)//i表示第i趟排序，需要n-2趟
	{
		min = i;//假设i即为当前最小值的下标
		for (int j = i + 1; j < len; ++j)//选择出最小值的下标，用min保存
		{
			//if (arr[min] > arr[j])
			//	min = j;
			if (pFun(arr[min], arr[j]))
			{
				min = j;
			}
		}
		if (min != i)//若min发生改变
		{
			Swap(arr[i], arr[min]);//更新最小值下标元素的值
		}
	}
}

template <typename T>
bool isMax(T a, T b)  //升序
{
	return a > b;
}

template <typename T>
bool isMin(T a, T b)  //降序
{
	return a < b;
}

//3.插入排序
template <typename T>
void Insert_Sort(T* arr, int len, bool reverse) //reverse = false,默认升序
{
	T temp(0);
	int j(0);
	//外层循环 插入数据量
	for (int i = 1; i < len; ++i)//下标i=0元素视为有序，插入数值的下标从1开始
	{
		if (reverse == false)//从小到大
		{
			if (arr[i] < arr[i - 1])//当前驱元素 大于 当前元素时，才需要排序
			{
				temp = arr[i];//保存待插入的无序数据
				//插入数据小于相邻有序元素，需要前移，直到大于有序元素时插入（保持插入前后均有序）
				for (j = i - 1; j >= 0 && temp < arr[j]; j -= 1)//j为有序部分的下标，j在i前
				{
					arr[j + 1] = arr[j];//有序数据后移，空出位置
				}
			}
		}
		else //reverse == true 从大到小
		{
			if (arr[i] > arr[i - 1])//当前驱元素 小于 当前元素时，才需要排序
			{
				temp = arr[i];//保存待插入的无序数据
				for (j = i - 1; j >= 0 && temp > arr[j]; j -= 1)
				{
					arr[j + 1] = arr[j];
				}
			}
		}
		arr[j + 1] = temp;//j的后一项才是待插入元素的下标
	}
}

//4.希尔排序是插入排序优化
template <typename T>
void Shell_Sort(T* arr, int size, bool reverse)
{
	T temp;
	int j, i;
	//增量分组 ，例如分组[1 2 3 4 1 2 3 4],标号相同的组，对应下标相差值 = 分组量4
	int jump = size >> 1;//分组量也为步长,直接插入排序中步长为1
	while (jump > 0)
	{
		//外层循环 插入数据量
		for (i = jump; i < size; ++i)//循环次数随分组量的减少而增多
		{
			temp = arr[i];//保存待插入的无序数据
			if (reverse == false)//从小到大
			{
				//j为有序部分的下标，j在i前的相邻步长位置
				//若temp小于有序元素，继续前移，直到大于有序元素arr[j]。插入过程保持有序
				for (j = i - jump; j >= 0 && temp < arr[j]; j -= jump)
				{
					arr[j + jump] = arr[j];//有序数据后移，空出位置
				}
			}
			else //reverse == true 从大到小
			{
				for (j = i - jump; j >= 0 && temp > arr[j]; j -= jump)
				{
					arr[j + jump] = arr[j];
				}
			}
			arr[j + jump] = temp;//j的后一项才是待插入元素的下标
		}
		jump >>= 1;//每次排序完，分组减半,直到最后jump=1(每组只有1个元素)
	}
}

//5.快速排序_1
template <typename T>
void Quick_Sort(T* arr, int begin, int end, bool reverse)  //快速排序（递归）,默认升序
{
	if (begin < end)//递归跳出条件
	{
		int pivot = partition(arr, begin, end, reverse); //划分区间的基准下标
		Quick_Sort(arr, begin, pivot-1, reverse);//划分左表
		Quick_Sort(arr, pivot + 1, end, reverse);//划分右表
	}
}

//指针交换法：左边大于基准的元素和右边小于基准的元素交换
template  <typename T>
int partition(T arr[], int low, int high, bool reverse)  //分区函数
{
	T pivot = arr[low];//先设当前表中首元素为基准，开始进行划分
	//low左边的元素 < 基准pivot , high右边的元素都要 >= pivot
	while (low < high) //循环跳出条件 low >= high
	{	
		if (reverse == false)//升序,默认
		{
			while (arr[high] >= pivot && low < high)
				--high;
			arr[low] = arr[high]; //把比基准小的元素 移动到左端
			while (arr[low] <= pivot && low < high)
				++low;
			arr[high] = arr[low]; //把比基准大的元素 移动到右端
		}

		if (reverse == true)//降序
		{
			while (arr[high] <= pivot && low < high)
				--high;
			arr[low] = arr[high]; //把比基准大的元素 移动到左端

			while (arr[low] >= pivot && low < high)
				++low;
			arr[high] = arr[low]; //把比基准小的元素 移动到右端
		}
	}
	arr[low] = low;//基准元素存放到最终位置
	return low;	//返回基准最终下标
}


//5.快速排序_2
template <typename T>
void Quick_Sort_2(T* arr, int size, bool reverse)  //快速排序（递归）,默认升序
{
	_Quick_Sort_2(arr, 0, size - 1, reverse);
}

template  <typename T>
void _Quick_Sort_2(T arr[], int begin, int end, bool reverse)  //分区函数
{
	T pivot = arr[begin]; //初始设arr[low]为标杆
	//搜索区间为 [low + 1 , high] 
	int left = begin + 1; //小游标
	int right = end;	  //大游标

	//递归结束条件 - 区间至多只有1个元素
	if (begin >= end)
		return;
	//正式排序 - 划分左右区间
	while (left <= right) //大前提
	{
		if (reverse == false) //升序
		{
			while (arr[right] >= pivot && left <= right)
			{
				right--;//right过滤大于标杆的值；否则，停住
			}
			while (arr[left] <= pivot && left <= right)
			{
				left++;//left过滤小于标杆的值；否则，停住
			}
		}
		else//降序
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
		//left和right都停住
		if (left < right)//区间还没搜索完，则相互交换
		{
			Swap(arr[left], arr[right]);
			left++;//交换完后，满足过滤条件，游标继续移动一次
			right--;
		}
	}
	//当left > high ，结束循环，此时right指向的值小于标杆，left指向值大于标杆
	//让 arr[high]与标杆交换，才能使得 序列保持[左边 < 标杆 < 右边]的格式
	arr[begin] = arr[right];
	arr[right] = pivot;
	//最后一步 递归左右区间
	_Quick_Sort_2(arr, begin, right - 1, reverse);
	_Quick_Sort_2(arr, right + 1, end, reverse);
}


//7.归并排序入口函数
template  <typename T>
void Merge_Sort(T arr[], int size, bool reverse)
{
	_Merge(arr, 0, size - 1, reverse);
}

template  <typename T>
void _Merge(T arr[], int left, int right, bool reverse)//递归拆分函数
{
	//递归结束条件
	if (left >= right)//至多一个元素
		return;
	int mid = left + ((right - left) >> 1);//折半查找，( low + high )/2 可能会有数值溢出

	//递归左边
	_Merge(arr, left, mid, reverse);
	//递归右边
	_Merge(arr, mid + 1, right, reverse);

	//二路归并
	_Merge_In_Arr(arr, left, mid, right, reverse);
}

//将有序子序列 arr[low,mid] 和 arr[mid+1,high]归并为新的有序序列
template  <typename T>
void _Merge_In_Arr(T arr[], int left, int mid, int right, bool reverse)//合并函数
{
	//准备 辅助数组 三个记录下标索引的变量
	int length = right - left + 1;//元素量
	T* pData = new T[length];
	//初始化
	memset(pData, 0, sizeof(int) * length);

	//三个下标索引变量
	int low, hig, index = 0;//左边 右边 辅助数组
	low = left;//左边
	hig = mid + 1;//右边
	if (reverse == false) //升序
	{
		//左边区间（left, mid)	，	右边（mid + 1, high)
		while (low <= mid && hig <= right)//大前提
		{
			//左区间存在数据 且 arr[low]较小，先归并
			while (low <= mid && arr[low] <= arr[hig])
			{
				pData[index++] = arr[low++];
			}
			//右区间存在数据 且 arr[hig]较小，先归并
			while (hig <= right && arr[low] > arr[hig])
			{
				pData[index++] = arr[hig++];
			}
		}
	}
	else //降序
	{
		//左边区间（left, mid)	，	右边（mid + 1, high)
		while (low <= mid && hig <= right)//大前提
		{
			//右区间存在数据 且 arr[hig]较大，先归并
			while (hig <= right && arr[hig] >= arr[low])
			{
				pData[index++] = arr[hig++];
			}
			//左区间存在数据 且 arr[low]较大，先归并
			while (low <= mid && arr[low] > arr[hig])
			{
				pData[index++] = arr[low++];
			}
		}
	}
	//循环结束 至少有一个区间为空， 剩下的数据直接拷贝内存
	if (low <= mid)//左边有剩
	{
		//内存移动函数 参数： 目的地的地址  来源地的地址 字节数
		memmove(&pData[index], &arr[low], sizeof(int) * (mid - low + 1));
	}
	if (hig <= right)//右边有剩
	{
		memmove(&pData[index], &arr[hig], sizeof(int) * (right - hig + 1));
	}

	//最后一步，辅助数组完成数列排序的记录 需要拷贝回原数组
	memmove(&arr[left], pData, sizeof(int) * length);
	delete[] pData;
}



//6.基数排序(适用非负整数)
void Radix_Sort(int arr[], int size, bool reverse)
{
	if (size < 2)//元素数量小于2，不用排序
		return;

	//1、准备桶子
	//int tempArr[size][10] = {};
	int** tempArr = new int* [size];
	for (int x = 0; x < size; ++x)
	{
		tempArr[x] = new int[10];
	}
	int i, j, num, index;
	//2.1、桶子初始化
	for (i = 0; i < size; i++) //数据量决定行数
	{
		for (j = 0; j < 10; j++) //0~9
		{
			//初始化的值一定是不会在数据中出现的值
			tempArr[i][j] = -1;
		}
	}
	//2、循环
	for (int n = 1; n <= 100; n *= 10) //n = 1，10，100 分别表示个 十 百位
	{
		//2.2、数据入桶
		for (i = 0; i < size; ++i)
		{
			index = arr[i] / n % 10;//桶子编号,从最低位(个位)开始，再次低位...最后到最高位
			tempArr[i][index] = arr[i];
		}

		//2.3、数据出桶 - 竖着遍历
		num = 0;//一定要在循环内部初始化
		if (reverse == false)//升序，数据出桶从左上开始，逐列自上而下遍历，直到右下
		{
			for (i = 0; i < 10; ++i)//列
			{
				for (j = 0; j < size; ++j)//行
				{
					if (tempArr[j][i] != -1)
					{
						arr[num++] = tempArr[j][i]; //数据出桶后
						tempArr[j][i] = -1;	//重置为-1，就不必再初始化一遍所有桶子
					}
					//不需要 else break
				}
			}
		}
		else	//降序，数据出桶从右下开始，逐列自下而上遍历，直到左上
		{
			for (i = 9; i >= 0; --i)//列
			{
				for (j = size - 1; j >=0; --j)//行
				{
					if (tempArr[j][i] != -1)
					{
						arr[num++] = tempArr[j][i]; //数据出桶后
						tempArr[j][i] = -1;	//重置为-1，就不必再初始化一遍所有桶子
					}
					//不需要 else break
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



//(升序，无重复元素序列)二分查找,返回目标值下标 [low,high]
template  <typename T>
T Binary_Search(T arr[], int len, T target)
{
	int left = 0;
	int right = len - 1;//右区间端点能够取到
	int mid;//中位数下标
	while (left <= right)// 当left==right，区间[low, high]依然有效，所以用 <=
	{
		//第一步 确定中位数
		mid = left + ((right - left) >> 1);//等同于(low + high)/2
		//第二步 和目标值比较,不是中位数,搜索区间缩小
		if (target < arr[mid])//target 在左区间
		{
			right = mid - 1;//区间缩小为[low, middle - 1]
		}
		else if (target > arr[mid])// target 在右区间
		{
			left = mid + 1; //[middle + 1, high]
		}
		else //target == arr[mid],找到目标值，直接返回下标
		{
			return mid;
		}
	}
	return -1;// 未找到目标值
}


//动态数组类模板
template <class T>
class MyArr				//即STL中的vector
{
	T* pBuff;			//动态数组的首地址
	size_t	maxSize;	//动态数组的最大的长度
	size_t	len;		//当前数组中的元素个数
public:
	MyArr();
	MyArr(int length);     //创建指定大小动态数组
	MyArr(MyArr const& other); //有堆内存，重写拷贝构造函数（深拷贝）
	~MyArr();
public:
	MyArr& operator=(MyArr const& srcArr);//有堆内存，重载赋值运算符（比拷贝构造多了清空内存）
public:
	void clear();							//释放动态内存
	void appendVal(T const& val);			//尾部添加数据
	void insert(size_t index, T const& val);//按下标插入元素
	void earse(size_t index);				//按下标删除元素
	void addCapacity();						//扩容函数
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
	*this = other;	//通过重载赋值=运算符,简化代码
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
	clear();//清空原内存
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
void MyArr<T>::appendVal(T const& val) //尾部插入元素
{
	addCapacity();
	if (len >= maxSize)//表示当前空间元素放满,自动扩容
	{
		addCapacity();
	}
	pBuff[len++] = val;
}

template <class T>
void MyArr<T>::insert(size_t index, T const& val)
{
	if (len >= maxSize)//表示当前空间元素放满
	{
		addCapacity();
	}
	for (size_t i = len - 1; i >= index; --i)//从后往前，[index,len-1]元素依次后移到[index+1,len]
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
	for (size_t i = index + 1; i < len; ++i)//从前往后，[index+1,len-1]元素依次前移到[index,len-2]
	{
		pBuff[i - 1] = pBuff[i];
	}
	len--;
}


//循环队列
template <typename T>
class MyQueue {
	T* que_arr;		 //动态数组,存储MaxSize-1个元素, 空一个位置用来判断队满
	size_t front, rear; //队头下标,队尾下标(rear指向最后一个元素的下一位置，不指向元素)
	size_t size, maxSize;
public:
	MyQueue();
	MyQueue(size_t); //自定义大小队列
	MyQueue(MyQueue const& other);//有堆内存，重写拷贝构造函数（深拷贝）
	~MyQueue();
public:
	MyQueue& operator = (MyQueue const& other); //有堆内存，重载赋值运算符（比拷贝构造多了清空内存操作）
public:
	void clear();			//释放动态内存
	void addCapacity();
	bool enQueue(T const&); //入队
	bool deQueue();			//出队
public:
	bool getFront(T&) const;
	bool getRear(T&) const;
	bool isEmpty()const { return rear == front; }//队空，相等即可不需要为0
	bool isFull()const { return (rear + 1) % maxSize == front; }//队满：队头指针在队尾的下一位置
	size_t getSize() const { return size; }
	T const* getQue_arr() const { return que_arr; }  //获取队列内部的数组指针
};

template <typename T>
MyQueue<T>::MyQueue()	//默认构造函数
{
	que_arr = nullptr;
	front = rear = 0;   //空队列，rear与front相等
	maxSize = size = 0;
}

template <typename T>
MyQueue<T>::MyQueue(size_t Custom_size) //普通构造函数
{
	front = rear = 0;
	size = 0;
	maxSize = Custom_size;		//自定义大小
	que_arr = new T[maxSize];
}

template <typename T>
MyQueue<T>::MyQueue(MyQueue const& other)  //拷贝构造函数
{
	*this = other;//通过重载赋值=运算符,简化代码
}

template <typename T>
MyQueue<T>& MyQueue<T>::operator = (MyQueue const& other)  //赋值运算符重载
{
	clear();//在赋值之前,不确定自己的堆内存有没有数据,就清一次内存
	front = other.front;
	rear = other.rear;
	size = other.size;
	maxSize = other.maxSize;
	que_arr = nullptr;
	if (maxSize > 0)
	{
		que_arr = new T[maxSize];
		memset(que_arr, 0, sizeof(T) * maxSize);
		for (size_t i = 0; i < len; ++i)//拷贝other（que_arr）中的数据
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
	for (size_t i = 0, j = front; i < size; ++i) //元素复制,注意循环队列元素下标
		tempQueArr[i] = que_arr[(i + j) % maxSize];
	if (que_arr) delete[] que_arr;
	que_arr = tempQueArr;
	front = 0;	//扩容后,队列变量的变化
	rear = size;
}

template <typename T>
bool MyQueue<T>::enQueue(T const& elem) //入队
{
	if (isFull())//（循环）队列已满，扩容
	{
		addCapacity();
	}
	que_arr[rear] = elem;  //在队尾，元素入队
	rear = (rear + 1) % maxSize; //下标可循环
	++size;
	return true;
}

template <typename T>
bool MyQueue<T>::deQueue() //队头元素出队
{
	if (isEmpty())	//队列为空，没有元素
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
	elem = que_arr[front];  //返回队头元素
	return true;
}

template <typename T>
bool MyQueue<T>::getRear(T& elem) const
{
	if (isEmpty())
	{
		return false;
	}
	elem = que_arr[rear];  //返回队尾元素
	return true;
}

template<typename T>
struct TreeNode {
	//圆球 - 数据域
	T data;
	//3个针 - 结点指针
	TreeNode* pParent;//父结点指针
	TreeNode* pBrother;//兄弟结点指针
	TreeNode* pChild;//子结点指针
};

//树形结构 - 容器 - 泛型编程 - 模板类
template<typename T>
class CMyTree_List {
	//内置类型 - 树结点类型  ;类外使用需要加上 CMyTree_List<T>:: +   (例 TreeNode* ...)
	TreeNode* pRoot;//根节点
public:
	//成员函数 - 构造析构 增删查改 - 公有
	CMyTree_List();
	~CMyTree_List();
public:
	void clear();//清除函数（可以单独调用，也可以给析构调用）
	bool find(T const& findData);//查找
	//插入 3个参数 ： 插入数据 参考坐标 插入方向-兄弟/儿子
	void insert(T const& insertData, T const& findData, bool isChild);
	void deleteNode(T const& findData);
private:
	//私有接口 - 开发者使用的函数
	void _clear(TreeNode<T> *& root);//清除
	//因为涉及递归，内联失败, 定义可以在写在类内
	TreeNode<T>* _find(TreeNode<T>* root, T const& findData);
};

template<typename T>
CMyTree_List<T>::CMyTree_List()
{
	pRoot = nullptr;//空树
}

template<typename T>
CMyTree_List<T>::~CMyTree_List()
{
	clear();
}

template<typename T>
void CMyTree_List<T>::clear()
{
	_clear(pRoot);//赶尽杀绝
}

template<typename T>
void CMyTree_List<T>::_clear(TreeNode<T> *& root) //参数为指针的引用，若只传入一级指针（值传递），最后实参的pRoot指向没有被修改，会导致根节点指针是个野指针。
{
	if (root/* != nullptr*/)//满足条件进行递归，否则自动结束
	{
		//先递归兄弟，再递归儿子
		_clear(root->pBrother);
		_clear(root->pChild);
		//递归结束 ， 逆向删除
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
	//结束条件：1、找得到；2、找不到；
	if (root)//2、找不到；
	{
		if (root->data == findData)//1、找得到；
		{
			return root;
		}
		//先递归兄弟
		TreeNode* pTemp = _find(root->pBrother, findData);
		if (pTemp)
			return pTemp;
		else//不在兄弟方向，只可能在儿子方向
			return _find(root->pChild, findData);
	}
	else//找不到，就返回空
		return nullptr;
}


template<typename T>
void CMyTree_List<T>::insert(T const& insertData, T const& findData, bool isChild)
{
	// 要准备一个结点
	TreeNode* tempInsertNode = new TreeNode;
	TreeNode*& tINode = tempInsertNode;//给指针起别名
	tINode->data = insertData;
	tINode->pParent = nullptr;
	tINode->pBrother = nullptr;
	tINode->pChild = nullptr;

	//开始插入
	if (pRoot)	//非空树插入
	{
		TreeNode* pFind = _find(pRoot, findData);	//获取参考结点（插入位置）
		if (pFind)		//存在参考节点（插入位置）
		{
			if (isChild) //待插入节点为孩子节点
			{
				//儿子方向插入
				if (pFind->pChild) //已经有儿子
				{
					//做最小的儿子 - 5
					TreeNode* pTemp = pFind->pChild;
					while (pTemp->pBrother)
					{
						pTemp = pTemp->pBrother;
					}
					//找到了最小的儿子
					pTemp->pBrother = tINode;
					tINode->pParent = pFind;
				}
				else	//没有儿子
				{
					//做长子 - 4
					pFind->pChild = tINode;
					tINode->pParent = pFind;
				}
			}
			else	//待插入节点为兄弟节点
			{
				//兄弟方向插入 - 3
				TreeNode* pTemp = pFind;
				while (pTemp->pBrother)
				{
					pTemp = pTemp->pBrother;
				}
				//找到了最小的兄弟
				pTemp->pBrother = tINode;
				tINode->pParent = pFind->pParent;
			}
		}
		else	//不存在参考结点 - 作为最小的长孙插入 - 2
		{
			TreeNode* pTemp = pRoot;
			while (pTemp->pChild)
			{
				pTemp = pTemp->pChild;
			}
			//找到了最小的孙子
			pTemp->pChild = tINode;
			tINode->pParent = pTemp;
		}
	}
	else	//空树插入 - 1
	{
		pRoot = tINode;
	}
}


template<typename T>
void CMyTree_List<T>::deleteNode(T const& findData)
{
	TreeNode* pFind = _find(pRoot, findData);
	//这个是根节点，直接调用clear
	if (pFind == pRoot)
	{
		clear();
		return;
	}
	if (pFind == nullptr)	//找不到结点
	{
		//cout << "没有这个结点" << endl;
		return;
	}
	else
	{
		//能找到结点，先删除它的子树
		_clear(pFind->pChild);
		//再删除这个结点 ，考虑两个情况
		//被删除节点是长子
		if (pFind == pFind->pParent->pChild)
		{
			//长子换人
			pFind->pParent->pChild = pFind->pBrother;
		}
		//被删除节点不是长子
		else
		{
			//先定位长子
			TreeNode* pTemp = pFind->pParent->pChild;
			//再找到 当前结点的前一个兄弟节点
			while (pTemp->pBrother != pFind)
			{
				pTemp = pTemp->pBrother;
			}
			//通过前一个结点指针指向下一个来删除当前结点
			pTemp->pBrother = pTemp->pBrother->pBrother;
		}
		delete pFind;//临时指针变量不用管赋空
	}
}




//树形结构 - 顺序树
template<typename T>
class CMyTree_Arr {
private:
	T* pBuff;//动态数组，根节点下标为0
	size_t len;//长度
	size_t Maxsize;//容量
public:
	//公有函数成员
	CMyTree_Arr();
	CMyTree_Arr(int n, T val = 0);
	CMyTree_Arr(CMyTree_Arr const& other); //拷贝构造函数（深拷贝）
	~CMyTree_Arr();//清空完全二叉树
	CMyTree_Arr& operator=(CMyTree_Arr const& other); //有动态内存，重载赋值运算符
public:
	void clear();//清空完全二叉树
	void initTree(T arr[], size_t length);//初始化一棵树
public:
	bool find(T const& findVal)const;//查找函数
	void AppendNode(T const& data);//尾部添加数据
	void PrintTree(); //遍历树 3种方式
	bool DeleteNode(int index, T& elem);//删除节点,并用elem返回删除元素
public:
	bool isEmpty() const { return len == 0; }
	T getParentVal(int index)const;//获取父节点
	T GetLeftVal(int index) const; //获取左子树
	T GetRightVal(int index) const;//获取右子树
private:
	int _find(T const& findVal)const;//开发用查找
	void _PrintTree(int ArrIndex);//递归访问 - 下标
};

template<typename T>
CMyTree_Arr<T>::CMyTree_Arr()
{
	//空树
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
	*this = other;	//通过重载赋值=运算符,简化代码
}

template<typename T>
CMyTree_Arr<T>& CMyTree_Arr<T>::operator=(CMyTree_Arr const& other)//重载赋值运算符
{
	clear();//清空原内存
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
	//必须要先做清除
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
bool CMyTree_Arr<T>::find(T const& findVal)const //查找
{
	return _find(findVal) != -1;
}

template<typename T>
int CMyTree_Arr<T>::_find(T const& findVal)const
{
	//树的层次遍历 - 数组的迭代遍历
	for (int i = 0; i < len; i++)
	{
		if (pBuff[i] == findVal)
			return i;
	}
	//找不到就返回不存在的下标
	return -1;
}

template<typename T>
void CMyTree_Arr<T>::AppendNode(T const& data)
{
	//数组的尾插 - 需要考虑到扩容
	if (len >= Maxsize)
	{
		//半倍扩容法
		Maxsize += (Maxsize >> 1) > 1 ? (Maxsize >> 1) : 1;
		T* pTemp = new T[Maxsize];
		for (int i = 0; i < len; ++i)
			pTemp[i] = pBuff[i];
		if (pBuff)
			delete[] pBuff;
		pBuff = pTemp;//pBuff指向新内存空间
	}
	//数据插入
	pBuff[len++] = data;
}

template<typename T>
bool CMyTree_Arr<T>::DeleteNode(int index, T& elem)	//删除节点,并用elem返回元素
{
	if (index < 0 || index >= len)
		return false;
	elem = pBuff[index];
	pBuff[index] = pBuff[len - 1];//移动最后一个叶子节点，填补删除位置
	len--; //长度减一
	return true;
}

template<typename T>
T CMyTree_Arr<T>::getParentVal(int index) const  //返回index的父节点数据
{
	//if (len< =1) 树中只有 根节点没有父节点
	if (index > 0 && index < len && len > 1) //根节点下标为0
	{
		return pBuff[(index - 1) >> 1];
	}
	else
		throw "error";
}

template<typename T>
T CMyTree_Arr<T>::GetLeftVal(int index) const  //返回index的左子树数据
{
	if (2 * index + 1 >= len || index < 0)
		throw "out_range";
	return pBuff[2 * index + 1];
}

template<typename T>
T CMyTree_Arr<T>::GetRightVal(int index) const//获取右子树
{
	if (2 * index + 2 >= len || index < 0)
		throw "out_range";
	return pBuff[2 * index + 2];

}

template<typename T>
void CMyTree_Arr<T>::PrintTree()
{
	_PrintTree(0);//从根节点开始
}
template<typename T>
void CMyTree_Arr<T>::_PrintTree(int ArrIndex)
{
	if (ArrIndex<(int)len && ArrIndex > -1)//区间
	{
		//先序遍历: 根- 左子树- 右子树
		cout << pBuff[ArrIndex] << '\t';
		_PrintTree(ArrIndex * 2 + 1);//递归左子树
		//中序遍历：左子树 -根 -右子树
		//cout << pBuff[ArrIndex] << '\t';
		_PrintTree(ArrIndex * 2 + 2);//递归右子树
		//后序遍历：左子树- 右子树- 根
	}
}



//堆结构 - 容器 - 类模板
template<typename T>
class CMyHeap {
public:
	//数据 - 私有
	T* pBuff;//数据域
	size_t len;//数据量
	size_t MaxSize;//容量

	//行为 - 公有
public:
	CMyHeap();
	~CMyHeap();
public:
	void clear();
	void AppEndNode(T const& srcData);//添加数据
	void DeleteNode();//删除数据
	void initHeap(T arr[], size_t srcLen);//初始化
	T GetTop() { return pBuff[0]; }//简单版

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
	//插入 - 首先考虑扩容
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
	//扩容完成 - 调整 - 插入排序的一趟
	pBuff[len++] = srcData;
	//保存值 保存下标
	int tempIndex = len - 1;//当前下标 - 更新
	int tempData = pBuff[tempIndex];//当前值
	//开始调整
	//结束条件 - 遇到比自己大的父节点 - 到根节点了
	while (tempIndex)//tempIndex == 0 - 到根节点了
	{
		//获取父节点的下标
		int ParentIndex = (tempIndex - 1) >> 1;
		//比较 - 数据下移
		if (pBuff[ParentIndex] < tempData)
		{
			pBuff[tempIndex] = pBuff[ParentIndex];//子 = 父
		}
		else
		{
			//遇到了比自己大的
			break;
		}
		//更新坐标
		tempIndex = ParentIndex;
	}
	//出循环了，插入排序的一趟 - 还需要“插入”
	pBuff[tempIndex] = tempData;
}

//删除规则：1、每次只能删除根节点；2、把最后一个节点移动到根节点；3、调整根节点的位置，让这个堆 重新满足堆的特性
template<typename T>
void CMyHeap<T>::DeleteNode()
{
	if (len == 0)//空堆
		return;
	//存在两个结点以上，尾结点覆盖根节点
	if (len > 1)
		pBuff[0] = pBuff[len - 1];
	len--;//删除，长度减一
	//向下的比较过程 - 插入排序的一趟
	bool isLeft;//开关
	int tempIndex = 0;//保存根节点的下标
	T tempData = pBuff[0];//保存当前根节点的值

	//开始调整
	//结束条件 - 到叶节点了 - tempData比它大
	while (true)
	{
		//获取左右子树的下标
		int left = tempIndex * 2 + 1;
		int right = tempIndex * 2 + 2;
		//如果左子树越界了 说明当前节点是叶节点
		if (left >= len)
			break;//到叶节点了
		//修改开关（和较大的子树相比） - 默认左边
		isLeft = true;
		if (right<len && pBuff[right]>pBuff[left])//右子树较大
		{
			isLeft = false;//开关向右
		}
		//确定开关的方向
		if (isLeft)
		{
			//和左子树比较（左子树的值大于或等于右子树的值，或者没有右子树）
			if (tempData < pBuff[left])
			{
				//根节点的值小于左子树的值
				pBuff[tempIndex] = pBuff[left];//左子树的值上浮
				tempIndex = left;
			}
			else//tempData比它大
				break;
		}
		else
		{
			//和右子树比较
			if (tempData < pBuff[right])
			{
				//比不过右子树
				pBuff[tempIndex] = pBuff[right];//数据上浮
				tempIndex = right;
			}
			else//tempData比它大
				break;
		}
	}
	//循环结束 - 插入操作
	pBuff[tempIndex] = tempData;
}

template<typename T>
void CMyHeap<T>::initHeap(T arr[], size_t srcLen)
{
	//先做清除
	clear();
	if (srcLen == 0)
		return;
	//一次性加入所有的元素
	len = MaxSize = srcLen;
	pBuff = new T[MaxSize];
	for (int i = 0; i < len; i++)
		pBuff[i] = arr[i];

	//从最后一个叶子结点的父节点开始
	for (int i = (len - 1 - 1) >> 1; i >= 0; i--)
	{
		//上浮操作
		bool isLeft;//开关
		int tempIndex = i;
		T tempData = pBuff[tempIndex];

		//开始调整
		//结束条件 - 到叶节点了 - tempData比它大
		while (true)
		{
			//获取左右子树的下标
			int left = tempIndex * 2 + 1;
			int right = tempIndex * 2 + 2;
			//如果左子树越界了 说明这是叶节点
			if (left >= len)
				break;//到叶节点了
			//修改开关 - 默认左边
			isLeft = true;
			if (right<len && pBuff[right]>pBuff[left])
			{
				isLeft = false;
			}
			//确定开关的方向
			if (isLeft)
			{
				//和左子树比较
				if (tempData < pBuff[left])
				{
					//比不过左子树
					pBuff[tempIndex] = pBuff[left];//pBuff[low]数据上浮
					tempIndex = left;
				}
				else//tempData比它大
					break;
			}
			else
			{
				//和右子树比较
				if (tempData < pBuff[right])
				{
					//比不过右子树
					pBuff[tempIndex] = pBuff[right];//pBuff[high]数据上浮
					tempIndex = right;
				}
				else//tempData比它大
					break;
			}
		}
		//循环结束 - 插入操作
		pBuff[tempIndex] = tempData;
	}
}