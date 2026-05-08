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
	
	//单表操作——增,删,查，打印，清空链表

	//学生表
	bool insertStudent(const Student& s);
	bool removeStudentByKey(const std::string& stuID);
	const Student* findStudent(const std::string& stuID) const;
	void printStudents() const;
	void clearStudents();

	//竞赛表
	bool insertContest(const Contest& c);
	bool removeContestByKey(const std::string& conID);
	const Contest* findContest(const std::string& conID) const;
	void printContests() const;
	void clearContests();

	//获奖表
	bool insertAward(const Award& a);
	bool removeAwardByKey(int awardID);
	const Award* findAward(int awardId) const;
	void printAwards() const;
	void clearAwards();


	//跨表操作

	//添加获奖，学生学号校验+竞赛编号校验
	bool addAward(const std::string& stuID, const std::string& conID, const std::string& prize, std::string& time);

	//删除学生，同时删除获奖记录
	bool removeStudentAwards(const std::string& stuID);

	//删除竞赛，同时删除获奖记录
	bool removeContestAwards(const std::string& conID);

	//按学号、比赛名称、获奖级别删除对应获奖记录
	bool removeAwardByDetails(const std::string& stuID, const std::string& conName, const std::string& prize);

	//按比赛名称删除该比赛所有获奖记录
	bool removeAwardsByConName(const std::string& conName);

	//查询学生所有获奖信息
	void showStudentAwards(const std::string& stuID) const;

	//查询比赛获奖人数排名
	void showContestRanking() const;

	//查询比赛获奖情况
	void showContestAwards(const std::string& conID) const;

	//清空三张表
	void clearAllFiles();
};