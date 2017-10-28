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
	min_max_heap(int initialCapacity = 10);//Ĭ�ϲ���Ϊ10
	~min_max_heap() { delete[] heap; }//��������
	bool empty() const { return heapSize == 0; }//�ж϶��Ƿ�Ϊ��
	int size() const {//���ضѵĴ�С
		return heapSize;
	}
	T* getHeap() const {
		return heap;
	}

	void  initialize(T *theHeap,int theSize);//������֪���齨��
	const T& getMax();//�õ����ֵ
	const T& getMin();//�õ���Сֵ
	void insert(T&);//����ֵ
	const T& popMin();//ɾ����Сֵ
	const T& popMax();//ɾ�����ֵ
	void output(ostream& out);//���
public:
	int heapSize;//�Ѵ�С
	int arrayLength;//�ѵ����ֵ
	T *heap;//������
};

template<class T>
min_max_heap<T>::min_max_heap(int initialCapacity) {//���캯��
	if (initialCapacity < 1) {//��ʼ��С�������0
		ostringstream s;
		s << "Error : Initial capacity = " << initialCapacity << " Must be > 0";
		throw s.str();
	}
	arrayLength = initialCapacity + 1;//
	heap = new T[arrayLength];
	heapSize = 0;
}

int is_min_level(int i) {//�����±�Ϊi�����ݵĲ㣨��㻹��С�㣩
	if ((int)(floor(log(i) / log(2))) % 2) {
		return 0;
	}
	else {
		return 1;
	}
}

template<class T>
int index_min_child_grandchild(min_max_heap<T>* h ,int i) {//�ҳ��±�Ϊi�Ľ��Ķ��Ӻ���������С��ֵ
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
int index_max_child_grandchild(min_max_heap<T>* h, int i) {//�ҳ��±�Ϊi�Ľ��Ķ��Ӻ���������С��ֵ
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
void swap(min_max_heap<T>* h, int i, int m) {//���������±�Ϊi��m������
	T temp = h->heap[i];
	h->heap[i] = h->heap[m];
	h->heap[m] = temp;
if(flagPrint)
cout << "     heap[" << i << "]:" << h->heap[m] << "<-->" << "heap[" << m << "]:" << h->heap[i] << endl <<"h:\n"<< *h << endl;
}






int trickleDownCount;//��¼���˵Ĵ���
int bubbleUpCount;//��¼���˵Ĵ���

/*
С�����ˣ����ҵ��Լ����Ӻ���������С��ֵ��
�����ֵΪ���ӣ�֤���Լ�û�����ӣ���ʱֻ��Ƚϸ���Сֵ���Լ����������СֵС�������Լ�����λ�ã����˽��������򲻱仯�����˽�����
�����ֵΪ���ӣ���Ƚϸ���Сֵ���Լ����������Сֵ�����Լ�����֤���Ը�Ԫ��Ϊ���ڵ��������Сֵ���Ǹ�Ԫ�أ�������ɣ������������СֵС���Լ�������н���λ�ã��������ж��Լ��븸�׽��Ĵ�С��ϵ��
	������׽ڵ㣨��㣩С���Լ����򽻻�λ�ã�������ֻ�иø��׽ڵ�Ԫ��λ�ò���ȷ�����ԶԸ��׽ڵ�Ԫ�����½������ˣ�
	�����׽ڵ�����Լ�������Լ����½������˲�����
*/
template<class T>
void TrickleDownMin(min_max_heap<T>* h,int i) {//С�����ˣ�����ɾ����

////////////////////////////////////////cout << "��ʼ���е�" << ++trickleDownCount << "������:" << endl;
	int m = index_min_child_grandchild(h,i);//�õ����Ӻ���������С��ֵ
//cout << "�ҳ�Ԫ��"<<h->heap[i]<<"(�±�Ϊ��"<<i<<"���Ķ��Ӻ���������С��ֵ" << endl;
	if (m <= -1) {
//////////////////////////////////cout << "����Ԫ��" << h->heap[i] << ",�±�Ϊ��" << i << "û�ж��Ӻ�����,�������" << endl;		
	return;
	}
else
//cout << "��СֵΪheap[" << m << "]:" << h->heap[m] << endl;
	if (m > second_child(i)) {//���������С
		if (h->heap[m] < h->heap[i]) {
			swap(h, i, m);
//cout << "��СֵΪ���ӣ���С���Լ������Խ��н���:heap["<<i<<"]:"<<h->heap[i]<<"��"<< "heap["<<m<<"]:"<<h->heap[m]<< ",��������Ԫ�����ƣ���hΪ:"<<endl;
//cout<< "heap[" << i << "]:" << h->heap[m] << "<-->" << "heap[" << m << "]:" << h->heap[i] <<endl<< *h << endl;
//cout << "���ڱȽ�Ԫ��heap[" << m << "]:" << h->heap[m] << "�븸�׽ڵ�heap[" << parent(m) << "]:" <<h->heap[parent(m)]<<":" <<endl;
			if (h->heap[m] > h->heap[parent(m)]) {
				swap(h, m, parent(m));
//cout << "��Ȼ," << h->heap[m] << ">" << h->heap[parent(m)] << ",�ʽ��н���,������h��Ϊ��" << endl 
//cout<< "heap["<<m<<"]:"<< h->heap[parent(m)] << "<-->" << "heap["<<parent(m)<<"]:"<< h->heap[m] <<endl<< *h << endl;
			}
			else {
//cout << "��Ȼ��" << h->heap[m] << "<=" << h->heap[parent(m)] << ",�ʲ����н���" << endl;
			}
////////////////////////////cout << "������Ԫ��heap[" << m << "]:" << h->heap[m] << "��������" << endl;
		TrickleDownMin(h, m);
		}
		else {
////////////////////////////cout << "����ֵ��С���������Լ������Բ���Ҫ���н������������"<<endl;
		}
	}
	else {//���������С

		if (h->heap[m] < h->heap[i]) {
			swap(h, i, m);
//cout << "û�����ӣ���СֵΪ���ӣ���С���Լ������Խ��н���.:heap[" << i << "]:" << h->heap[i] << "��" << "heap[" << m << "]:" << h->heap[m]  <<",��������Ԫ�����ƣ���hΪ:" << endl ;
			
//cout<< "heap[" << i << "]:" << h->heap[m] << "<-->" << "heap[" << m << "] : " << h->heap[i]<< ":"<< endl << *h << endl<<"�������"<<endl;
		}
		else {
////////////////////////////////////////cout << "����Ҫ���н������������" << endl;//û�����ӣ�����ֵ��С���������Լ�������
		}
	}
}

template<class T>
void TrickleDownMax(min_max_heap<T>* h,int i) {//������ˣ�����ɾ����
/////////////////////////////////////////cout << "��ʼ���е�" << ++trickleDownCount << "������:" << endl;
	int m = index_max_child_grandchild(h, i);//�õ����Ӻ��������ֵ
	if (m <= -1) {
//////////////////////////////////////////cout << "����Ԫ��" << h->heap[i] << ",�±�Ϊ��" << i << "û�ж��Ӻ�����,�������" << endl;
		return;
	}
	if (m > second_child(i)) {//����������
		if (h->heap[m] > h->heap[i]) {
			swap(h, i, m);
//cout << "heap[" << i << "]:" << h->heap[m] << "<-->" << "heap[" << m << "]:" << h->heap[i] << endl << *h << endl;
			if (h->heap[m] < h->heap[parent(m)]) {
				swap(h, m, parent(m));
//cout << "heap[" << m << "]:" << h->heap[parent(m)] << "<-->" << "heap[" << parent(m) << "]:" << h->heap[m] << endl << *h << endl;
			}
/////////////////////////////////////////////////cout << "������Ԫ��heap[" << m << "]:" << h->heap[m] << "��������" << endl;
			TrickleDownMax(h, m);
		}
		else {
/////////////////////////////////////////////////cout << "����ֵ��󣬵�С���Լ������Բ���Ҫ���н������������" << endl;
		}
	}
	else {//����������
		if (h->heap[m] > h->heap[i]) {
			swap(h, i, m);
//cout << "heap[" << i << "]:" << h->heap[m] << "<-->" << "heap[" << m << "] : " << h->heap[i] << ":" << endl << *h << endl << "�������" << endl;
		}
		else {
///////////////////////////////////////////////////cout << "����Ҫ���н������������" << endl;//û�����ӣ�����ֵ��󣬵�С���Լ�
		}
	}
}

template<class T>
void trickleDown(min_max_heap<T>* h,int i) {//���ˣ�����ɾ��
//cout << "���ж���ɾ������СԪ�أ��������Ԫ��" << endl;
trickleDownCount = 0;
	if (is_min_level(i)) {
//cout << "���˵�Ԫ���±�Ϊ"<<i<<",��Ȼɾ������СԪ��" << endl;
		TrickleDownMin(h, i);
	}
	else {
//cout << "���˵�Ԫ���±�Ϊ" << i << ",��Ȼɾ�������Ԫ��" << endl;
		TrickleDownMax(h, i);
	}
		
}

template<class T>
void bubbleup_min(min_max_heap<T>* h, int i) {//С������

	int pp_i = parent(parent(i));
	if (pp_i <= 0) return;
//printf("���е�%d��С������:\n", ++bubbleUpCount);
	if (h->heap[i]<h->heap[pp_i]) {//����游���Լ����򽻻�
		swap(h, i, pp_i);
		bubbleup_min(h, pp_i);
	}

}

template<class T>
void bubbleup_max(min_max_heap<T>* h, int i) {//�������

	int pp_i = parent(parent(i));
	if (pp_i <= 0) return;
//printf("���е�%d�δ������:\n", ++bubbleUpCount);
	if (h->heap[i]>h->heap[pp_i]) {//����游���Լ�С�򽻻�
		swap(h, i, pp_i);
		bubbleup_max(h, pp_i);
	}

}

template<class T>
void BubbleUp(min_max_heap<T>* h, int i) {//���ˣ������ڲ���
bubbleUpCount = 0;
	int p_i = parent(i);
	if (p_i <= 0) return;
	if (is_min_level(i)) {//�����С�㣬���и��׽ڵ����Լ���ֵ��С�Ƚ�
		if (h->heap[i] > h->heap[p_i]) {//�����ڵ�С���򽻻��������д������
			swap(h, i, p_i);
			bubbleup_max(h, p_i);
		}
		else {//������ڵ�������С������
			bubbleup_min(h, i);
		}
	}
	else {//�����Ǵ��
		if (h->heap[i] < h->heap[p_i]) {//�����׽ڵ�����Լ����򽻻���������С������
			swap(h, i, p_i);
			bubbleup_min(h, p_i);
		}
		else {//�����׽ڵ�С���Լ������д�㽻��
			bubbleup_max(h, i);
		}
	}
}



int flagPrint = true;//�ж��Ƿ��ӡ������Ϣ

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
void min_max_heap<T>::insert(T& Element) {//����
if (flagPrint) {
	cout << "�������-����";
	cout << Element;
	cout << ":" << endl;
}
	
	//�����������������ĳ��ȣ��˴���չΪԭ�ȵ�2��;
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
//printf("����ɹ�\n");
}

template<class T>
const T& min_max_heap<T>::getMax() {//�������ֵ
	printf("�õ����ֵ������");
	if (heapSize > 2) {//�Ƚ�heap[2]��heap[3]
//cout<<"�Ƚ�heap[2]" << this->heap[2] << "��heap[3]" << this->heap[3] << ",�ó����ֵ:" << this->heap[2]<this->heap[3]?this->heap[3]:this->heap[2] << endl;
		printf("%d\n", heap[2] < heap[3] ? heap[3] : heap[2]);
		return heap[2] < heap[3] ? heap[3] : heap[2];
	}
	if (heapSize == 2) {
//cout << "����ֻ��������Ԫ�أ�����ȡ�ڶ���Ԫ�أ�" << heap[2] << endl;
		printf("%d\n", heap[2]);
		return heap[2];
	}
	if (heapSize == 1) {
//cout << "����ֻ����һ��Ԫ�أ����ֵȡ���Ԫ�ؼ��ɣ�" << heap[1] << endl;
		printf("%d\n", heap[1]);
		return heap[1];
	}
	throw "���󣺿նѲ��ܵõ����ֵ\n";

}


template<class T>
const T& min_max_heap<T>::getMin() {//���ظ��ڵ㣨����һ��Ԫ�أ�����СԪ��
	if (heapSize > 0) {
cout << "�õ���Сֵ������" <<heap[1] << endl;
		return heap[1];
	}
	throw "���󣺿նѲ��ܵõ���Сֵ\n";
	//printf("���󣺿ն�\n");
	//return NULL;
}

template<class T>
const T& min_max_heap<T>::popMin() {//ɾ����Сֵ
if (flagPrint)
cout << "ɾ����Сֵ����" << endl;
	if (heapSize > 1) {
		T d = heap[1];
//cout << "�����ڵ�" << heap[1] << "����Сֵ���滻Ϊ���һ��Ԫ��" << heap[heapSize] << "����ʼ���ˣ�" << endl;
		heap[1] = heap[heapSize--];
if(flagPrint)
cout << "heap[1] = "<<heap[1]<< endl <<"h:\n"<<*this << endl;
		trickleDown(this, 1);
		return d;
	}
	if (heapSize == 1) {
if (flagPrint)
cout << "ֻ��һ��Ԫ�أ���ɾ�����Ϊ��" << endl;
		heapSize--;
		return heap[1];
	}
	throw "���󣺿նѲ���ɾ����Сֵ\n";
	//printf("���󣺿ն�\n");
	//return NULL;
}

template<class T>
const T& min_max_heap<T>::popMax() {//ɾ�����ֵ
if (flagPrint)
cout << "ɾ�����ֵ����" << endl;
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
cout << "����Ԫ�أ�����heap[2]����" << endl;
		heapSize--;
		return heap[2];
	}
	if (heapSize == 1) {
if (flagPrint)
cout << "ֻ��һ��Ԫ�أ���ɾ�����Ϊ��" << endl;
		heapSize--;
		return heap[1];
	}
	throw "���󣺿նѲ��ܵõ���Сֵ\n";
}


template<class T>
void min_max_heap<T>::output(ostream& out) {//�����Ԫ��
	//����б��
	//T **heapTreeMatrix;
	//if (heapSize == 0) throw "Error : empty heap not output!";
	//int level = 0;
	//int high = (int)(floor(log(heapSize) / log(2)));//high��0�㿪ʼ
	//int bottle_node_count_max = pow(2, high);//���²�������ӵ�еĽ����
	//heapTreeMatrix = new T*[high + 1];
	//for (int i = 0; i < high + 1; i++) {
	//	heapTreeMatrix[i] = new T[bottle_node_count_max * 2];
	//}

	//T *t = new T(INF);//////////////////////////////////////////////////��ʼ��
	//for (int i = 0; i < high+1 ; i++) {
	//	for (int j = 0; j < bottle_node_count_max*2; j++) {
	//		heapTreeMatrix[i][j] = *t;
	//	}
	//}
	//
	////�����е�ֵд�����
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
	////��ӡ
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

	//б����ÿ��Ԫ���Ϸ�
	T **heapTreeMatrix;
	if (heapSize == 0) throw "Error : empty heap not output!";
	int level = 0;
	int high = (int)(floor(log(heapSize) / log(2)));//high��0�㿪ʼ
	int bottle_node_count_max = pow(2, high);//���²�������ӵ�еĽ����
	heapTreeMatrix = new T*[(high + 1) * 2];
	for (int i = 0; i < (high + 1) * 2; i++) {
		heapTreeMatrix[i] = new T[bottle_node_count_max * 2];
	}

	T *t = new T(INF);//////////////////////////////////////////////////��ʼ��
	for (int i = 0; i < (high + 1) * 2; i++) {
		for (int j = 0; j < bottle_node_count_max * 2; j++) {
			heapTreeMatrix[i][j] = *t;
		}
	}

	//�����е�ֵд�����
	int index = 1;
	bool flag_zuoxie = true;
	//printf("%d 1111", heap[1]);
	while (level < high + 1) {
		flag_zuoxie = true;
		int inscrease = bottle_node_count_max * 2 / pow(2, level);//����������֮��ľ���
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

	//��ӡ
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



	//б�������²�Ԫ��֮��
	//T **heapTreeMatrix;
	//if (heapSize == 0) throw "Error : empty heap not output!";
	//int level = 0;
	//int high = (int)(floor(log(heapSize) / log(2)));//high��0�㿪ʼ
	//int bottle_node_count_max = pow(2, high);//���²�������ӵ�еĽ����
	//heapTreeMatrix = new T*[(high + 1)*2];
	//for (int i = 0; i < (high + 1)*2; i++) {
	//	heapTreeMatrix[i] = new T[bottle_node_count_max * 2];
	//}

	//T *t = new T(INF);//////////////////////////////////////////////////��ʼ��
	//for (int i = 0; i < (high+1)*2 ; i++) {
	//	for (int j = 0; j < bottle_node_count_max*2; j++) {
	//		heapTreeMatrix[i][j] = *t;
	//	}
	//}
	//
	////�����е�ֵд�����
	//int index = 1;
	//bool flag_zuoxie = true;
	////printf("%d 1111", heap[1]);
	//while (level < high + 1) {
	//	flag_zuoxie = true;
	//	int inscrease = bottle_node_count_max * 2 / pow(2, level);//����������֮��ľ���
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
	////��ӡ
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
ostream& operator<<(ostream& out, min_max_heap<T>& x) {//<<���������
	
	x.output(out);
	out << endl;
	return out;
}

