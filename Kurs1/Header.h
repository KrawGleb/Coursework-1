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

struct monument
{
	string name;
	int year;
	long cost;
	popularityUnion popularity;
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
	Exit = 0
};


void menu(int& N, monument** monuments);
void print(int& N, monument** monuments);
void add(int& N, monument** monuments);
void remove(int& N, monument** monuments);
void save(int& N, monument** monuments);
void edit(int& N, monument** monuments);
void insert_after(int& N, monument** monuments);
void insert_before(int& N, monument** monuments);
void replace(int& N, monument** monuments);
void backup(int& N, monument** monuments);
struct monument* new_monument();

void backup(int& N, monument** monuments);
void save(int& N, monument** monuments);


#endif
#pragma once