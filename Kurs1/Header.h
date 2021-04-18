#ifndef Header_H
#define Header_H

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <iomanip>

using namespace std;

union popularityUnion
{
	char isPayback;
	int peopleCount;
};

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
	Backup,
	EditPath,
	Exit = 0
};

enum eraEnum
{
	StoneAge = 1,
	MiddleAges,
	Modernity,
	NotFound = -1
};

struct monument
{
	string name;
	int year;
	long cost;
	popularityUnion popularity;
	eraEnum era;
};




// פאיכמגûי גגמה/גûגמה
void save(int& N, monument** monuments, string& path);
void backup(int& N, monument** monuments, string& path);
void editPath(string& path);

void menu(int& N, monument** monuments, string& path);


void print(int& N, monument** monuments);
void add(int& N, monument** monuments);
void remove(int& N, monument** monuments, string& path);

void edit(int& N, monument** monuments, string& path);
void insert_after(int& N, monument** monuments, string& path);
void insert_before(int& N, monument** monuments, string& path);
void replace(int& N, monument** monuments, string& path);

struct monument* new_monument();

eraEnum define_era(int eraNum);
string convert_eraEnumToStr(eraEnum era);

#endif
#pragma once