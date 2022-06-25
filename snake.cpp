#include"snake.h"
#include"windows.h"
//��궨λ
void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //������ʾ���������

Snake::Snake(Wall&tmpWall, Food& tmpFood):wall(tmpWall),food(tmpFood) //��ʼ���б�
{
	pHead = NULL;
}

Snake::~Snake()
{
}

void Snake::initSnake()
{
	//�������н��
	destroyPoint();

	//��ӽ��
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
		//��ԭ�е���ͷ��Ϊ = ����
		wall.setWall(pHead->x, pHead->y, '=');
		gotoxy(hOut, pHead->y * 2, pHead->x);
		cout << "=";
	}
	//�½ڵ��Ϊͷ
	newPoint->next = pHead;
	//���½��Ľ���Ϊͷ���
	pHead = newPoint;
	wall.setWall(pHead->x, pHead->y, '@');
	gotoxy(hOut, pHead->y * 2, pHead->x);
	cout << "@";
}

void Snake::delPoint()
{
	//�����ڵ�������ɾ��
	if (pHead == NULL || pHead->next == NULL)
	{
		return;
	}
	//����������ʱ�ڵ㣬ɾ��β�ڵ�
	Point* pre = pHead;
	Point* cur = pHead->next;
	while (cur->next != NULL)
	{
		pre = pre->next;
		cur = cur->next;
	}
	//�޸�β�ڵ�����
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

	//����β
	Point* pre = pHead;
	Point* cur = pHead->next;
	while (cur->next != NULL)
	{
		pre = pre->next;
		cur = cur->next;
	}
	//cur ��β   
	//�ж���һ���Ƿ�����β
	if (cur->x == x && cur->y == y)
	{
		isRool = true;
	}
	else
	{
		//�ж���Ϸ����
		if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=')
		{
			addPoint(x, y);
			delPoint();
			//system("cls");
			//wall.draw();
			gotoxy(hOut, 0, wall.ROW);
			cout << "GameOver!!       " << endl;
			cout << "��Ϸ�÷�Ϊ��" << getScore() << endl;
			return false;
		}
	}



	//�����ƶ�
	//�Ե�ʳ��
	if (wall.getWall(x, y) == '#')
	{
		addPoint(x, y);
		//��������ʳ��
		food.setFood();		
	}
	else //δ�Ե�ʳ��
	{
		if (isRool == true)
		{
			//�����ƶ�
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
	//����ԭ������
	destroyPoint();

	//��ʼ��ǽ
	wall.initWall();

	//��ȡ�浵
	InfoFile file;
	file.readInfo();

	//���÷���
	key = file.key;

	//����ʳ��
	wall.setWall(file.foodX, file.foodY, '#');

	//�߳���
	int num = file.num;

	//���ýڵ�
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
