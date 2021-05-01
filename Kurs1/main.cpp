#include "Header.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	string path = "_________";

	const int size = 100;
	int N = 0;
	monument **monuments = new monument*[size];
	
	while (true)
	{
		menu(N, monuments, path);
		system("pause");
		system("cls");
	}

	return 0;
}
