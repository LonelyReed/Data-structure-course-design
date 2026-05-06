#pragma once

#include "common.h"
#include <sstream>

//定义学生节点的data(class和struct几乎没区别)
class Student
{
public:
	std::string id;
	std::string name;
	int grade;				//年级
	std::string major;		//专业

	//无参构造
	Student() : id(""),name(""),grade(0),major(""){}
	//带参构造
	Student(std::string i,std::string n,int g,std::string m)
		: id(std::move(i)),name(std::move(n)),grade(g),major(std::move(m)){ }

	//<运算重载,按学号比较
	bool operator<(const Student& s) const
	{
		return id < s.id;
	}

	//==运算重载
	bool operator==(const Student& s) const
	{
		return id == s.id;
	}

	//将对象节点格式化为一行文本
	std::string toLine() const
	{
		return id + DELIMITER + name + DELIMITER + std::to_string(grade) + DELIMITER + major;
	}

	//从一行文本解析出对象节点——静态函数
	static bool fromLine(const std::string& line, Student& out)					//定义为静态函数，是因为读取时候没有实例对象，只能依靠类直接调用生成实例对象
	{
		//空行直接放回false
		if (line.empty())	return false;

		// 按顺序读取：学号 -> '|' -> 姓名 -> '|' -> 年级 -> '|' -> 专业
		std::stringstream ss(line);
		std::string id, name, major;
		int grade;
		char delim;
		if(std::getline(ss,id,DELIMITER)			//getline(ss,str,'|')只能读取str，遇到'|'就停止，并去除'|'
			&& std::getline(ss,name,DELIMITER)
			&& (ss >> grade >> delim)				//grade是int,先按照整数格式解析grade，解析完后就会停留在后面的'|'
			&& delim == DELIMITER					//此时读入的delim就是'|'
			&& std::getline(ss, major))
		{
			//全部读取成功，构造一个学生对象塞给 out
			out = Student(id,name,grade,major);
			return true;
		}
		return false;
	}

};

//<<流输出重载
inline std::ostream& operator<<(std::ostream& os, const Student& s)
{
	os << s.id << DELIMITER << s.name << DELIMITER << s.grade << DELIMITER << s.major;
	return os;
}