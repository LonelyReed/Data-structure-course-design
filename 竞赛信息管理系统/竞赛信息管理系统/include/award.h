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
};

//<<运算重载
inline std::ostream& operator<<(std::ostream& os, const Award& a)
{
	os << a.awardID << DELIMITER << a.studentID << DELIMITER 
		<< a.contestID << DELIMITER << a.prize << DELIMITER << a.time;
	return os;
}