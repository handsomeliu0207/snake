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
		ROW = 26,//����
		COL = 26  //����

	};
	//��ʼ��ǽ
	void initWall();
	//���ƶ�ά���鵽��Ļ����
	void draw();
	//�����������������еķ���
	void setWall(int x, int y, char key);
	//����������ȡ�����еķ���
	char getWall(int x, int y);


private:
	// ά����ά���� �û���ʾ��Ļ��
	char gameArray[ROW][COL];

};

