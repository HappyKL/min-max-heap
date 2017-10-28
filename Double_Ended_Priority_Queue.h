#pragma once
using namespace std;
template<class T>
class Double_Ended_Priority_Queue {
public:
	virtual ~Double_Ended_Priority_Queue(){}
	virtual bool empty() const = 0;//���˫�����ȶ���Ϊ�գ��򷵻�true
	virtual int size() const = 0;//����˫�����ȶ��е�Ԫ�ظ���
	virtual const T& getMax() = 0;//�������Ԫ�ص�����
	virtual const T& getMin() = 0;//������СԪ�ص�����
	virtual const T& popMax() = 0;//ɾ�����Ԫ��
	virtual const T& popMin() = 0;//ɾ����СԪ��
	virtual void insert(T& theElement) = 0;//����Ԫ��
};