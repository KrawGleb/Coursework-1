#include "Header.h"

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
	cout << "Популярность(Количество людей или окупаемость +/-): " << endl;
	string temp;
	cin >> temp;
	if (temp[0] == '+' || temp[0] == '-')
	{
		newMonument->popularity.isPayback = temp[0];
	}
	else
		newMonument->popularity.peopleCount = atoi(temp.c_str());

	cout << "Эра памятника: " << endl;
	cout << "1. Каменный век" << endl;
	cout << "2. Средневековье" << endl;
	cout << "3. Современность" << endl;
	int era;
	cin >> era;
	switch (era)
	{
	case StoneAge:
		newMonument->era = StoneAge;
		break;
	case MiddleAges:
		newMonument->era = MiddleAges;
		break;
	case Modernity:
		newMonument->era = Modernity;
		break;
	}

	return newMonument;
}

void menu(int& N, monument** monuments, string& path)
{
	int answer = 0;
	cout << "Меню: " << setw(70) << right << "Сейчас вы работаете с файлом:  " << path << endl;
	cout << "1. Добавить новый памятник" << endl;
	cout << "2. Показать весь список" << endl;
	cout << "3. Изменить элемент" << endl;
	cout << "4. Удалить элемент" << endl;
	cout << "5. Сохранить изменения" << endl;
	cout << "6. Вставить после выбранного элемента" << endl;
	cout << "7. Вставить перед выбранным элементом" << endl;
	cout << "8. Заменить элемент" << endl;
	cout << "9. Загрузить из файла" << endl;
	cout << "10. Изменить целевой файл" << endl;

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
		edit(N, monuments, path);
		break;
	case Remove:
		remove(N, monuments, path);
		break;
	case Save:
		save(N, monuments, path);
		break;
	case InsertAfter:
		insert_after(N, monuments, path);
		break;
	case InsertBefore:
		insert_before(N, monuments, path);
		break;
	case Replace:
		replace(N, monuments, path);
		break;
	case Backup:
		backup(N, monuments, path);
		break;
	case EditPath:
		editPath(path);
		break;
	case Exit:
		exit(1);
		break;
	default:
		break;
	}
}


void backup(int& N, monument** monuments, string& path)
{
	/*
	* Структура файла:
	* Название
	* Год
	* Стоимость
	* Эра (перечисление)
	* Популярность (объединение)
	*/
	if (path == "_________")
	{
		editPath(path);
	}
	cout << "Загрузка из файла..." << endl;
	int eraNum = -1;
	N = 0;
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
		while (getline(input, temp))
		{
			try
			{
				monument* nextMonument = new monument;

				nextMonument->name = temp;
				input >> nextMonument->year;
				input >> nextMonument->cost;
				input >> eraNum;
				nextMonument->era = define_era(eraNum);
				getline(input, temp);
				getline(input, temp);
				if (temp == "+" || temp == "-")
				{
					nextMonument->popularity.isPayback = temp[0];
				}
				else
					nextMonument->popularity.peopleCount = atoi(temp.c_str());

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
		ofstream file(path);
		file.close();
		cout << "Такого файла не существовало. Загрузка не завершена \nФайл был создан" << endl;
		return;
	}
	input.close();
	cout << "Загрузка завершена!" << endl;
	return;
}

void save(int& N, monument** monuments, string& path)
{
	/*
	* Структура файла:
	* Название
	* Год
	* Стоимость
	* Эра (перечисление)
	* Популярность (объединение)
	*/
	if (path == "_________")
	{
		editPath(path);
	}
	cout << "Сохранение..." << endl;
	ofstream output;
	output.open(path, ios::trunc);
	if (output.is_open())
	{
		for (int i = 0; i < N; i++)
		{
			output << monuments[i]->name << endl;
			output << monuments[i]->year << endl;
			output << monuments[i]->cost << endl;
			output << monuments[i]->era << endl;
			if (i != N - 1)
			{
				if (monuments[i]->popularity.isPayback == '+' || monuments[i]->popularity.isPayback == '-')
					output << monuments[i]->popularity.isPayback << endl;
				else
					output << monuments[i]->popularity.peopleCount << endl;
			}
			else
			{
				if (monuments[i]->popularity.isPayback == '+' || monuments[i]->popularity.isPayback == '-')
					output << monuments[i]->popularity.isPayback;
				else
					output << monuments[i]->popularity.peopleCount;
			}
		}
	}
	else
	{
		cout << "Ошибка открытия файла!" << endl;
	}
	output.close();
	cout << "Сохранено!" << endl;
	return;
}

void editPath(string& path)
{
	getchar();
	cout << "Введите имя файла(без .txt): " << endl;
	string temp;
	getline(cin, temp);
	temp += ".txt";
	path = temp;

	return;
}

void print(int& N, monument** monuments)
{
	cout << "#  " << setw(30) << left << "Название" << "|" << setw(15) << "Год открытия" << "|" << setw(25) << "Стоимость содержания" << "|" << setw(25) << "Окупаемость/Кол-во людей |" << setw(15) << "Эра" << "|" << endl;
	cout << "_________________________________|_______________|_________________________|_________________________|_______________|" << endl;
	for (int i = 0; i < N; i++)
	{
		if (monuments[i]->popularity.isPayback == '+' || monuments[i]->popularity.isPayback == '-')
		{
			string temp;
			if (monuments[i]->popularity.isPayback == '+')
				temp = "Окупается";
			else
				temp = "Не окупается";
			cout << i + 1 << ". " << setw(30) << left << monuments[i]->name << "|" << setw(15) << monuments[i]->year << "|" << setw(25) << monuments[i]->cost << "|" << setw(5) << " " << setw(20) << temp << "|" << setw(15) << convert_eraEnumToStr(monuments[i]->era) << setw(5) << "|" << endl;
		}
		else
			cout << i + 1 << ". " << setw(30) << left << monuments[i]->name << "|" << setw(15) << monuments[i]->year << "|" << setw(25) << monuments[i]->cost << "|" << setw(9) << " " << setw(16) << monuments[i]->popularity.peopleCount << "|" << setw(15) << convert_eraEnumToStr(monuments[i]->era) << setw(5) << "|" << endl;
		cout << "_________________________________|_______________|_________________________|_________________________|_______________|" << endl;
	}
}


void add(int& N, monument** monuments)
{
	// backup(N, monuments);
	monuments[N] = new_monument();
	N++;
	return;
}

void edit(int& N, monument** monuments, string& path)
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
		save(N, monuments, path);

	return;
}

void remove(int& N, monument** monuments, string& path)
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
		save(N, monuments, path);

	return;
}


void insert_after(int& N, monument** monuments, string& path)
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
		save(N, monuments, path);

	return;
}

void insert_before(int& N, monument** monuments, string& path)
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
		save(N, monuments, path);

	return;
}

void replace(int& N, monument** monuments, string& path)
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
		save(N, monuments, path);
}

eraEnum define_era(int eraNum)
{
	switch (eraNum)
	{
	case StoneAge:
		return StoneAge;
	case MiddleAges:
		return MiddleAges;
	case Modernity:
		return Modernity;
	default:
		return NotFound;
	}
}

string convert_eraEnumToStr(eraEnum era)
{
	switch (era)
	{
	case StoneAge:
		return "Каменный век";
		break;
	case MiddleAges:
		return "Средневековье";
		break;
	case Modernity:
		return "Современность";
		break;
	case NotFound:
		return "Не определено";
		break;
	}
}