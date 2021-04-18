#include "Header.h"

char path[99] = "monuments.txt";

monument* new_monument()
{
	monument* newMonument = new monument;
	cout << "Название памятника: " << endl;
	getchar();
	getline(cin, newMonument->name);
	cout << "Год открытия: " << endl;
	cin >> newMonument->year;
	cout << "Стоимость содержания: " << endl;
	cin >> newMonument->cost;

	return newMonument;
}

void menu(int& N, monument** monuments)
{
	int answer = 0;
	cout << "Меню: " << endl;
	cout << "1. Добавить новый памятинк" << endl;
	cout << "2. Показать весь список" << endl;
	cout << "3. Изменить элемент" << endl;
	cout << "4. Удалить элемент" << endl;
	cout << "5. Сохранить изменения" << endl;
	cout << "6. Вставить после выбранного элемента" << endl;
	cout << "7. Вставить перед выбранным элементом" << endl;
	cout << "8. Заменить элемент" << endl;
	cout << "0. Выход" << endl;
	cout << "Ваш выбор: ";
	cin >> answer;
	switch (answer)
	{
	case Add:
		add(N, monuments);
		break;
	case Print:
		print(N, monuments);
		break;
	case Edit:
		edit(N, monuments);
		break;
	case Remove:
		remove(N, monuments);
		break;
	case Save:
		save(N, monuments);
		break;
	case InsertAfter:
		insert_after(N, monuments);
		break;
	case InsertBefore:
		insert_before(N, monuments);
		break;
	case Replace:
		replace(N, monuments);
		break;
	case Exit:
		exit(1);
		break;
	default:
		break;
	}
}

void print(int& N, monument** monuments)
{
	cout << "#  " << setw(30) << left << "Название" << "|" << setw(15) << "Год открытия" << "|" << setw(25) << "Стоимость содержания" << "|" << endl;
	cout << "_________________________________|_______________|_________________________|" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << i + 1 << ". " << setw(30) << left << monuments[i]->name << "|" << setw(15) << monuments[i]->year << "|" << setw(25) << monuments[i]->cost << "|" << endl;
		cout << "_________________________________|_______________|_________________________|" << endl;
	}
}


void backup(int& N, monument** monuments)
{
	cout << "Загрузка из файла..." << endl;
	N = 0;
	string skip;
	ifstream input;
	string temp;

	try
	{
		input.open(path);
	}
	catch (const exception& exc)
	{
		cout << "Критическая ошибка открытия файла" << endl;
		system("pause");
		return;
	}
	if (input.is_open())
	{
		while (!input.eof())
		{
			try
			{
				monument* nextMonument = new monument;
				
				getline(input, nextMonument->name);
				input >> nextMonument->year;
				input >> nextMonument->cost;
				getline(input, skip);
				cout << nextMonument->name << endl;
				monuments[N] = nextMonument;
				N++;
			}
			catch (const exception& exc)
			{
				cout << "Ошибка чтения из файла" << endl;
				cout << exc.what() << endl;
				system("pause");
				return;
			}

		}
	}
	else
	{
		cout << "Ошибка открытия файла!" << endl;
		return;
	}
	input.close();
	cout << "Загрузка завершена!" << endl;
	system("pause");
	return;
}

void add(int& N, monument** monuments)
{
	backup(N, monuments);
	monuments[N] = new_monument();
	N++;
	return;
}

void edit(int& N, monument** monuments)
{
	print(N, monuments);
	int index = 0;
	cout << "Введите номер памятника: " << endl;
	cin >> index;
	cout << "Что нужно изменить: " << endl;
	cout << "1. Название" << endl;
	cout << "2. Год открытия" << endl;
	cout << "3. Стоимость содержания" << endl;
	int answer = 0;
	cin >> answer;
	cout << "Новое значение: " << endl;
	switch (answer)
	{
	case 1:
		getchar();
		getline(cin, monuments[--index]->name);
		break;
	case 2:
		cin >> monuments[--index]->year;
		break;
	case 3:
		cin >> monuments[--index]->cost;
		break;
	default:
		cout << "Ошибка изменения" << endl;
		break;
	}

	cout << "Сохранить изменения?\n(Д)а / (Н)ет" << endl;
	getchar();
	char anws = getchar();
	if (anws == 'Д')
		save(N, monuments);

	return;
}

void remove(int& N, monument** monuments)
{
	if (N == 0)
	{
		cout << "Список пуст" << endl;
		system("pause");
		return;
	}
	print(N, monuments);
	int index = 0;
	cout << "Введите номер памятника: " << endl;
	cin >> index;
	for (int i = --index; i < --N; i++)
	{
		monuments[i] = monuments[i + 1];
	}

	cout << "Сохранить изменения?\n(Д)а / (Н)ет" << endl;
	getchar();
	char anws = getchar();
	if (anws == 'Д')
		save(N, monuments);

	return;
}

void save(int& N, monument** monuments)
{
	ofstream output;
	output.open(path, ios::trunc);
	if (output.is_open())
	{
		for (int i = 0; i < N; i++)
		{
			output << monuments[i]->name << endl;
			output << monuments[i]->year << endl;
			if (i != N - 1)
			{
				output << monuments[i]->cost << endl;
			}
			else
			{
				output << monuments[i]->cost;
			}

		}
	}
	else
	{
		cout << "Ошибка открытия файла!" << endl;
	}

	return;
}

void insert_after(int& N, monument** monuments)
{
	print(N, monuments);
	int index = 0;
	cout << "Введите номер памятника: " << endl;
	cin >> index;

	for (int i = N + 1; i > index; i--)
	{
		monuments[i] = monuments[i - 1];
	}
	monuments[index] = new_monument();
	N++;

	cout << "Сохранить изменения?\n(Д)а / (Н)ет" << endl;
	getchar();
	char anws = getchar();
	if (anws == 'Д')
		save(N, monuments);

	return;
}

void insert_before(int& N, monument** monuments)
{
	print(N, monuments);
	int index = 0;
	cout << "Введите номер памятника: " << endl;
	cin >> index;

	for (int i = N + 1; i >= index; i--)
	{
		monuments[i] = monuments[i - 1];
	}
	monuments[--index] = new_monument();
	N++;

	cout << "Сохранить изменения?\n(Д)а / (Н)ет" << endl;
	getchar();
	char anws = getchar();
	if (anws == 'Д')
		save(N, monuments);

	return;
}

void replace(int& N, monument** monuments)
{
	print(N, monuments);
	int index = 0;
	cout << "Введите номер памятника: " << endl;
	cin >> index;

	monuments[--index] = new_monument();

	cout << "Сохранить изменения?\n(Д)а / (Н)ет" << endl;
	getchar();
	char anws = getchar();
	if (anws == 'Д')
		save(N, monuments);
}