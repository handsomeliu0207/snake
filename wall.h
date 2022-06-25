#pragma once
#include<iostream>

using namespace std;



class Wall
{
public:
	Wall();
	~Wall();
	enum
	{
		ROW = 26,//行数
		COL = 26  //列数

	};
	//初始化墙
	void initWall();
	//绘制二维数组到屏幕窗口
	void draw();
	//根据索引设置数组中的符号
	void setWall(int x, int y, char key);
	//根据索引获取数组中的符号
	char getWall(int x, int y);


private:
	// 维护二维数组 用户显示屏幕中
	char gameArray[ROW][COL];

};

