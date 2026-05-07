#pragma once

#include "linkedlist.h"
#include <fstream>
#include <sstream>

//Table模板类
template <typename T>
class Table
{
private:
	LinkedList<T> list;				//table基于linkedlist实现，存储链表信息
	std::string filename;			//txt文件

public:
	//构造函数指定数据文件名
	explicit Table(const std::string& fname):filename(fname){}				//禁止隐式类型转化
	~Table() = default;														//编译器生成默认析构函数，这是由于禁止拷贝是特殊成员函数

	//禁止拷贝，与LinkedList一致
	Table(const Table&) = delete;
	Table& operator=(const Table&) = delete;

	//插入，自动去重
	bool insert(const T& record)
	{
		//去重
		if (list.find(record))
		{
			return false;
		}
		//有序插入
		list.insertSorted(record);
		return true;
	}

	//按主键查找
	const T* findByKey(const T& key) const
	{
		const Node<T>* node = list.find(key);
		if (node)
		{
			return &(node->data);			//返回node指向的data的地址值，不能返回node的地址值，node的地址值不是链表节点的
		}
		else
		{
			return nullptr;
		}
	}

	//删除
	bool removeByKey(const T& key)
	{
		return list.remove(key);
	}

	//遍历,推荐使用lambda函数
	template <typename Func>
	void traverse(Func func) const
	{
		list.traverse(func);
	}

	//获取表中记录总数
	size_t size() const
	{
		return list.size();
	}

	//清空表
	void clear()
	{
		if (!list.empty()) return list.clear();
	}

	//读取文件
	void loadFromFile()
	{
		std::ifstream file(filename);
		if (!file.is_open())
		{
			std::cerr << " Warning: Cannot open " << filename << std::endl;
			return;
		}

		//读取新数据前，删除当前链表的旧有数据
		clear();

		std::string line;
		while (std::getline(file, line))
		{
			if (line.empty())
			{
				//如果为空行，那么跳过读下一行
				continue;
			}
			T record;
			if (T::fromLine(line, record))
			{
				insert(record);
			}
			else
			{
				std::cerr << "Skipping bad line:" << line << std::endl;
			}
		}

		//关闭文件
		file.close();
	}

	//保存文件
	void saveToFile() const
	{
		//写入方式打开文件
		std::ofstream file(filename);
		if (!file) return;
		if (!file.is_open())
		{
			std::cerr << "Error: Cannot write to file" << filename << std::endl;
			return;
		}
		list.traverse([&file](const T& record) {file << record.toLine() << std::endl; });

		//关闭文件
		file.close();
	}
};