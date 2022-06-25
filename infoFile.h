#pragma once
#include<iostream>

using namespace std;

#define _FILE_PATH "./file.txt"


class InfoFile
{
public:
	InfoFile();
	~InfoFile();


	//蛇方向
	char key;

	//食物
	int foodX;
	int foodY;

	//蛇长度
	int num;

	int snakeX[600];
	int snakeY[600];

	int maxScore=0;

	//保存游戏
	void saveInfo();

	//读取游戏
	void readInfo();

	void saveScore();
	void readScore();

	
};

