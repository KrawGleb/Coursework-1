#include "Header.h"

monument* new_monument()
{
	HANDLE color_changer = GetStdHandle(STD_OUTPUT_HANDLE);
	monument* newMonument = new monument;

	cout << "Название памятника: " << endl;
	getchar();
	cin.getline(newMonument->name, 100);
	
	cout << "Год открытия: " << endl;
	newMonument->year = read_integer();

	cout << "Стоимость содержания: " << endl;
	newMonument->cost = read_integer();

	cout << "Популярность(Количество людей или окупаемость +/-): " << endl;
	string temp;
readPopularity:
	cin >> temp;
	if (temp[0] == '+' || temp[0] == '-')
	{
		newMonument->popularity.isPayback = temp[0];
	}
	else
	{
		for (int i = 0; i < temp.length(); i++)
		{
			if ((unsigned int)temp[i] - 48 < 0 || (unsigned int)temp[i] - 48 > 9)
			{
				red("Неверное представление данных");
				cout << "Попробуйте снова: " << endl;
				goto readPopularity;
			}
		}
		newMonument->popularity.peopleCount = atoi(temp.c_str());

	}

	cout << "Эра памятника: " << endl;
	cout << "1. Каменный век" << endl;
	cout << "2. Средневековье" << endl;
	cout << "3. Современность" << endl;
	int era;
readEra:
	era = read_integer();
	if (era < 1 || era > 3)
	{
		red("Неверное представление данных");
		cout << "Попробуйте снова: " << endl;
		goto readEra;
	}
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
	HANDLE color_changer = GetStdHandle(STD_OUTPUT_HANDLE);
	int answer = 0;
	cout << "Меню: " << setw(70) << right << "Сейчас вы работаете с файлом:  " << path << endl;
	cout << "1. Добавить новый памятник " << endl;
	cout << "2. Показать весь список" << endl;
	cout << "3. Изменить элемент" << endl;
	cout << "4. Удалить элемент" << endl;
	cout << "5. Вставить после выбранного элемента" << endl;
	cout << "6. Вставить перед выбранным элементом" << endl;
	cout << "7. Заменить элемент" << endl;
	cout << "8. Загрузить из файла" << endl;
	cout << "9. Изменить целевой файл" << endl;
	green("10. Сохранить изменения");
	red("0. Выход");

	cout << "Ваш выбор: ";
	answer = read_integer();

	if (answer < 1 || answer > 10)
	{
		red("Такой команды нет");
	}

	switch (answer)
	{

	case Add:
		add(N, monuments, path);
		break;
	case Print:
		display(N, monuments);
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
		edit_path(path);
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
		edit_path(path);
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
		red("Критическая ошибка открытия файла");
		system("pause");
		return;
	}

	if (input.is_open())
	{
		monument* nextMonument = new monument;
		while (input.getline(nextMonument->name, 100))
		{
			try
			{
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
				nextMonument = new monument;

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
		edit_path(path);
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

void edit_path(string& path)
{
	getchar();
	cout << "Введите имя файла(без .txt): " << endl;
	string temp;
	getline(cin, temp);
	temp += ".txt";
	path = temp;

	return;
}

void display(int& N, monument** monuments)
{
	// Шапка таблицы
	cout << "+----+-------------------------------+---------------+-------------------------+--------------------------+---------------+" << endl;
	cout << "| #  |" << setw(31) << left << " Название" << "|" << setw(15) << " Год открытия" << "|" << setw(25) << " Стоимость содержания" << "|" << setw(25) << " Окупаемость/Кол-во людей |" << setw(15) << " Эра" << "|" << endl;
	cout << "+----+-------------------------------+---------------+-------------------------+--------------------------+---------------+" << endl;

	if (N == 0)
	{
		cout << "| " << setw(51) << " " << setw(68) << "Тут пока пусто" << " |" << endl;
		cout << "+----+-------------------------------+---------------+-------------------------+--------------------------+---------------+" << endl;
		return;
	}

	// Содержание таблицы
	for (int i = 0; i < N; i++)
	{
		if (monuments[i]->popularity.isPayback == '+' || monuments[i]->popularity.isPayback == '-')
		{
			string temp;
			if (monuments[i]->popularity.isPayback == '+')
				temp = "Окупается";
			else
				temp = "Не окупается";
			cout << "| " << setw(3) << i + 1 << "| " << setw(30) << left << monuments[i]->name << "| " << setw(14) << monuments[i]->year << "| " << setw(24) << monuments[i]->cost << "| " << " " << setw(24) << temp << "| " << setw(14) << convert_eraEnumToStr(monuments[i]->era) << "|" << endl;
		}
		else
			cout << "| " << setw(3) << i + 1 << "| " << setw(30) << left << monuments[i]->name << "| " << setw(14) << monuments[i]->year << "| " << setw(24) << monuments[i]->cost << "| " << " " << setw(24) << monuments[i]->popularity.peopleCount << "| " << setw(14) << convert_eraEnumToStr(monuments[i]->era) << "|" << endl;

	}

	// Конец таблицы
	cout << "+----+-------------------------------+---------------+-------------------------+--------------------------+---------------+" << endl;
	return;
}


void add(int& N, monument** monuments, string& path)
{
	// backup(N, monuments);
	monuments[N] = new_monument();
	N++;

	cout << "Сохранить изменения?\n(Д)а / (Н)ет" << endl;
	getchar();
	char anws = getchar();
	if (anws == 'Д')
		save(N, monuments, path);

	return;
}

void edit(int& N, monument** monuments, string& path)
{
	if (N == 0)
	{
		cout << "Список пуст" << endl;
		return;
	}

	HANDLE color_changer = GetStdHandle(STD_OUTPUT_HANDLE);
	display(N, monuments);
	int index = 0;
	int era;
	string temp;
	cout << "Введите номер памятника: " << endl;
	cin >> index;
	cout << "Что нужно изменить: " << endl;
	cout << "1. Название" << endl;
	cout << "2. Год открытия" << endl;
	cout << "3. Стоимость содержания" << endl;
	cout << "4. Окупаемость/Кол-во людей" << endl;
	cout << "5. Эра" << endl;
	cout << "6. Поменять полностью" << endl;
	int answer = 0;
readAnswer:
	answer = read_integer();
	if (answer < 1 || answer > 7)
	{
		red("Такой опции нет");
		cout << "Попробуйте ещё раз: " << endl;
		goto readAnswer;
	}

	cout << "Новое значение: " << endl;
	switch (answer)
	{
	case 1:
		getchar();
		cin.getline(monuments[--index]->name, 100);
		break;
	case 2:
		monuments[--index]->year = read_integer();
		break;
	case 3:
		monuments[--index]->cost = read_integer();
		break;
	case 4:
	readPopularity:
		SetConsoleTextAttribute(color_changer, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cin >> temp;
		SetConsoleTextAttribute(color_changer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		if (temp[0] == '+' || temp[0] == '-')
		{
			monuments[--index]->popularity.isPayback = temp[0];
		}
		else
		{
			for (int i = 0; i < temp.length(); i++)
			{
				if ((unsigned int)temp[i] - 48 < 0 || (unsigned int)temp[i] - 48 > 9)
				{
					red("Неверное представление данных");
					cout << "Попробуйте снова: " << endl;
					goto readPopularity;
				}
			}
			monuments[--index]->popularity.peopleCount = atoi(temp.c_str());
		}
		break;
	case 5:
		cout << "1. Каменный век" << endl;
		cout << "2. Средневековье" << endl;
		cout << "3. Современность" << endl;
	readEra:
		era = read_integer();
		if (era < 1 || era > 3)
		{

			red("Неверное представление данных");
			cout << "Попробуйте снова: " << endl;
			goto readEra;
		}
		switch (era)
		{
		case StoneAge:
			monuments[--index]->era = StoneAge;
			break;
		case MiddleAges:
			monuments[--index]->era = MiddleAges;
			break;
		case Modernity:
			monuments[--index]->era = Modernity;
			break;
		}
		break;
	case 6:
		monuments[--index] = new_monument();
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
		return;
	}
	display(N, monuments);
	int index = 0;
	cout << "Введите номер памятника: " << endl;

readIndex:
	index = read_integer();
	if (index < 1 || index > N)
	{
		cout << "Нет записи под таким номером" << endl;
		goto readIndex;
	}

	cout << "Удаление..." << endl;
	for (int i = --index; i < N; i++)
	{
		monuments[i] = monuments[i + 1];
	}

	cout << "Запись под номером " << index + 1 << " удалена" << endl;
	N--;

	cout << "Сохранить изменения?\n(Д)а / (Н)ет" << endl;
	getchar();
	char anws = getchar();
	if (anws == 'Д')
		save(N, monuments, path);

	return;
}


void insert_after(int& N, monument** monuments, string& path)
{
	if (N == 0)
	{
		cout << "Список пуст" << endl;
		return;
	}
	display(N, monuments);
	int index = 0;
	cout << "Введите номер памятника: " << endl;
readIndex:
	index = read_integer();
	if (index < 1 || index > N)
	{
		cout << "Неверный номер" << endl;
		cout << "Попробуйте снова: " << endl;
		goto readIndex;
	}
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
	if (N == 0)
	{
		cout << "Список пуст" << endl;
		return;
	}
	display(N, monuments);
	int index = 0;
	cout << "Введите номер памятника: " << endl;
readIndex:
	index = read_integer();
	if (index < 1 || index > N)
	{
		cout << "Неверный номер" << endl;
		cout << "Попробуйте снова: " << endl;
		goto readIndex;
	}

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
	if (N == 0)
	{
		cout << "Список пуст" << endl;
		return;
	}
	display(N, monuments);
	int index = 0;
	cout << "Введите номер памятника: " << endl;
	
readIndex:
	index = read_integer();
	if (index < 1 || index > N)
	{
		red("Неверный индекс\nПопытайтесь снова: ");
		goto readIndex;
	}

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

int read_integer()
{
	string temp;
	HANDLE color_changer = GetStdHandle(STD_OUTPUT_HANDLE);
read:
	SetConsoleTextAttribute(color_changer, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cin >> temp;
	SetConsoleTextAttribute(color_changer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	for (int i = 0; i < temp.length(); i++)
	{
		if ((unsigned int)temp[i] - 48 < 0 || (unsigned int)temp[i] - 48 > 9)
		{
			red("Неверный формат");
			goto read;
		}
	}
	return atoi(temp.c_str());
}

void red(string text)
{
	HANDLE color_changer = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color_changer, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << text << endl;
	SetConsoleTextAttribute(color_changer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return;
}

void blue(string text)
{
	HANDLE color_changer = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color_changer, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << text << endl;
	SetConsoleTextAttribute(color_changer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return;
}

void green(string text)
{
	HANDLE color_changer = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color_changer, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << text << endl;
	SetConsoleTextAttribute(color_changer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return;
}