#include<iostream>
//#include"wall.h"
#include"snake.h"
//#include"food.h"
#include<ctime>
#include<conio.h>
#include<windows.h>
//��궨λ
void gotoxy3(HANDLE hOut3, int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut3, pos);
}
HANDLE hOut3 = GetStdHandle(STD_OUTPUT_HANDLE); //������ʾ���������


using namespace std;

int pauseScene()
{
	int ret = -1;
	while (true)
	{
		system("cls");
		cout << "������ѡ��" << endl;
		cout << "1.������Ϸ" << endl;
		cout << "2.������Ϸ" << endl;
		cout << "3.��ȡ��Ϸ" << endl;
		cout << "0.�˳���Ϸ" << endl;

		cin >> ret;
		if (ret == 0 || ret == 1 || ret == 2 || ret == 3)
		{
			return ret;
		}
		//����cin��־λ ������ĸ����
		cin.clear();
		////��ջ�����
		cin.sync();

		//��־λΪ0�������� Ϊ1 ������  cin.fail()
		//cout << "��־λ" << cin.fail() << endl;
		//system("pause");

	}

}

int main() {
	srand((unsigned int)time(NULL));
	Wall wall;
	wall.initWall();
	wall.draw();

	Food food(wall);
	food.setFood();
	
	Snake snake(wall,food);
	snake.initSnake();

	gotoxy3(hOut3, 0, wall.ROW);
	cout << "��ǰ�÷֣�" << snake.getScore() << endl;
	cout << "��ߵ÷֣�" << snake.getMaxScore() << endl;

	bool isDead = false;  //������ʶ
	char preKey = NULL;	//��һ�η���ı�ʶ


	while (!isDead)
	{
		char key = _getch(); //�����û�������ַ� ͷ�ļ�<conio.h>
		
		if (preKey==NULL && key == snake.LEFT) //���������Ϸ�������󰴼�
		{
			continue;
		}
		do 
		{
			if (key == snake.UP || key == snake.DOWN || key == snake.LEFT || key == snake.RIGHT)
			{
				//��¼��һ�ΰ���
				if (key == snake.UP && preKey == snake.DOWN||key==snake.DOWN&&preKey==snake.UP
					||key==snake.LEFT&&preKey==snake.RIGHT||key==snake.RIGHT&&preKey==snake.LEFT)//���������ͻ
				{
					key = preKey;
				}
				else
				{
					preKey = key; //���·���
				}
				if (snake.move(key) == true)
				{
					//system("cls");
					//wall.draw();
					snake.saveScore();
					gotoxy3(hOut3, 0, wall.ROW);
					cout << "��ǰ�÷֣�" << snake.getScore() << endl;
					cout << "��ߵ÷֣�" << snake.getMaxScore() << endl;
					Sleep(snake.getSleepTime());
				}
				else
				{
					isDead = true;
					break;
				}
			}
			else if (key == ' ')
			{
				//�ո������ͣ
				//��ͣ����ͣ�Ľ���
				int select=pauseScene();
				switch (select)
				{
				case 0: //�˳�
					exit(0);
					break;
				case 1: //����
					system("cls");
					wall.draw();
					cout << "��ǰ�÷֣�" << snake.getScore() << endl;
					cout << "��ߵ÷֣�" << snake.getMaxScore() << endl;
					key = preKey;
					break;
				case 2: //����
					{
						snake.saveGame(preKey);
						system("cls");
						cout << "�浵�ɹ���" << endl;
						system("pause");
						break;
					}

				case 3: //��ȡ
					{
						snake.readGame(key);
						preKey = key;
						system("cls");
						wall.draw();
						cout << "��ǰ�÷֣�" << snake.getScore() << endl;
						cout << "��ߵ÷֣�" << snake.getMaxScore() << endl;

						break;
					}
				
				default:
					break;
				}
			}
			else
			{
				key = preKey; //��ǰ�����밴��ǿ�Ʊ�Ϊ��һ�η���
			}

		} while (!_kbhit());  //����û�û���κ����룬����0

	}






	//snake.move('w');
	//snake.move('w');
	//snake.move('a');
	//snake.delPoint();

	//����
	//cout<<wall.getWall(0,0)<<endl;
	//wall.setWall(5, 5, 'x');
	//cout << wall.getWall(5, 5)<<endl;
	//cout << wall.getWall(5, 6) << endl;;



	system("pause");
	return 0;
}