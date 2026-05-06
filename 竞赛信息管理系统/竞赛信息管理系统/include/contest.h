#pragma once

#include "common.h"

class Contest
{
public:
	std::string id;
	std::string name;
	std::string level;			//竞赛等级
	std::string time;			//比赛时间

	Contest() : id(""),name(""),level(""),time(""){}
	Contest(std::string i, std::string n, std::string lev, std::string t)
		: id(std::move(i)),name(std::move(n)),level(std::move(lev)),time(std::move(t)){ }

	//运算重载
	bool operator<(const Contest& c) const
	{
		return id < c.id;
	}

	bool operator==(const Contest& c) const
	{
		return id == c.id;
	}

	//将对象节点格式化为一行文本
	std::string toLine() const
	{
		return id + DELIMITER + name + DELIMITER + level + DELIMITER + time;
	}

	//从一行文本解析出对象节点——静态函数
	static bool fromLine(const std::string& line, Contest& out)					//定义为静态函数，是因为读取时候没有实例对象，只能依靠类直接调用生成实例对象
	{
		//空行直接放回false
		if (line.empty())	return false;

		// 按顺序读取：编号 -> '|' -> 比赛名称 -> '|' -> 竞赛等级 -> '|' -> 比赛时间
		std::stringstream ss(line);
		std::string id, name, level,time;
		if (std::getline(ss, id, DELIMITER)			//getline(ss,str,'|')只能读取str，遇到'|'就停止，并去除'|'
			&& std::getline(ss, name, DELIMITER)
			&& std::getline(ss, level, DELIMITER)									
			&& std::getline(ss, time))
		{
			//全部读取成功，构造一个学生对象塞给 out
			out = Contest(id, name, level, time);
			return true;
		}
		return false;
	}
};

//<<流输出运算重载
inline std::ostream& operator<<(std::ostream& os, const Contest& c)
{
	os << c.id << DELIMITER << c.name << DELIMITER << c.level << DELIMITER << c.time;
	return os;
}