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
	studentTable.print();
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
	contestTable.print();
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
	awardTable.print();
}

void Database::clearAwards()
{
	awardTable.clear();
}


//跨表操作

//添加获奖
bool Database::addAward(const std::string& stuID, const std::string& conID, const std::string& prize, std::string& time)
{
	//学号检验——学生必须存在
	if (!findStudent(stuID))
	{
		std::cerr << " Error:student ID " << stuID << " Not found,can not add award record " << std::endl;
		return false;
	}

	//竞赛检验——竞赛必须存在
	if (!findContest(conID))
	{
		std::cerr << " Error:contest ID " << conID << " Not found,can not add award record " << std::endl;
		return false;
	}

	//分配获奖记录编号
	int maxID = 0;
	awardTable.traverse([&maxID](const Award& a)
		{
			if (a.awardID > maxID)
			{
				maxID = a.awardID;
			}
		});

	Award newAward(maxID + 1, stuID, conID, prize, time);
	return insertAward(newAward);
}	

//删除学生及其获奖——先删除获奖记录，再删除学生
bool Database::removeStudentAwards(const std::string& stuID)
{
	//收集获得该学生所有获奖记录ID
	std::vector<int> awardIDs;
	awardTable.traverse([&](const Award& a) {
		if (a.studentID == stuID)
		{
			awardIDs.push_back(a.awardID);
		}
	});

	//一个一个删除记录
	for (int id : awardIDs)
	{
		removeAwardByKey(id);
	}

	//删除学生
	return removeStudentByKey(stuID);
}

//删除竞赛，同时删除获奖记录——先删除获奖记录，再删除比赛
bool Database::removeContestAwards(const std::string& conID)
{
	//收集获得该比赛的所有相关获奖记录ID
	std::vector<int> awardIDs;
	awardTable.traverse([&](const Award& a) {
		if (a.contestID == conID)
		{
			awardIDs.push_back(a.awardID);
		}
		});

	//一个一个删除获奖记录
	for (int id : awardIDs)
	{
		removeAwardByKey(id);
	}

	//删除比赛
	return removeContestByKey(conID);
}

//按学号、比赛名称、获奖级别删除对应获奖记录
bool Database::removeAwardByDetails(const std::string& stuID, const std::string& conName, const std::string& prize)
{
	//通过比赛名称反向找到竞赛编号
	std::string conID;
	bool foundContest = false;
	contestTable.traverse([&](const Contest& c) {
		if (c.name == conName)
		{
			conID = c.id;
			foundContest = true;
		}
	});

	//没有找到比赛
	if (!foundContest)
	{
		std::cerr << " Error:contest name " << conName << " Not found " << std::endl;
		return false;
	}

	//在award表中寻找匹配的记录
	int targetID = -1;				//标记是否找到
	awardTable.traverse([&](const Award& a) {
		if (a.studentID == stuID && a.contestID == conID && a.prize == prize)
		{
			targetID = a.awardID;
		}
	});

	//没有找到
	if (targetID == -1)
	{
		std::cerr << " Error:Not found the award record that meets a condition " << std::endl;
		return false;
	}

	//删除符合条件的获奖记录
	return removeAwardByKey(targetID);
}

//按比赛名称删除该比赛所有获奖记录
bool Database::removeAwardsByConName(const std::string& conName)
{
	//由比赛名称找到比赛编号
	std::string conID;
	bool foundContest = false;
	contestTable.traverse([&](const Contest& c) {
		if (c.name == conName)
		{
			conID = c.id;
			foundContest = true;
		}
		});

	//没有找到比赛
	if (!foundContest)
	{
		std::cerr << " Error:contest name " << conName << " Not found " << std::endl;
		return false;
	}

	//收集获得该比赛的所有相关获奖记录ID
	std::vector<int> awardIDs;
	awardTable.traverse([&](const Award& a) {
		if (a.contestID == conID)
		{
			awardIDs.push_back(a.awardID);
		}
		});

	//一个一个删除获奖记录
	for (int id : awardIDs)
	{
		removeAwardByKey(id);
	}

	return true;			//没有删除竞赛本身，只是删除了获奖信息
}

//查询学生所有获奖信息
void Database::showStudentAwards(const std::string& stuID) const
{
	//调用函数寻找该学生是否存在
	const Student* s = findStudent(stuID);
	
	//没有找到
	if (!s)
	{
		std::cerr << " Error:Not found the student whose ID is " << stuID << std::endl;
		return;
	}

	//找到并打印出来
	std::cout << s->name << " " << s->id << "的获奖记录" << std::endl;
	//判断该学生是否获过奖
	bool isAward = false;
	//遍历并打印
	awardTable.traverse([&](const Award& a) {
		if (a.studentID == stuID)
		{
			std::cout << a << std::endl;
		}
		isAward = true;
	});

	//没有获奖记录
	if (!isAward)
	{
		std::cout << "暂时没有获奖记录" << std::endl;
	}
}

//查询比赛获奖人数排名
void Database::showContestRanking() const
{
	return;
}

//查询比赛获奖情况
void Database::showContestAwards(const std::string& conID) const
{
	//调用函数寻找该比赛是否存在
	const Contest* c = findContest(conID);

	//没有找到
	if (!c)
	{
		std::cerr << " Error:Not found the contest whose ID is " << conID << std::endl;
		return;
	}

	//找到并打印出来
	std::cout << c->name << "相关的获奖记录" << std::endl;
	//判断该学生是否获过奖
	bool isAward = false;
	//遍历并打印
	awardTable.traverse([&](const Award& a) {
		if (a.contestID == conID)
		{
			std::cout << a << std::endl;
		}
		isAward = true;
		});

	//没有获奖记录
	if (!isAward)
	{
		std::cout << "暂时没有获奖记录" << std::endl;
	}
}

//清空三张表
void Database::clearAllFiles()
{
	clearStudents();
	clearContests();
	clearAwards();

	//清空完后一定要保存
	saveAll();
	std::cout << " 所有数据已清空，文件内容已经删除 " << std::endl;

}