#pragma once

#include "common.h"

//定义学生节点的data(class和struct几乎没区别)
class Student
{
public:
	std::string id;
	std::string name;
	int grade;
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

	
};

//<<流输出重载
inline std::ostream& operator<<(std::ostream& os, const Student& s)
{
	os << s.id << DELIMITER << s.name << DELIMITER << s.grade << DELIMITER << s.major;
	return os;
}