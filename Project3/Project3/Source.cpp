#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <Windows.h>
using namespace std;

char** fieldCreate()//создание нового поля без кораблей
{
	char** field = new char* [10];
	for (int i = 0; i < 10; i++)
	{
		field[i] = new char[10];
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			field[i][j] = '~';
		}
	}
	return field;
}
void graphic(char** field)//вывод поля в консоль
{
	cout << "  ";
	for (int i = 0; i <= 9; i++)
	{
		cout << i << " ";
	}
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		char row(65 + i);
		cout << row << " ";
		for (int j = 0; j < 10; j++)
		{
			cout << field[i][j] << " ";
		}
		cout << endl;
	}
}

struct Field
{
	int shipTileCount = 20;
	char** fieldFull = fieldCreate();
	char** fieldCovered = fieldCreate();
};

Field fieldChange(Field Subject, int shotI, int shotJ, bool hit)
{

	if (hit)
	{
		Subject.fieldCovered[shotI][shotJ] = 'x';
		Subject.fieldFull[shotI][shotJ] = 'x';
		Subject.shipTileCount--;
	}
	else
	{
		Subject.fieldCovered[shotI][shotJ] = '*';
		Subject.fieldFull[shotI][shotJ] = '*';
	}
	return Subject;
}

class Player
{
private:
	string name;
	Field field;
	char** fieldFill(char** field)
	{
		int shipCount = 1;
		while (shipCount <= 10)
		{
			system("cls");
			cout << "Заполняем поле игрока " << name << endl;
			graphic(field);
			cout << "______________________" << endl;
			if (shipCount == 1)
			{
				char crd1[2], crd2[2];
				int axis;
				cout << "Размещаем 4-ёх палубное судно." << endl;
				cout << "Набор координат(формата A1, латиница) первого конца корабля: ";
				cin >> crd1;
				cout << "Набор координат(формата A1, латиница) второго конца корабля: ";
				cin >> crd2;
				cout << "Введите 0, если корабль расположен вертикально и 1, если горизонтально: ";
				cin >> axis;
				if (validPlacement(field, crd1, crd2, axis, 4) == true)
				{
					shipCount++;
					field = shipPlacement(field, crd1, crd2, axis, 4);

				}
				else
				{
					cout << "Недопустимое расположение корябля. Попробуйте снова.";
					continue;
				}
			}
			else if (shipCount == 2 || shipCount == 3)
			{
				char crd1[2], crd2[2];
				int axis;
				cout << "Размещаем 3-ёх палубное судно." << endl;
				cout << "Набор координат(формата A1, латиница) первого конца корабля: ";
				cin >> crd1;
				cout << "Набор координат(формата A1, латиница) второго конца корабля: ";
				cin >> crd2;
				cout << "Введите 1, если корабль расположен вертикально и 2, если горизонтально: ";
				cin >> axis;
				if (validPlacement(field, crd1, crd2, axis, 3) == true)
				{
					shipCount++;
					field = shipPlacement(field, crd1, crd2, axis, 3);
				}
				else
				{
					cout << "Недопустимое расположение корябля. Попробуйте снова.";
					continue;
				}
			}
			else if (shipCount >= 4 && shipCount <= 6)
			{
				char crd1[2], crd2[2];
				int axis;
				cout << "Размещаем 2-ух палубное судно." << endl;
				cout << "Набор координат(формата A1, латиница) первого конца корабля: ";
				cin >> crd1;
				cout << "Набор координат(формата A1, латиница) второго конца корабля: ";
				cin >> crd2;
				cout << "Введите 1, если корабль расположен вертикально и 2, если горизонтально: ";
				cin >> axis;
				if (validPlacement(field, crd1, crd2, axis, 2) == true)
				{
					shipCount++;
					field = shipPlacement(field, crd1, crd2, axis, 2);
				}
				else
				{
					cout << "Недопустимое расположение корябля. Попробуйте снова.";
					continue;
				}
			}
			else
			{
				char crd[2];
				int axis;
				cout << "Размещаем 1-но палубное судно." << endl;
				cout << "Набор координат(формата A1, латиница) корабля: ";
				cin >> crd;
				if (validPlacement(field, crd) == true)
				{
					shipCount++;
					field = shipPlacement(field, crd);
				}
				else
				{
					cout << "Недопустимое расположение корябля. Попробуйте снова.";
					continue;
				}
			}
		}
		return field;
	}
public:
	bool victory = false;

	bool validPlacement(char** field, char* crd1, char* crd2, int axis, int shipSize)//выдача разрешения на установку корябля в заданных координатах при длине корябля больше 1
	{
		bool valid = false;
		if (axis == 0)
		{
			if (crd1[1] == crd2[1])
			{
				if (int(crd1[0]) - int(crd2[0]) == (shipSize - 1))
				{
					for (int i = (int(crd2[0]) - 65); i < (int(crd1[0]) - 65); i++)
					{
						if (validSurround(field, i, (int(crd1[1]) - 48)))
						{
							valid = true;
						}
						else
						{
							valid = false;
							break;
						}
					}
				}
				else if (int(crd2[0]) - int(crd1[0]) == (shipSize - 1))
				{
					for (int i = (int(crd1[0]) - 65); i < (int(crd2[0]) - 65); i++)
					{
						if (validSurround(field, i, (int(crd1[1]) - 48)))
						{
							valid = true;
						}
						else
						{
							valid = false;
							break;
						}
					}
				}
				else valid = false;
			}
			else valid = false;
		}
		else
		{
			if (crd1[0] == crd2[0])
			{
				if (int(crd1[1]) - int(crd2[1]) == (shipSize - 1))
				{
					for (int j = (int(crd2[1]) - 48); j < (int(crd1[1]) - 48); j++)
					{
						if (validSurround(field, (int(crd1[0] - 65)), j))
						{
							valid = true;
						}
						else
						{
							valid = false;
							break;
						}
					}
				}
				else if (int(crd2[1]) - int(crd1[1]) == (shipSize - 1))
				{
					for (int j = (int(crd1[1]) - 48); j < (int(crd2[1]) - 48); j++)
					{
						if (validSurround(field, (int(crd1[0] - 65)), j))
						{
							valid = true;
						}
						else
						{
							valid = false;
							break;
						}
					}
				}
				else valid = false;
			}
			else valid = false;
		}
		return valid;
	}
	bool validPlacement(char** field, char* crd)//выдача разрешения на установку корябля в заданных координатах при длине корабля равной единице
	{
		return validSurround(field, (int(crd[0]) - 65), (int(crd[1]) - 48));
	}
	bool validSurround(char** field, int i, int j)//проверка на наличиче занятых клеток вокруг и в заданной клетке
	{
		bool valid = false;
		if (i != 0 && i != 9 && j != 0 && j != 9)
		{
			valid = validCheck(field, i + 1, j + 1, i - 1, j - 1);
		}
		else if (i == 0 && j == 0)
		{
			valid = validCheck(field, i + 1, j + 1, i, j);
		}
		else if (i == 9 && j == 9)
		{
			valid = validCheck(field, i, j, i - 1, j - 1);
		}
		else if (i == 0 && j == 9)
		{
			valid = validCheck(field, i + 1, j, i, j - 1);
		}
		else if (i == 9 && j == 0)
		{
			valid = validCheck(field, i, j + 1, i - 1, j);
		}
		else if (i == 0 && (j != 9 && j != 0))
		{
			valid = validCheck(field, i + 1, j + 1, i, j - 1);
		}
		else if (i == 9 && (j != 9 && j != 0))
		{
			valid = validCheck(field, i, j + 1, i - 1, j - 1);
		}
		else if ((i != 0 && i != 9) && j == 0)
		{
			valid = validCheck(field, i + 1, j + 1, i - 1, j);
		}
		else if ((i != 0 && i != 9) && j == 9)
		{
			valid = validCheck(field, i + 1, j, i - 1, j - 1);
		}
		return valid;
	}
	bool validCheck(char** field, int maxI, int maxJ, int minI, int minJ)
	{
		bool valid = false;
		for (int i = minI; i <= maxI; i++)
		{
			for (int j = minJ; j <= maxJ; j++)
			{
				if (field[i][j] == '~') valid = true;
				else
				{
					valid = false;
					return valid;
				}
			}
		}
		return valid;
	}

	char** shipPlacement(char** field, char* crd1, char* crd2, int axis, int shipSize)
	{
		int I1 = int(crd1[0]) - 65, I2 = int(crd2[0]) - 65;
		int J1 = int(crd1[1]) - 48, J2 = int(crd2[1]) - 48;
		if (axis == 0)
		{
			if (I1 - I2 == (shipSize - 1))
			{
				for (int i = I2; i <= I1; i++)
				{
					field[i][J1] = '#';
				}
			}
			else
			{
				for (int i = I1; i <= I2; i++)
				{
					field[i][J1] = '#';
				}
			}
		}
		else
		{
			if (J1 - J2 == (shipSize - 1))
			{
				for (int j = J2; j <= J1; j++)
				{
					field[I1][j] = '#';
				}
			}
			else
			{
				for (int j = J1; j <= J2; j++)
				{
					field[I1][j] = '#';
				}
			}
		}
		return field;
	}
	char** shipPlacement(char** field, char* crd)
	{
		int i = int(crd[0]) - 65, j = int(crd[1]) - 48;
		field[i][j] = '#';
		return field;
	}

	friend class System;
};

class AI : public Player
{
private:
	Field field;
	char** fieldFill(char** field)
	{
		srand(time(NULL));
		int shipCount = 1;
		while (shipCount <= 10)
		{
			if (shipCount == 1)
			{
				char* crd1 = new char[2];
				crd1[0] = (rand() % 10) + 65;
				crd1[1] = (rand() % 10) + 48;
				char* crd2 = new char[2];
				crd2[0] = (rand() % 10) + 65;
				crd2[1] = (rand() % 10) + 48;
				int axis = rand() % 2;
				if (validPlacement(field, crd1, crd2, axis, 4))
				{
					shipCount++;
					field = shipPlacement(field, crd1, crd2, axis, 4);
				}
				else
				{
					continue;
				}
			}
			else if (shipCount == 2 || shipCount == 3)
			{
				char* crd1 = new char[2];
				crd1[0] = (rand() % 10) + 65;
				crd1[1] = (rand() % 10) + 48;
				char* crd2 = new char[2];
				crd2[0] = (rand() % 10) + 65;
				crd2[1] = (rand() % 10) + 48;
				int axis = rand() % 2;
				if (validPlacement(field, crd1, crd2, axis, 3))
				{
					shipCount++;
					field = shipPlacement(field, crd1, crd2, axis, 3);
				}
				else
				{
					continue;
				}
			}
			else if (shipCount >= 4 && shipCount <= 6)
			{
				char* crd1 = new char[2];
				crd1[0] = (rand() % 10) + 65;
				crd1[1] = (rand() % 10) + 48;
				char* crd2 = new char[2];
				crd2[0] = (rand() % 10) + 65;
				crd2[1] = (rand() % 10) + 48;
				int axis = rand() % 2;
				if (validPlacement(field, crd1, crd2, axis, 2))
				{
					shipCount++;
					field = shipPlacement(field, crd1, crd2, axis, 2);
				}
				else
				{
					continue;
				}
			}
			else
			{
				char* crd = new char[2];
				crd[0] = (rand() % 10) + 65;
				crd[1] = (rand() % 10) + 48;
				if (validPlacement(field, crd))
				{
					shipCount++;
					field = shipPlacement(field, crd);
				}
				else
				{
					continue;
				}
			}
		}
		return field;
	}
public:
	friend class System;
};

class System
{
private:
	fstream stats;
public:
	void menu()
	{
		int action;
		system("cls");
		cout << "_________________________" << endl;
		cout << "       Морской Бой       " << endl;
		cout << "                         " << endl;
		cout << "1. Игрок Против Игрока" << endl;
		cout << "2. Игрок Против ИИ" << endl;
		cout << "3. Статистика" << endl;
		cin >> action;
		if (action == 1) MannVsMann();
		else if (action == 2) MannVsMachine();
		else if (action == 3) Stat();
		else
		{
			cout << "Неверный ввод.";
			Sleep(5000);
			menu();
		}
	}

	bool hitOrMiss(char** fieldFull, int shotI, int shotJ)
	{
		if (fieldFull[shotI][shotJ] == '~')
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	int* randomShot(char** fieldFull)
	{
		int* shotCrd = new int[2];
		while (true)
		{
			int i = rand() % 10, j = rand() % 10;
			if (fieldFull[i][j] != 'x' && fieldFull[i][j] != '*')
			{
				shotCrd[0] = i;
				shotCrd[1] = j;
				break;
			}
		}
		return shotCrd;
	}
	int* smartShot(char** fieldFull, int* prevShot)
	{
		int* nextShot = prevShot;
		while (true)
		{
			int direction = rand() % 4;
			if ((direction == 0) && (prevShot[0] + 1 < 10))
			{
				nextShot[0]++;
				return nextShot;
			}
			else if ((direction == 1) && (prevShot[0] - 1 >= 0))
			{
				nextShot[0]--;
				return nextShot;
			}
			else if ((direction == 2) && (prevShot[1] + 1 < 10))
			{
				nextShot[1]++;
				return nextShot;
			}
			else if ((direction == 3) && (prevShot[1] - 1 >= 0))
			{
				nextShot[1]--;
				return nextShot;
			}
			else
			{
				continue;
			}
		}
	}

	int statSearch(string name)
	{
		stats.open("C:\\Users\\alex\\Source\\repos\\Project3\\statistics.txt");
		string lineFull;
		string lineName = "";
		int lineI = 0;
	    while (name != lineName)
	    {
			lineI++;
			getline(stats, lineName, '|');
			getline(stats, lineFull);
			if (lineI >= 100)
			{
				lineI = 0;
				break;
			}
		}
		stats.close();
		return lineI;
	}
	void statAdd(string name, int wins, int loses)
	{
		char winsChr = char(wins + 48);
		char losesChr = char(loses + 48);
		stats.open("C:\\Users\\alex\\Source\\repos\\Project3\\statistics.txt");
		stats << name << "|" << winsChr << "|" << losesChr << endl;
		stats.close();
	}
	void statChange(string name, int addWin, int addLoss)
	{
		int lineI = statSearch(name);
		stats.open("C:\\Users\\alex\\Source\\repos\\Project3\\statistics.txt");
		if (lineI == 0)
		{
			statAdd(name, addWin, addLoss);
		}
		else
		{
			string emptyStr;
			char chr;
			for (int i = 1; i < lineI; i++)
			{
				getline(stats, emptyStr);
			}
			getline(stats, emptyStr, '|');

			stats.get(chr);

			int pos = stats.tellg();
			stats.seekg(pos);
			stats.get(chr);
			int wins = int(chr);
			stats.seekg(pos);
			stats.put(char(wins + addWin));

			stats.get(chr);

			pos = stats.tellg();
			stats.get(chr);
			int losses = int(chr);
			stats.seekg(pos);
			stats.put(char(losses + addLoss));
		}
		stats.close();
	}

	void MannVsMann()
	{
		Player human1;
		system("cls");
		cout << "Введите имя: ";
		cin >> human1.name;
		human1.field.fieldFull = human1.fieldFill(human1.field.fieldFull);
		Player human2;
		cout << "Введите имя: ";
		cin >> human2.name;
		human2.field.fieldFull = human2.fieldFill(human2.field.fieldFull);
		while (!human1.victory && !human2.victory)
		{
			bool hit = true;
			do
			{
				bool hit = false;
				system("cls");
				cout << "Ход игрока " << human1.name << endl << endl;
				cout << "Поле противника:" << endl;
				graphic(human2.field.fieldCovered);
				cout << "_____________________" << endl;
				cout << "_____________________" << endl;
				cout << "Ваше поле:" << endl;
				graphic(human1.field.fieldFull);
				cout << "_____________________" << endl;
				char* shotCrd1 = new char[2];
				cout << "Введите координаты(формат А1, латиница) выстрела: ";
				cin >> shotCrd1;
				hit = hitOrMiss(human2.field.fieldFull, int(shotCrd1[0]) - 65, int(shotCrd1[1]) - 48);
				human2.field = fieldChange(human2.field, int(shotCrd1[0]) - 65, int(shotCrd1[1]) - 48, hit);
				
			} while(hit);

			if (human2.field.shipTileCount == 0) human1.victory = true;
			if (human1.victory)
			{
				break;
			}

			do
			{
				hit = false;
				system("cls");
				cout << "Ход игрока " << human2.name << endl << endl;
				cout << "Поле противника:" << endl;
				graphic(human1.field.fieldCovered);
				cout << "_____________________" << endl;
				cout << "_____________________" << endl;
				cout << "Ваше поле:" << endl;
				graphic(human2.field.fieldFull);
				cout << "_____________________" << endl;
				char* shotCrd2 = new char[2];
				cout << "Введите координаты(формат А1, латиница) выстрела: ";
				cin >> shotCrd2;
				hit = hitOrMiss(human1.field.fieldFull, int(shotCrd2[0]) - 65, int(shotCrd2[1]) - 48);
				human1.field = fieldChange(human1.field, int(shotCrd2[0]) - 65, int(shotCrd2[1]) - 48, hit);
				if (human1.field.shipTileCount == 0) human2.victory = true;
			} while (hit);
		}
	}
	void MannVsMachine()
	{
		Player human;
		system("cls");
		cout << "Введите имя: ";
		cin >> human.name;
		human.field.fieldFull = human.fieldFill(human.field.fieldFull);
		AI ai;
		ai.field.fieldFull = ai.fieldFill(ai.field.fieldFull);
		while (!human.victory && !ai.victory)
		{
			bool hit;
			hit = false;
			do
			{
				system("cls");
				cout << "Ход игрока " << human.name << endl << endl;
				cout << "Поле противника:" << endl;
				graphic(ai.field.fieldCovered);
				cout << "_____________________" << endl;
				cout << "_____________________" << endl;
				cout << "Ваше поле:" << endl;
				graphic(human.field.fieldFull);
				cout << "_____________________" << endl;
				char* shotCrd1 = new char[2];
				cout << "Введите координаты(формат А1, латиница) выстрела: ";
				cin >> shotCrd1;
				hit = hitOrMiss(ai.field.fieldFull, int(shotCrd1[0]) - 65, int(shotCrd1[1]) - 48);
				ai.field = fieldChange(ai.field, int(shotCrd1[0]) - 65, int(shotCrd1[1]) - 48, hit);
			} while (hit);

			if (ai.field.shipTileCount == 0) human.victory = true;
			if (human.victory)
			{
				break;
			}

			hit = false;
			int* shotCrd2 = randomShot(human.field.fieldFull);
			do
			{
				system("cls");
				cout << "Ход противника" << endl << endl;
				cout << "Поле противника:" << endl;
				graphic(ai.field.fieldCovered);
				cout << "_____________________" << endl;
				cout << "_____________________" << endl;
				cout << "Ваше поле:" << endl;
				graphic(human.field.fieldFull);
				cout << "_____________________" << endl;
				cout << "Введите Y, чтобы компъютер совершил выстрел: ";
				char Y;
				cin >> Y;
				if (!hit)
				{
					shotCrd2 = randomShot(human.field.fieldFull);
				}
				else
				{
					shotCrd2 = smartShot(human.field.fieldFull, shotCrd2);
				}
				hit = hitOrMiss(human.field.fieldFull, shotCrd2[0], shotCrd2[1]);
				human.field = fieldChange(human.field, shotCrd2[0], shotCrd2[1], hit);
			} while (hit);
			if (human.field.shipTileCount == 0) ai.victory = true;
		}
		if (human.victory)
		{
			system("cls");
			cout << "__________________________" << endl;
			cout << "       Вы победили!       " << endl;
			cout << "__________________________" << endl;

		}
	}
	void Stat()
	{
		system("cls");
		cout << "__________________________" << endl;
		cout << "        Статистика        " << endl;
		cout << "__________________________" << endl;
		cout << "Имя|Победы|Поражения" << endl;
		string line;
		stats.open("C:\\Users\\alex\\Source\\repos\\Project3\\statistics.txt");
		while (getline(stats, line))
		{
			cout << line << endl;
		}
		stats.close();
	}
};

void main()
{
	setlocale(LC_ALL, "rus");
	System game;
	game.statChange("a", 1, 1);
	game.menu();
}