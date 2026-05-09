#include "ui.h"
#include <iostream>
#include <string>
#include <limits>

//主菜单
void UI::showMainMenu() const
{
	std::cout << "\n========== 学生竞赛信息管理系统 ==========\n"
        << "1. 学生管理\n"
        << "2. 竞赛管理\n"
        << "3. 获奖记录管理\n"
        << "4. 综合查询与统计\n"
        << "5. 清空获奖链表（不删文件）\n"    // 功能7
        << "6. 保存获奖信息到文件\n"          // 功能9
        << "7. 清空所有数据（含文件）\n"      // 功能8
        << "0. 退出并保存\n"
        << "==========================================\n";
}

//辅助函数
int UI::getIntInput(const std::string& prompt)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        //输入失败
        if (std::cin.fail())
        {
            std::cin.clear();
            //忽略刚刚的输入
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << " 无效输入，输入数字 " << std::endl;
        }
        else
        {
            //忽略输入的文字，只关注数字
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

    }
}

std::string UI::getStringInput(const std::string& prompt)
{
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

void UI::pause()
{
    std::cout << " 按Enter键继续... " << std::endl;
    std::cin.get();
}

//子菜单

//学生菜单
void UI::studentMenu()
{
    int choice;
    do
    {

    } while (choice != 0);
}

//竞赛菜单
void UI::contestsMenu()
{
    int choice;
    do
    {

    } while (choice != 0);
}

//获奖菜单
void UI::awardMenu()
{
    int choice;
    do
    {

    } while (choice != 0);
}

//综合查询与统计菜单
void UI::queryMenu()
{
    int choice;
    do
    {

    } while (choice != 0);
}


//运行函数
void UI::run()
{
    int choice;
    do
    {
        showMainMenu();
        choice = getIntInput("请选择：");
        
        //匹配选择
        switch (choice)
        {
        case 1:
            studentMenu(); 
            break;
        
        case 2:
            contestsMenu();
            break;

        case 3:
            awardMenu();
            break;

        case 4:
            queryMenu();
            break;

        case 5:
            db.clearAwards();
            std::cout << "获奖链表已清空" << std::endl;
            pause();        //等待下一步指令
            break;

        case 6:
            db.saveAll();
            pause();
            break;

        case 7:
            std::string confirm = getStringInput("确定要清空所有文件数据吗？此操作不可恢复！[y/n]:");
            if (confirm == "y" || confirm == "Y")        //不区分大小写
            {
                db.clearAllFiles();
                std::cout << "所有文件数据已经清空" << std::endl;
            }
            else
            {
                std::cout << "已取消操作" << std::endl;
            }

            pause();
            break;

        case 0:
            std::cout << "正在保存数据并退出..." << std::endl;
            db.saveAll();
            break;
        
        default:
            std::cout << "无效输入选项，请重新输入" << std::endl;
            pause();
        }
    } while (choice != 0);
}