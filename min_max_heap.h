#pragma once
#include"Double_Ended_Priority_Queue.h"
#include"changeArrayLength.h"
#include<sstream>
#include<iostream>
#include <algorithm>
#include <iomanip>
#include"studentInfo.h"
using namespace std;

#define INF 0x3f3f3f3f
#define parent(n) (n/2)
#define first_child(n) (n*2)
#define second_child(n) ((n*2)+1)

template<class T>
class min_max_heap:Double_Ended_Priority_Queue<T>{
public:
	min_max_heap(int initialCapacity = 10);//默认参数为10
	~min_max_heap() { delete[] heap; }//析构函数
	bool empty() const { return heapSize == 0; }//判断堆是否为空
	int size() const {//返回堆的大小
		return heapSize;
	}
	T* getHeap() const {
		return heap;
	}

	void  initialize(T *theHeap,int theSize);//根据已知数组建堆
	const T& getMax();//得到最大值
	const T& getMin();//得到最小值
	void insert(T&);//插入值
	const T& popMin();//删除最小值
	const T& popMax();//删除最大值
	void output(ostream& out);//输出
public:
	int heapSize;//堆大小
	int arrayLength;//堆的最大值
	T *heap;//堆数组
};

template<class T>
min_max_heap<T>::min_max_heap(int initialCapacity) {//构造函数
	if (initialCapacity < 1) {//初始大小必须大于0
		ostringstream s;
		s << "Error : Initial capacity = " << initialCapacity << " Must be > 0";
		throw s.str();
	}
	arrayLength = initialCapacity + 1;//
	heap = new T[arrayLength];
	heapSize = 0;
}

int is_min_level(int i) {//返回下标为i的数据的层（大层还是小层）
	if ((int)(floor(log(i) / log(2))) % 2) {
		return 0;
	}
	else {
		return 1;
	}
}

template<class T>
int index_min_child_grandchild(min_max_heap<T>* h ,int i) {//找出下标为i的结点的儿子和孙子中最小的值
	int a = first_child(i);
	int b = second_child(i);
	int d = second_child(a);
	int c = first_child(a);
	int f = second_child(b);
	int e = first_child(b);

	int min_idx = -1;
	if (a <= h->heapSize) min_idx = a;
	if (b <= h->heapSize && h->heap[b] < h->heap[min_idx]) min_idx = b;
	if (c <= h->heapSize && h->heap[c] < h->heap[min_idx]) min_idx = c;
	if (d <= h->heapSize && h->heap[d] < h->heap[min_idx]) min_idx = d;
	if (e <= h->heapSize && h->heap[e] < h->heap[min_idx]) min_idx = e;
	if (f <= h->heapSize && h->heap[f] < h->heap[min_idx]) min_idx = f;

	return min_idx;
}

template<class T>
int index_max_child_grandchild(min_max_heap<T>* h, int i) {//找出下标为i的结点的儿子和孙子中最小的值
	int a = first_child(i);
	int b = second_child(i);
	int d = second_child(a);
	int c = first_child(a);
	int f = second_child(b);
	int e = first_child(b);

	int max_idx = -1;
	if (a <= h->heapSize) max_idx = a;
	if (b <= h->heapSize && h->heap[b] > h->heap[max_idx]) max_idx = b;
	if (c <= h->heapSize && h->heap[c] > h->heap[max_idx]) max_idx = c;
	if (d <= h->heapSize && h->heap[d] > h->heap[max_idx]) max_idx = d;
	if (e <= h->heapSize && h->heap[e] > h->heap[max_idx]) max_idx = e;
	if (f <= h->heapSize && h->heap[f] > h->heap[max_idx]) max_idx = f;

	return max_idx;
}

template<class T>
void swap(min_max_heap<T>* h, int i, int m) {//交换堆中下标为i和m的数据
	T temp = h->heap[i];
	h->heap[i] = h->heap[m];
	h->heap[m] = temp;
if(flagPrint)
cout << "     heap[" << i << "]:" << h->heap[m] << "<-->" << "heap[" << m << "]:" << h->heap[i] << endl <<"h:\n"<< *h << endl;
}






int trickleDownCount;//记录下滤的次数
int bubbleUpCount;//记录上滤的次数

/*
小层下滤，先找到自己儿子和孙子中最小的值。
如果该值为儿子，证明自己没有孙子，这时只需比较该最小值与自己，如果该最小值小，则与自己交换位置，下滤结束；否则不变化，下滤结束；
如果该值为孙子，则比较该最小值与自己，如果该最小值大于自己，则证明以该元素为根节点的树的最小值就是该元素，下滤完成；否则如果该最小值小于自己，则进行交换位置，交换后判断自己与父亲结点的大小关系：
	如果父亲节点（大层）小于自己，则交换位置，交换后只有该父亲节点元素位置不正确，所以对父亲节点元素重新进行下滤；
	否则父亲节点大于自己，则对自己重新进行下滤操作。
*/
template<class T>
void TrickleDownMin(min_max_heap<T>* h,int i) {//小层下滤（用于删除）

////////////////////////////////////////cout << "开始进行第" << ++trickleDownCount << "次下滤:" << endl;
	int m = index_min_child_grandchild(h,i);//得到儿子和孙子中最小的值
//cout << "找出元素"<<h->heap[i]<<"(下标为："<<i<<"）的儿子和孙子中最小的值" << endl;
	if (m <= -1) {
//////////////////////////////////cout << "下滤元素" << h->heap[i] << ",下标为：" << i << "没有儿子和孙子,下滤完成" << endl;		
	return;
	}
else
//cout << "最小值为heap[" << m << "]:" << h->heap[m] << endl;
	if (m > second_child(i)) {//如果孙子最小
		if (h->heap[m] < h->heap[i]) {
			swap(h, i, m);
//cout << "最小值为孙子，且小于自己，所以进行交换:heap["<<i<<"]:"<<h->heap[i]<<"与"<< "heap["<<m<<"]:"<<h->heap[m]<< ",交换（即元素下移）后h为:"<<endl;
//cout<< "heap[" << i << "]:" << h->heap[m] << "<-->" << "heap[" << m << "]:" << h->heap[i] <<endl<< *h << endl;
//cout << "现在比较元素heap[" << m << "]:" << h->heap[m] << "与父亲节点heap[" << parent(m) << "]:" <<h->heap[parent(m)]<<":" <<endl;
			if (h->heap[m] > h->heap[parent(m)]) {
				swap(h, m, parent(m));
//cout << "显然," << h->heap[m] << ">" << h->heap[parent(m)] << ",故进行交换,交换后h变为：" << endl 
//cout<< "heap["<<m<<"]:"<< h->heap[parent(m)] << "<-->" << "heap["<<parent(m)<<"]:"<< h->heap[m] <<endl<< *h << endl;
			}
			else {
//cout << "显然，" << h->heap[m] << "<=" << h->heap[parent(m)] << ",故不进行交换" << endl;
			}
////////////////////////////cout << "继续对元素heap[" << m << "]:" << h->heap[m] << "进行下滤" << endl;
		TrickleDownMin(h, m);
		}
		else {
////////////////////////////cout << "孙子值最小，但大于自己，所以不需要进行交换，下滤完成"<<endl;
		}
	}
	else {//如果儿子最小

		if (h->heap[m] < h->heap[i]) {
			swap(h, i, m);
//cout << "没有孙子，最小值为儿子，且小于自己，所以进行交换.:heap[" << i << "]:" << h->heap[i] << "与" << "heap[" << m << "]:" << h->heap[m]  <<",交换（即元素下移）后h为:" << endl ;
			
//cout<< "heap[" << i << "]:" << h->heap[m] << "<-->" << "heap[" << m << "] : " << h->heap[i]<< ":"<< endl << *h << endl<<"下滤完成"<<endl;
		}
		else {
////////////////////////////////////////cout << "不需要进行交换，下滤完成" << endl;//没有孙子，儿子值最小，但大于自己，所以
		}
	}
}

template<class T>
void TrickleDownMax(min_max_heap<T>* h,int i) {//大层下滤（用于删除）
/////////////////////////////////////////cout << "开始进行第" << ++trickleDownCount << "次下滤:" << endl;
	int m = index_max_child_grandchild(h, i);//得到儿子和孙子最大值
	if (m <= -1) {
//////////////////////////////////////////cout << "下滤元素" << h->heap[i] << ",下标为：" << i << "没有儿子和孙子,下滤完成" << endl;
		return;
	}
	if (m > second_child(i)) {//如果孙子最大
		if (h->heap[m] > h->heap[i]) {
			swap(h, i, m);
//cout << "heap[" << i << "]:" << h->heap[m] << "<-->" << "heap[" << m << "]:" << h->heap[i] << endl << *h << endl;
			if (h->heap[m] < h->heap[parent(m)]) {
				swap(h, m, parent(m));
//cout << "heap[" << m << "]:" << h->heap[parent(m)] << "<-->" << "heap[" << parent(m) << "]:" << h->heap[m] << endl << *h << endl;
			}
/////////////////////////////////////////////////cout << "继续对元素heap[" << m << "]:" << h->heap[m] << "进行下滤" << endl;
			TrickleDownMax(h, m);
		}
		else {
/////////////////////////////////////////////////cout << "孙子值最大，但小于自己，所以不需要进行交换，下滤完成" << endl;
		}
	}
	else {//如果儿子最大
		if (h->heap[m] > h->heap[i]) {
			swap(h, i, m);
//cout << "heap[" << i << "]:" << h->heap[m] << "<-->" << "heap[" << m << "] : " << h->heap[i] << ":" << endl << *h << endl << "下滤完成" << endl;
		}
		else {
///////////////////////////////////////////////////cout << "不需要进行交换，下滤完成" << endl;//没有孙子，儿子值最大，但小于自己
		}
	}
}

template<class T>
void trickleDown(min_max_heap<T>* h,int i) {//下滤，用于删除
//cout << "先判断是删除了最小元素，还是最大元素" << endl;
trickleDownCount = 0;
	if (is_min_level(i)) {
//cout << "下滤的元素下标为"<<i<<",显然删除了最小元素" << endl;
		TrickleDownMin(h, i);
	}
	else {
//cout << "下滤的元素下标为" << i << ",显然删除了最大元素" << endl;
		TrickleDownMax(h, i);
	}
		
}

template<class T>
void bubbleup_min(min_max_heap<T>* h, int i) {//小层上滤

	int pp_i = parent(parent(i));
	if (pp_i <= 0) return;
//printf("进行第%d次小层上滤:\n", ++bubbleUpCount);
	if (h->heap[i]<h->heap[pp_i]) {//如果祖父比自己大，则交换
		swap(h, i, pp_i);
		bubbleup_min(h, pp_i);
	}

}

template<class T>
void bubbleup_max(min_max_heap<T>* h, int i) {//大层上滤

	int pp_i = parent(parent(i));
	if (pp_i <= 0) return;
//printf("进行第%d次大层上滤:\n", ++bubbleUpCount);
	if (h->heap[i]>h->heap[pp_i]) {//如果祖父比自己小则交换
		swap(h, i, pp_i);
		bubbleup_max(h, pp_i);
	}

}

template<class T>
void BubbleUp(min_max_heap<T>* h, int i) {//上滤，可用于插入
bubbleUpCount = 0;
	int p_i = parent(i);
	if (p_i <= 0) return;
	if (is_min_level(i)) {//如果是小层，进行父亲节点与自己的值大小比较
		if (h->heap[i] > h->heap[p_i]) {//若父节点小，则交换，并进行大层上滤
			swap(h, i, p_i);
			bubbleup_max(h, p_i);
		}
		else {//如果父节点大则进行小层上滤
			bubbleup_min(h, i);
		}
	}
	else {//否则是大层
		if (h->heap[i] < h->heap[p_i]) {//若父亲节点大于自己，则交换，并进行小层上滤
			swap(h, i, p_i);
			bubbleup_min(h, p_i);
		}
		else {//否则父亲节点小于自己，进行大层交换
			bubbleup_max(h, i);
		}
	}
}



int flagPrint = true;//判断是否打印交换信息

template<class T>
void min_max_heap<T>::initialize(T *theHeap, int theSize) {

	delete[] heap;
	heap = theHeap;
	heapSize = theSize;
	
//flagPrint = true;
if(flagPrint)
cout << *this << endl;
	// heapify
	for (int root = heapSize / 2; root >= 1; root--)
	{
		trickleDown(this, root);
	}

}



template<class T>
void min_max_heap<T>::insert(T& Element) {//插入
if (flagPrint) {
	cout << "插入操作-插入";
	cout << Element;
	cout << ":" << endl;
}
	
	//如果堆满可增加数组的长度，此处扩展为原先的2倍;
	if (heapSize == arrayLength - 1) {
		changeArrayLength(heap, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	int currentNode = ++heapSize;
	heap[currentNode] = Element;
if(flagPrint)
cout <<"h:\n"<<*this<<endl;
	BubbleUp(this, currentNode);
	//while(currentNode!=1&&heap[currentNode/2])
//printf("插入成功\n");
}

template<class T>
const T& min_max_heap<T>::getMax() {//返回最大值
	printf("得到最大值操作：");
	if (heapSize > 2) {//比较heap[2]和heap[3]
//cout<<"比较heap[2]" << this->heap[2] << "和heap[3]" << this->heap[3] << ",得出最大值:" << this->heap[2]<this->heap[3]?this->heap[3]:this->heap[2] << endl;
		printf("%d\n", heap[2] < heap[3] ? heap[3] : heap[2]);
		return heap[2] < heap[3] ? heap[3] : heap[2];
	}
	if (heapSize == 2) {
//cout << "堆中只含有两个元素，所以取第二个元素：" << heap[2] << endl;
		printf("%d\n", heap[2]);
		return heap[2];
	}
	if (heapSize == 1) {
//cout << "堆中只含有一个元素，最大值取这个元素即可：" << heap[1] << endl;
		printf("%d\n", heap[1]);
		return heap[1];
	}
	throw "错误：空堆不能得到最大值\n";

}


template<class T>
const T& min_max_heap<T>::getMin() {//返回根节点（即第一个元素）即最小元素
	if (heapSize > 0) {
cout << "得到最小值操作：" <<heap[1] << endl;
		return heap[1];
	}
	throw "错误：空堆不能得到最小值\n";
	//printf("错误：空堆\n");
	//return NULL;
}

template<class T>
const T& min_max_heap<T>::popMin() {//删除最小值
if (flagPrint)
cout << "删除最小值操作" << endl;
	if (heapSize > 1) {
		T d = heap[1];
//cout << "将根节点" << heap[1] << "（最小值）替换为最后一个元素" << heap[heapSize] << "，开始下滤：" << endl;
		heap[1] = heap[heapSize--];
if(flagPrint)
cout << "heap[1] = "<<heap[1]<< endl <<"h:\n"<<*this << endl;
		trickleDown(this, 1);
		return d;
	}
	if (heapSize == 1) {
if (flagPrint)
cout << "只有一个元素，故删除后堆为空" << endl;
		heapSize--;
		return heap[1];
	}
	throw "错误：空堆不能删除最小值\n";
	//printf("错误：空堆\n");
	//return NULL;
}

template<class T>
const T& min_max_heap<T>::popMax() {//删除最大值
if (flagPrint)
cout << "删除最大值操作" << endl;
	if (heapSize > 2) {
		int index = 2;
		if (heap[2] < heap[3]) index = 3;
		T d = heap[index];
		heap[index] = heap[heapSize--];
if (flagPrint)
cout << "heap["<<index<<"] = " << heap[index] << endl <<"h:\n"<<*this << endl;

		trickleDown(this, index);

		return d;
	}
	if (heapSize == 2) {
if (flagPrint)
cout << "两个元素，返回heap[2]即可" << endl;
		heapSize--;
		return heap[2];
	}
	if (heapSize == 1) {
if (flagPrint)
cout << "只有一个元素，故删除后堆为空" << endl;
		heapSize--;
		return heap[1];
	}
	throw "错误：空堆不能得到最小值\n";
}


template<class T>
void min_max_heap<T>::output(ostream& out) {//输出堆元素
	//不画斜杠
	//T **heapTreeMatrix;
	//if (heapSize == 0) throw "Error : empty heap not output!";
	//int level = 0;
	//int high = (int)(floor(log(heapSize) / log(2)));//high从0层开始
	//int bottle_node_count_max = pow(2, high);//最下层最多可以拥有的结点数
	//heapTreeMatrix = new T*[high + 1];
	//for (int i = 0; i < high + 1; i++) {
	//	heapTreeMatrix[i] = new T[bottle_node_count_max * 2];
	//}

	//T *t = new T(INF);//////////////////////////////////////////////////初始化
	//for (int i = 0; i < high+1 ; i++) {
	//	for (int j = 0; j < bottle_node_count_max*2; j++) {
	//		heapTreeMatrix[i][j] = *t;
	//	}
	//}
	//
	////将堆中的值写入矩阵
	//int index = 1;
	////printf("%d 1111", heap[1]);
	//while (level < high + 1) {
	//	int inscrease = bottle_node_count_max * 2 / pow(2, level);
	//	for (int j = inscrease/2 ; j < bottle_node_count_max * 2; j += inscrease) {
	//		if(index<=heapSize)
	//		heapTreeMatrix[level][j] = heap[index++];
	//		//printf("%d -%d ", heap[index - 1], index);
	//	}
	//	level++;
	//}
	//	
	////打印
	//for (int i = 0; i < high + 1; i++) {
	//	for (int j = 0; j < bottle_node_count_max * 2; j++) {
	//		if (heapTreeMatrix[i][j] == *t) {
	//			printf("    ");
	//		}
	//		else {
	//			//printf("%4d", heapTreeMatrix[i][j]);
	//			out << setw(4) << heapTreeMatrix[i][j];
	//		}
	//		
	//	}
	//	printf("\n");
	//}

	//for (int i = 0; i < high + 1; i++) {
	//	delete[] heapTreeMatrix[i];
	//}
	//delete[] heapTreeMatrix;

	//斜杠在每个元素上方
	T **heapTreeMatrix;
	if (heapSize == 0) throw "Error : empty heap not output!";
	int level = 0;
	int high = (int)(floor(log(heapSize) / log(2)));//high从0层开始
	int bottle_node_count_max = pow(2, high);//最下层最多可以拥有的结点数
	heapTreeMatrix = new T*[(high + 1) * 2];
	for (int i = 0; i < (high + 1) * 2; i++) {
		heapTreeMatrix[i] = new T[bottle_node_count_max * 2];
	}

	T *t = new T(INF);//////////////////////////////////////////////////初始化
	for (int i = 0; i < (high + 1) * 2; i++) {
		for (int j = 0; j < bottle_node_count_max * 2; j++) {
			heapTreeMatrix[i][j] = *t;
		}
	}

	//将堆中的值写入矩阵
	int index = 1;
	bool flag_zuoxie = true;
	//printf("%d 1111", heap[1]);
	while (level < high + 1) {
		flag_zuoxie = true;
		int inscrease = bottle_node_count_max * 2 / pow(2, level);//计算两个数之间的距离
		for (int j = inscrease / 2; j < bottle_node_count_max * 2; j += inscrease) {
			if (index <= heapSize) {
				heapTreeMatrix[(level + 1) * 2 - 1][j] = heap[index++];
				if (flag_zuoxie) heapTreeMatrix[level * 2][j + 1] = INF - 1;
				else heapTreeMatrix[level * 2][j] = INF - 2;
				flag_zuoxie = !flag_zuoxie;
			}

			//printf("%d -%d ", heap[index - 1], index);
		}
		level++;
	}

	//打印
	for (int i = 1; i < (high + 1) * 2; i++) {
		for (int j = 0; j < bottle_node_count_max * 2; j++) {
			if (heapTreeMatrix[i][j] == *t) {
				printf("    ");
			}
			else if (heapTreeMatrix[i][j] == INF - 1) {
				printf("/   ");
			}
			else if (heapTreeMatrix[i][j] == INF - 2) {
				printf(" \\  ");
			}
			else {

				//printf("%4d", heapTreeMatrix[i][j]);
				out << setw(4) << heapTreeMatrix[i][j];
			}

		}
		printf("\n");
	}

	for (int i = 0; i < high + 1; i++) {
		delete[] heapTreeMatrix[i];
	}
	delete[] heapTreeMatrix;



	//斜杠在上下层元素之间
	//T **heapTreeMatrix;
	//if (heapSize == 0) throw "Error : empty heap not output!";
	//int level = 0;
	//int high = (int)(floor(log(heapSize) / log(2)));//high从0层开始
	//int bottle_node_count_max = pow(2, high);//最下层最多可以拥有的结点数
	//heapTreeMatrix = new T*[(high + 1)*2];
	//for (int i = 0; i < (high + 1)*2; i++) {
	//	heapTreeMatrix[i] = new T[bottle_node_count_max * 2];
	//}

	//T *t = new T(INF);//////////////////////////////////////////////////初始化
	//for (int i = 0; i < (high+1)*2 ; i++) {
	//	for (int j = 0; j < bottle_node_count_max*2; j++) {
	//		heapTreeMatrix[i][j] = *t;
	//	}
	//}
	//
	////将堆中的值写入矩阵
	//int index = 1;
	//bool flag_zuoxie = true;
	////printf("%d 1111", heap[1]);
	//while (level < high + 1) {
	//	flag_zuoxie = true;
	//	int inscrease = bottle_node_count_max * 2 / pow(2, level);//计算两个数之间的距离
	//	for (int j = inscrease/2 ; j < bottle_node_count_max * 2; j += inscrease) {
	//		if (index <= heapSize) {
	//			heapTreeMatrix[(level+1)*2-1][j] = heap[index++];
	//			if (flag_zuoxie) heapTreeMatrix[level * 2][j + inscrease /4 + 1] = INF - 1;
	//			else heapTreeMatrix[level * 2][j - inscrease /4] = INF - 2;
	//			flag_zuoxie = !flag_zuoxie;
	//		}
	//		
	//		//printf("%d -%d ", heap[index - 1], index);
	//	}
	//	level++;
	//}
	//	
	////打印
	//for (int i = 1; i < (high + 1)*2; i++) {
	//	for (int j = 0; j < bottle_node_count_max * 2; j++) {
	//		if (heapTreeMatrix[i][j] == *t) {
	//			printf("    ");
	//		}
	//		else if (heapTreeMatrix[i][j] == INF - 1) {
	//			printf("/   ");
	//		}
	//		else if (heapTreeMatrix[i][j] == INF - 2) {
	//			printf(" \\  ");
	//		}
	//		else {

	//			//printf("%4d", heapTreeMatrix[i][j]);
	//			out << setw(4) << heapTreeMatrix[i][j];
	//		}
	//		
	//	}
	//	printf("\n");
	//}

	//for (int i = 0; i < high + 1; i++) {
	//	delete[] heapTreeMatrix[i];
	//}
	//delete[] heapTreeMatrix;
}

template<class T>
ostream& operator<<(ostream& out, min_max_heap<T>& x) {//<<运算符重载
	
	x.output(out);
	out << endl;
	return out;
}

