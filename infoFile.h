#pragma once
#include<iostream>

using namespace std;

#define _FILE_PATH "./file.txt"


class InfoFile
{
public:
	InfoFile();
	~InfoFile();


	//�߷���
	char key;

	//ʳ��
	int foodX;
	int foodY;

	//�߳���
	int num;

	int snakeX[600];
	int snakeY[600];

	int maxScore=0;

	//������Ϸ
	void saveInfo();

	//��ȡ��Ϸ
	void readInfo();

	void saveScore();
	void readScore();

	
};

