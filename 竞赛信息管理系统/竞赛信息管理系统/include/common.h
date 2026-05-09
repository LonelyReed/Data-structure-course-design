#pragma once

//导入标准库头文件
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstddef>			//使用size_t
#include <utility>			//使用std::move

//全局常量
const std::string DATA_DIR = "data/";		//数据文件夹根目录
const std::string STUDENT_FILE = "students.txt";
const std::string CONTEST_FILE = "contests.txt";
const std::string AWARD_FILE = "awards.txt";
const char DELIMITER = '|';					//分隔符
