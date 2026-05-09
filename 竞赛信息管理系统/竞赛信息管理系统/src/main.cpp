#include "database.h"
#include "ui.h"

int main()
{
	Database db("students.txt", "contests.txt", "awards.txt");
	
	//加载文件
	db.loadAll();

	UI ui(db);
	ui.run();		//进入主循环

	//退出后默认保存
	db.saveAll();

	return 0;
}