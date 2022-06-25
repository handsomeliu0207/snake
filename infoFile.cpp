#include"infoFile.h"
#include<fstream>

InfoFile::InfoFile()
{
}

InfoFile::~InfoFile()
{
}

void InfoFile::saveInfo()
{
	ofstream ofs(_FILE_PATH);
	if (!ofs.is_open())
	{
		return;
	}
	ofs << key << endl; //保存方向
	ofs << foodX << "|"; //保存食物
	ofs << foodY << endl;
	ofs << num << endl; //长度

	for (int i = 0; i < num; i++) //保存蛇
	{
		ofs << snakeX[i] << "|";
		ofs << snakeY[i] << endl;
	}
	ofs.close();

}

void InfoFile::readInfo()
{
	ifstream ifs(_FILE_PATH);
	if (!ifs.is_open())
	{
		return;
	}

	char buf[1024];
	ifs.getline(buf,sizeof(buf));
	//运行方向
	key = buf[0];

	memset(buf, 0, sizeof(buf));
	ifs.getline(buf, sizeof(buf)); //食物
	char* str = strtok(buf, "|");
	foodX = atoi(str);
	str=strtok(NULL, "|");
	foodY = atoi(str);

	memset(buf, 0, sizeof(buf));
	ifs.getline(buf, sizeof(buf));
	num = atoi(buf);

	for (int i = 0; i < num; i++)
	{
		memset(buf, 0, sizeof(buf));
		ifs.getline(buf, sizeof(buf));
		char* str2 = strtok(buf, "|");
		snakeX[i] = atoi(str2);

		str2 = strtok(NULL, "|");
		snakeY[i] = atoi(str2);
	}
	ifs.close();
}

void InfoFile::saveScore()
{
	ofstream ofs1("./score.txt");
	if (!ofs1.is_open())
	{
		return;
	}
	ofs1 << maxScore << endl;
	ofs1.close();
}

void InfoFile::readScore()
{
	ifstream ifs1("./score.txt");
	if (!ifs1.is_open())
	{
		return;
	}
	char buf[1024];
	ifs1.getline(buf, sizeof(buf));
	maxScore = atoi(buf);
	ifs1.close();
}

