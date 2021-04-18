#include "Header.h"

int main()
{
	string path = "_________";

	const int size = 100;
	int N = 0;
	monument **monuments = new monument*[size];
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	while (true)
	{
		menu(N, monuments, path);
		system("pause");
		system("cls");
	}

	return 0;
}
