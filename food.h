#pragma once
#include<iostream>
#include"wall.h"


class Food
{
public:
	Food(Wall& tmpWall);
	~Food();
	//����ʳ��
	void setFood();
	int getFoodX();
	int getFoodY();
private:
	//ʳ��λ��
	int foodX;
	int foodY;

	Wall& wall;
};

