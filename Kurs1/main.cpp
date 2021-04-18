#include "Header.h"

int main()
{
	char path[] = "monuments.txt";
	const int size = 100;
	int N = 0;
	// monument* monuments = new monument[100];
	monument **monuments = new monument*[100];
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//backup(N, monuments);
	backup(N, monuments);
	while (true)
	{
		menu(N, monuments);
		system("pause");
		system("cls");
	}

	return 0;
}
