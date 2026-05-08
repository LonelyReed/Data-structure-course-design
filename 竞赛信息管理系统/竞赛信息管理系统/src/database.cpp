#include "database.h"

//database中的函数定义

//加载与保存
bool Database::loadAll()
{
	studentTable.loadFromFile();
	contestTable.loadFromFile();
	awardTable.loadFromFile();
	return true;
}

bool Database::saveAll() const
{
	studentTable.saveToFile();
	contestTable.saveToFile();
	awardTable.saveToFile();
	return true;
}

//单表操作

//学生表
bool Database::insertStudent(const Student& s)
{
	return studentTable.insert(s);
}

bool Database::removeStudentByKey(const std::string& stuID)
{
	Student s;
	s.id = stuID;
	return studentTable.removeByKey(s);
}

const Student* Database::findStudent(const std::string& stuID) const
{
	Student s;
	s.id = stuID;
	return studentTable.findByKey(s);
}

void Database::printStudents() const
{
	studentTable.traverse([](const Student& s) {std::cout << s << std::endl; });
}

void Database::clearStudents()
{
	studentTable.clear();
}

//竞赛表
bool Database::insertContest(const Contest& c)
{
	return contestTable.insert(c);
}

bool Database::removeContestByKey(const std::string& conID)
{
	Contest c;
	c.id = conID;
	return contestTable.removeByKey(c);
}

const Contest* Database::findContest(const std::string& conID) const
{
	Contest c;
	c.id = conID;
	return contestTable.findByKey(c);
}

void Database::printContests() const
{
	contestTable.traverse([](const Contest& c) {std::cout << c << std::endl; });
}

void Database::clearContests()
{
	contestTable.clear();
}

//获奖表
bool Database::insertAward(const Award& a)
{
	return awardTable.insert(a);
}

bool Database::removeAwardByKey(int awardID)
{
	Award a;
	a.awardID = awardID;
	return awardTable.removeByKey(a);
}

const Award* Database::findAward(int awardID) const
{
	Award a;
	a.awardID = awardID;
	return awardTable.findByKey(a);
}

void Database::printAwards() const
{
	awardTable.traverse([](const Award& a) {std::cout << a << std::endl; });
}

void Database::clearAwards()
{
	awardTable.clear();
}


//跨表操作

//添加获奖
bool Database::addAward(const std::string& stuID, const std::string& conID, const std::string& prize, std::string& time)
{

}

//删除学生及其获奖
bool Database::removeStudentAwards(const std::string& stuID)
{

}

//查询学生所有获奖信息
void Database::showStudentAwards(const std::string& stuID) const
{

}

////查询比赛获奖人数排名
//void Database::showContestRanking() const
//{
//
//}

void Database::showContestAwards(const std::string& conID) const
{

}