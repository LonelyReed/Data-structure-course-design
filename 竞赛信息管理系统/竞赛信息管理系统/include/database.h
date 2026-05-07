#pragma once

#include "table.h"
#include "student.h"
#include "contest.h"
#include "award.h"

//Database数据库类定义
class Database
{
private:
	Table<Student> studentTable;
	Table<Contest> contestTable;
	Table<Award> awardTable;

public:
	//构造函数，传入三个文件名作为参数
	Database(const std::string& stuFile, const std::string& conFile, std::string& awardFile)
		: studentTable(stuFile),contestTable(conFile),awardTable(awardFile){ }
	//析构函数，保持默认
	~Database() = default;

	//禁止拷贝
	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;
	
	//数据加载与保存
	bool loadAll();
	bool saveAll() const;
	
	//跨表操作

	//添加获奖，学生学号校验+竞赛编号校验
	bool addAward(const std::string& stuID, const std::string& conID, const std::string& prize, std::string& time);

	//删除学生，同时删除获奖记录
	bool removeStudent(const std::string& stuID);

	//查询学生所有获奖信息
	void showStudentAwards(const std::string& stuID) const;

	//查询比赛获奖人数排名
	void showContestRanking() const;
};