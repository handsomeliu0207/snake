#pragma once
#include<iostream>
#include"wall.h"


class Food
{
public:
	Food(Wall& tmpWall);
	~Food();
	//设置食物
	void setFood();
	int getFoodX();
	int getFoodY();
private:
	//食物位置
	int foodX;
	int foodY;

	Wall& wall;
};

