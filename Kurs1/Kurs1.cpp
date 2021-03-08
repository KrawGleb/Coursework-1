#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <iomanip>

using namespace std;

void menu();
void print();
void add();
void remove();
void save();
void edit();
void insert_after();
void insert_before();
void replace();
void backup();
struct monument new_monument();


struct monument
{
	char name[100];
	int year;
	long cost;
} monuments[50];

enum commands
{
	Add = 1,
	Print,
	Edit,
	Remove,
	Save,
	InsertAfter,
	InsertBefore,
	Replace,
	Exit = 0
};

int N = 0;
char path[] = "monuments.txt";

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	backup();

	while (true)
	{
		menu();
		system("pause");
		system("cls");
	}

	return 0;
}

monument new_monument()
{
	monument newMonument;
	cout << "Название памятника: " << endl;
	getchar();
	cin.getline(newMonument.name, 100);
	cout << "Год открытия: " << endl;
	cin >> newMonument.year;
	cout << "Стоимость содержания: " << endl;
	cin >> newMonument.cost;

	return newMonument;
}

void menu()
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
		add();
		break;
	case Print:
		print();
		break;
	case Edit:
		edit();
		break;
	case Remove:
		remove();
		break;
	case Save:
		save();
		break;
	case InsertAfter:
		insert_after();
		break;
	case InsertBefore:
		insert_before();
		break;
	case Replace:
		replace();
		break;
	case Exit:
		exit(1);
		break;
	default:
		break;
	}
}

void print()
{
	cout << "#  " << setw(30) << left << "Название" << "|" << setw(15) << "Год открытия" << "|" << setw(25) << "Стоимость содержания" << "|" << endl;
	cout << "_________________________________|_______________|_________________________|" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << i + 1 << ". " << setw(30) << left << monuments[i].name << "|" << setw(15) << monuments[i].year << "|" << setw(25) << monuments[i].cost << "|" << endl;
		cout << "_________________________________|_______________|_________________________|" << endl;
	}
}

void backup()
{
	N = 0;
	ifstream input;
	input.open(path);

	if (input.is_open())
	{
		while (input.read((char*)&monuments[N++], sizeof(monument))) {}
		N--;
	}
	else
	{
		cout << "Ошибка открытия файла" << endl;
	}
	input.close();
}

void add()
{
	backup();
	N++;
	monuments[N] = new_monument();

	ofstream output;
	output.open(path, ofstream::app);
	if (output.is_open())
	{
		output.write((char*)&monuments[N], sizeof(monument));
		cout << "Готово!" << endl;
	}
	else
	{
		cout << "Ошибка записи в файл" << endl;
	}

	output.close();
	backup();
	return;
}

void edit()
{
	print();
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
		cin.getline(monuments[--index].name, 100);
		break;
	case 2:
		cin >> monuments[--index].year;
		break;
	case 3:
		cin >> monuments[--index].cost;
		break;
	default:
		cout << "Ошибка изменения" << endl;
		break;
	}

	cout << "Сохранить изменения?\n(Д)а / (Н)ет" << endl;
	getchar();
	char anws = getchar();
	if (anws == 'Д')
		save();

	return;
}

void remove()
{
	if (N == 0)
	{
		cout << "Список пуст" << endl;
		system("pause");
		return;
	}
	print();
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
		save();

	return;
}

void save()
{
	ofstream output;
	output.open(path, ios::trunc);
	if (output.is_open())
	{
		for (int i = 0; i < N; i++)
		{
			output.write((char*)&monuments[i], sizeof(monument));
		}
	}
	else
	{
		cout << "Ошибка открытия файла" << endl;
	}
	output.close();

	cout << "Изменения сохранены" << endl;

	return;
}

void insert_after()
{
	print();
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
		save();

	return;
}

void insert_before()
{
	print();
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
		save();

	return;
}

void replace()
{
	print();
	int index = 0;
	cout << "Введите номер памятника: " << endl;
	cin >> index;

	monuments[--index] = new_monument();

	cout << "Сохранить изменения?\n(Д)а / (Н)ет" << endl;
	getchar();
	char anws = getchar();
	if (anws == 'Д')
		save();
}