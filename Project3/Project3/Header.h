using namespace std;

char** fieldCreate();
void graphic(char** field);

struct Field
{
	int shipcout = 10;
	char** fieldFull = fieldCreate();
	char** FieldCovered = fieldCreate();
};

class Player
{
private:
	string name;
	Field field;
	char** fieldFill(char** field);
public:
	bool victory;

	bool validPlacement(char** field, char* crd1, char* crd2, int axis, int shipSize);
	bool validPlacement(char** field, char* crd);
	bool validSurround(char** field, int i, int j);
	bool validCheck(char** field, int minI, int minJ, int maxI, int maxJ);

	char** shipPlacement(char** field, char* crd1, char* crd2, int axis, int shipSize);
	char** shipPlacement(char** field, char* crd);

	Player();
	
	friend class System;
};
class AI
{
private:
	Field field;
	char** fieldFill(char** field);
public:
	friend class System;
};
class System
{
public:
	void menu();

	bool hitOrMiss(char** fieldFull, int shotI, int shotJ);
	int* randomShot(char** fieldFull);

	void MannVsMann();
	void MannVsMachine();
	void Stat();
};