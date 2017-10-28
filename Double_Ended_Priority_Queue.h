#pragma once
using namespace std;
template<class T>
class Double_Ended_Priority_Queue {
public:
	virtual ~Double_Ended_Priority_Queue(){}
	virtual bool empty() const = 0;//如果双端优先队列为空，则返回true
	virtual int size() const = 0;//返回双端优先队列的元素个数
	virtual const T& getMax() = 0;//返回最大元素的引用
	virtual const T& getMin() = 0;//返回最小元素的引用
	virtual const T& popMax() = 0;//删除最大元素
	virtual const T& popMin() = 0;//删除最小元素
	virtual void insert(T& theElement) = 0;//插入元素
};