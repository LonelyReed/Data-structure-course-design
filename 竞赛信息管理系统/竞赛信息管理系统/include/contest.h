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
};

//<<流输出运算重载
inline std::ostream& operator<<(std::ostream& os, const Contest& c)
{
	os << c.id << DELIMITER << c.name << DELIMITER << c.level << DELIMITER << c.time;
	return os;
}