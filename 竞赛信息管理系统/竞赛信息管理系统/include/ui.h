#pragma once

#include "database.h"
#include <string>

//UI类定义
class UI
{
private:
	Database& db;

	//主菜单
	void showMainMenu() const;
	void handleMainMenu(int choice);

	//子菜单
	void studentMenu();
	void contestsMenu();
	void awardMenu();
	void queryMenu();		//查询菜单

	//插入辅助函数
	int getIntInput(const std::string& prompt);
	std::string getStringInput(const std::string& prompt);
	void pause();

public:
	//构造函数
	explicit UI(Database& database) : db(database){}
	//UI运行函数
	void run();

};