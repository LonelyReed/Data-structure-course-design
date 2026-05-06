#pragma once

#include "common.h"

class Award
{
public:
	int awardID;			//编号
	std::string studentID;
	std::string contestID;
	std::string prize;		//获奖级别
	std::string time;		//获奖时间

	//构造函数
	Award():awardID(0),studentID(""),contestID(""),prize(""),time(""){}
	Award(int aID,std::string sID,std::string cID,std::string p,std::string t)
		:awardID(aID),studentID(std::move(sID)),contestID(std::move(cID)),prize(std::move(p)),time(std::move(t)){ }

	//运算重载
	bool operator<(const Award& a) const
	{
		return awardID < a.awardID;
	}

	bool operator==(const Award& a) const
	{
		return awardID == a.awardID;
	}

	//将对象节点格式化为一行文本
	std::string toLine() const
	{
		return std::to_string(awardID) + DELIMITER + studentID + DELIMITER + contestID + DELIMITER + prize + DELIMITER + time;
	}

	//从一行文本解析出对象节点——静态函数
	static bool fromLine(const std::string& line, Award& out)					//定义为静态函数，是因为读取时候没有实例对象，只能依靠类直接调用生成实例对象
	{
		//空行直接放回false
		if (line.empty())	return false;

		// 按顺序读取：编号 -> '|' -> 学生学号 -> '|' -> 竞赛编号 -> '|' -> 获奖级别 -> '|' -> 获奖时间
		std::stringstream ss(line);
		int awardID;
		std::string studentID, contestID, prize, time;
		char delim;
		if ((ss >> awardID >> delim)				//grade是int,先按照整数格式解析grade，解析完后就会停留在后面的'|'
			&& delim == DELIMITER
			&& std::getline(ss, studentID, DELIMITER)			//getline(ss,str,'|')只能读取str，遇到'|'就停止，并去除'|'
			&& std::getline(ss, contestID, DELIMITER)
			&& std::getline(ss, prize, DELIMITER)
			&& std::getline(ss, time))
		{
			//全部读取成功，构造一个学生对象塞给 out
			out = Award(awardID, studentID, contestID, prize, time);
			return true;
		}
		return false;
	}
};

//<<运算重载
inline std::ostream& operator<<(std::ostream& os, const Award& a)
{
	os << a.awardID << DELIMITER << a.studentID << DELIMITER 
		<< a.contestID << DELIMITER << a.prize << DELIMITER << a.time;
	return os;
}