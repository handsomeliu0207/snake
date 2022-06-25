#include"snake.h"
#include"windows.h"
//光标定位
void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //定义显示器句柄变量

Snake::Snake(Wall&tmpWall, Food& tmpFood):wall(tmpWall),food(tmpFood) //初始化列表
{
	pHead = NULL;
}

Snake::~Snake()
{
}

void Snake::initSnake()
{
	//销毁所有结点
	destroyPoint();

	//添加结点
	addPoint(5, 3);
	addPoint(5, 4);
	addPoint(5, 5);
}

void Snake::destroyPoint()
{
	Point* pCur;
	while (pHead != NULL)
	{
		pCur = pHead->next;
		delete pHead;
		pHead = pCur;
	}

}

void Snake::addPoint(int x, int y)
{
	Point *newPoint = new Point;
	if (newPoint == NULL)
	{
		return;
	}

	newPoint->x = x;
	newPoint->y = y;

	newPoint->next = NULL;
	if (pHead != NULL)
	{
		//将原有的蛇头变为 = 蛇身
		wall.setWall(pHead->x, pHead->y, '=');
		gotoxy(hOut, pHead->y * 2, pHead->x);
		cout << "=";
	}
	//新节点变为头
	newPoint->next = pHead;
	//将新建的结点变为头结点
	pHead = newPoint;
	wall.setWall(pHead->x, pHead->y, '@');
	gotoxy(hOut, pHead->y * 2, pHead->x);
	cout << "@";
}

void Snake::delPoint()
{
	//两个节点以上再删除
	if (pHead == NULL || pHead->next == NULL)
	{
		return;
	}
	//利用两个临时节点，删除尾节点
	Point* pre = pHead;
	Point* cur = pHead->next;
	while (cur->next != NULL)
	{
		pre = pre->next;
		cur = cur->next;
	}
	//修改尾节点内容
	wall.setWall(cur->x, cur->y, ' ');
	gotoxy(hOut, cur->y * 2, cur->x);
	cout << " ";
	delete cur;

	cur = NULL;
	pre->next = NULL;
}

bool Snake::move(char key)
{
	int x = pHead->x;
	int y = pHead->y;

	switch (key)
	{
	case UP:
		x--;
		break;
	case DOWN:
		x++;
		break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	default:
		break;
	}

	//找蛇尾
	Point* pre = pHead;
	Point* cur = pHead->next;
	while (cur->next != NULL)
	{
		pre = pre->next;
		cur = cur->next;
	}
	//cur 蛇尾   
	//判断下一步是否是蛇尾
	if (cur->x == x && cur->y == y)
	{
		isRool = true;
	}
	else
	{
		//判断游戏结束
		if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=')
		{
			addPoint(x, y);
			delPoint();
			//system("cls");
			//wall.draw();
			gotoxy(hOut, 0, wall.ROW);
			cout << "GameOver!!       " << endl;
			cout << "游戏得分为：" << getScore() << endl;
			return false;
		}
	}



	//正常移动
	//吃到食物
	if (wall.getWall(x, y) == '#')
	{
		addPoint(x, y);
		//重新设置食物
		food.setFood();		
	}
	else //未吃到食物
	{
		if (isRool == true)
		{
			//正常移动
			addPoint(x, y);
			delPoint();
			wall.setWall(x,y,'@');
			gotoxy(hOut, y * 2, x);
			cout << "@";
		}
		else
		{
			addPoint(x, y);
			delPoint();
		}


	}
	return true;
}

int Snake::getSleepTime()
{
	int sTime = 0;
	int size = countList();
	if (size < 5)
	{
		sTime = 200;
	}
	else if (size >= 5 && size <= 10)
	{
		sTime = 200-size*4;
	}
	else
	{
		sTime = 160-size;
	}
	return sTime;
}

int Snake::countList()
{
	int size = 0;
	Point* curP = pHead;
	while (curP != NULL)
	{
		size++;
		curP = curP->next;
	}
	return size;
}

int Snake::getScore()
{
	int size = countList();
	int score = (size - 3) * 100;
	return score;
}

void Snake::saveGame(char key)
{
	InfoFile file;
	file.key = key;
	file.foodX = food.getFoodX();
	file.foodY = food.getFoodY();

	file.num = countList();

	Point* curP = pHead;
	for (int i = 0; i < countList(); i++)
	{
		file.snakeX[i] = curP->x;
		file.snakeY[i] = curP->y;
		curP = curP->next;
	}
	file.saveInfo();

}

void Snake::readGame(char& key)
{
	//销毁原来的蛇
	destroyPoint();

	//初始化墙
	wall.initWall();

	//读取存档
	InfoFile file;
	file.readInfo();

	//设置方向
	key = file.key;

	//设置食物
	wall.setWall(file.foodX, file.foodY, '#');

	//蛇长度
	int num = file.num;

	//设置节点
	for (int i = 0; i < num; i++)
	{
		addPoint(file.snakeX[num - 1 - i], file.snakeY[num - 1 - i]);
	}


}

void Snake::saveScore()
{
	InfoFile file;
	file.readScore();
	if (getScore() > file.maxScore)
	{
		file.maxScore = getScore();
		file.saveScore();
	}

}

int Snake::getMaxScore()
{
	InfoFile file;
	file.readScore();
	maxScore = file.maxScore;
	return maxScore;
}
