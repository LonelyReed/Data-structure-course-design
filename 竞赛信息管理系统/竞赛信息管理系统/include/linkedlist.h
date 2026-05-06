#pragma once
#include "common.h"

//节点模板
template <typename T>
struct Node
{
	T data;
	Node* next;
	//定义构造函数，初始化Node
	Node() : next(nullptr) {}									//无参构造，用于头节点
	Node(const T& value) : data(value), next(nullptr) {}		//带参构造，用于普通节点
};

//链表模板
template <typename T>
class LinkedList
{
	//私有成员
private:
	Node<T>* head;				//头指针
	Node<T>* tail;				//尾指针，指向链表最后一个元素，便于直接添加
	size_t count;				//节点数量

	//公有成员
public:
	//构造函数
	LinkedList()
	{
		//生成一个带头节点的空链表
		head = new Node<T>;
		tail = head;				//初始时尾指针指向头节点
		count = 0;
	}
	//析构函数
	~LinkedList()
	{
		//调用clear函数来释放链表内存
		clear();
		//释放头指针和尾指针
		delete head;
	}

	//禁止拷贝,避免浅拷贝对节点双重释放(该管理系统也用不到拷贝)
	LinkedList(const LinkedList&) = delete;
	LinkedList& operator=(const LinkedList&) = delete;


	//链表基本操作

	//编号或学号有序插入——升序
	void insertSorted(const T& value)
	{
		Node<T>* newNode = new Node<T>(value);
		Node<T>* prev = head;			//双指针移动
		Node<T>* p = head->next;

		while (p && p->data < value)	//注意重载<
		{
			p = p->next;
			prev = prev->next;
		}

		//重复检测，插入不允许重复
		if (p && value == p->data)
		{
			delete newNode;
			return;
		}

		newNode->next = p;
		prev->next = newNode;
		
		//如果刚好插到尾部，tail要更新
		if (!newNode->next)
		{
			tail = newNode;
		}
		count++;
		return;
	}

	//尾部添加，加快读取数据库的速度
	void push_back(const T& value)
	{
		Node<T>* newNode = new Node<T>(value);
		tail->next = newNode;
		tail = newNode;
		count++;
		return;
	}

	//查找
	Node<T>* find(const T& value) const
	{
		Node<T>* p = head->next;
		while (p)
		{
			if (p->data == value)		//注意重载==
			{
				return p;
			}
			p = p->next;
		}

		return nullptr;
	}

	//删除第一个符合条件的节点，返回是否成功
	bool remove(const T& value)
	{
		Node<T>* p = head->next;
		Node<T>* prev = head;

		while (p && !(p->data == value))		//不使用!=，方便使用已经重载的==
		{
			p = p->next;
			prev = prev->next;
		}

		//没找到
		if (!p)
		{
			return false;
		}

		prev->next = p->next;
		//如果删除的是尾节点
		if (p == tail)
		{
			tail = prev;
		}

		//目标p找到并断开连接，释放
		delete p;
		count--;
		return true;
	}

	//清空链表
	void clear()
	{
		Node<T>* p = head->next;
		while (p)
		{
			Node<T>* temp = p;
			p = p->next;
			delete temp;
		}
		head->next = nullptr;
		tail = head;
		count = 0;
	}

	//遍历,接受函数或者是lambada表达式（匿名函数）
	template <typename Func>
	void traverse(Func func) const
	{
		//对每一个节点的data都调用func
		Node<T>* p = head->next;
		while (p)
		{
			func(p->data);
			p = p->next;
		}
	}

	//读取头节点，用于数据库的双链联动
	//仅供Table等内部类使用，外部不要直接操作
	const Node<T>* getHead() const
	{
		return head;
	}

	//链表长度
	size_t size() const
	{
		return count;
	}

	//检查空表
	bool empty() const
	{
		return count == 0;
	}

	//打印链表
	void print() const
	{
		//使用匿名函数，[]没有传入参数，注意重载<<
		traverse([](const T& value) {std::cout << value << std::endl;});

		std::cout << std::endl;
	}

	//设置Table类为友元，可直接操作链表
	//允许Table类访问linkedlist类的所有成员
	template <typename> friend class Table;
};
