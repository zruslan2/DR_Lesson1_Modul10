#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <string.h>
#include "Struct.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void yellow()
{
	SetConsoleTextAttribute(hConsole, 14);
}

void white()
{
	SetConsoleTextAttribute(hConsole, 15);
}

void red()
{
	SetConsoleTextAttribute(hConsole, 12);
}

void green()
{
	SetConsoleTextAttribute(hConsole, 11);
}

char menu() //меню
{
	char nm;
	green();
	printf("Выберите пункт меню\n");
	white();
	printf("а) Показать количество свободных мест\n");
	printf("b) Показать список пустых свободных мест\n");
	printf("с) Показать алфавитный список занятых мест\n");
	printf("d) Назначить пассажиру место\n");
	printf("е) Удалить назначение места\n");
	printf("f) Выйти из программы\n");
	scanf("%c", &nm);
	return nm;
}

int cfseat(struct seat *par) //количество свободных мест
{
	int count=12;
	for (int i = 0; i < 12; i++)
	{
		if (par[i].reserve == true)count--;
	}
	return count;
}

void cfs(struct seat *par)//список свободных мест
{
	int f=0;
	for (int i = 0; i < 12; i++)
	{
		if (par[i].reserve == false)printf("%c - свободно\n", par[i].number);
		else f++;
	}
	red();
	if (f == 12)printf("Свободных мест нет((\n");
	white();
}

int crs(struct seat *par)//список занятых мест
{
	int f = 0;
	for (int i = 0; i < 12; i++)
	{
		if (par[i].reserve == true)
		{
			/*printf("Место %c\n", par[i].number);*/
			printf("Место %c - %s %s\n", par[i].number, par[i].sname, par[i].fname);
		}
		else f++;
	}
	yellow();
	if (f == 12)
	{
		printf("Все места свободны\n");
		return 0;
	}
	white();
	return f;
}

void res(struct seat *par)//резервирование места
{
	char s='a';	
	int m;
	bool free = false;	
	do
	{
		yellow();
		printf("Выберите свободное место\n");
		white();
		cfs(par);
		s = toupper(getch());
		if (s <= '@' || s >= 'M')printf("\nТакого места нет (((\n");
		for (int i = 0; i < 12; i++)
		{
			if (par[i].number == s&&par[i].reserve == false)
			{
				free = true;
				m = i;
			}
			else if (par[i].number == s&&par[i].reserve == true)
			{
				printf("Извините данное место занято\n");
				free = false;
				m = i;
			}
		}
	} while (s <= '@' || s >= 'M'||free==false);
		
	yellow();
	printf("Вы выбрали место - %c\n", s);
	white();
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("Введите ваше имя "); scanf("%s", par[m].fname);
	printf("Введите вашу фамилию "); scanf("%s", par[m].sname);
	par[m].reserve = true;
}

void deres(struct seat *par)
{
	char name[25], sname[25];
	bool r = false;
	bool s = false;
	char m;	
	int a=0;
	if (cfseat(par) != 12)
	{
		do
		{
			yellow();
			printf("Выберите место\n");
			white();
			crs(par);			
			m = toupper(getch());
			for (int i = 0; i < 12; i++)
			{
				if (par[i].number == m)
				{
					a = i;
					break;
				}
			}
			if (par[a].reserve == false)
			{
				r = false;
				printf("Данное место незарезервированно\n");
			}
			else if (par[a].reserve == true) r = true;
		} while (r != true);
		printf("Введите ваше имя "); scanf("%s", &name);
		printf("Введите вашу фамилию "); scanf("%s", &sname);
		if (stricmp(name, par[a].fname) == 0 && stricmp(sname, par[a].sname) == 0)s = true;
		else s = false;		
		if (s == true)
		{
			par[a].reserve = false;
		}
	}
}