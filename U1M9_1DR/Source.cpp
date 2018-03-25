#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include "Struct.h"
#include "MyFunc.h"

void main()
{
	setlocale(LC_ALL, "Rus");	
	char r;
	seat seats[12];
	struct seat * pseats= seats;
	FILE*f;
	f=fopen("data.txt", "r");
	if (f == NULL)
	{
		for (int i = 0; i < 12; i++)
		{
			seats[i].number = (char)65 + i;
			seats[i].reserve = false;
			/*seats[i].fname = "";*/
			strcpy(seats[i].fname, "free");
			/*seats[i].sname = "B";*/
			strcpy(seats[i].sname, "free");
		}
	}
	else
	{
		for (int i = 0; i < 12; i++)
		{
			/*fscanf(f, "%c ", seats[i].number);*/
			seats[i].number = fgetc(f);
			/*fscanf(f, "%d ", seats[i].reserve);*/
			fscanf(f, "%d\n", &seats[i].reserve);
			fscanf(f, "%s ", seats[i].fname);
			/*fgets(seats[i].fname, 20, f);*/
			fscanf(f, "%s ", seats[i].sname);
			/*fgets(seats[i].sname, 20, f);*/
		}
		fclose(f);
	}
	
	while (true)
	{
		system("cls");
		r = menu();
		if (r == 'a')
		{
			int c;
			c = cfseat(pseats);
			system("cls");
			yellow();
			printf("Количество свободных мест - %d\n", c);
			white();
			printf("Вернутся в меню?\n");
			getch();
		}
		else if (r == 'b')
		{
			system("cls");
			cfs(pseats);
			printf("Вернутся в меню?\n");
			getch();
		}
		else if (r == 'c')
		{
			system("cls");
			crs(pseats);
			printf("Вернутся в меню?\n");
			getch();
		}
		else if (r == 'd')
		{
			system("cls");
			res(pseats);
			printf("Вернутся в меню?\n");
			getch();
		}
		else if (r == 'e')
		{
			system("cls");
			deres(pseats);
			printf("Вернутся в меню?\n");
			getch();
		}
		else if (r == 'f')
		{
			f = fopen("data.txt", "w");
			if (f == NULL)perror("Ошибка открытия файла");
			else
			{
				for (int i = 0; i < 12; i++)
				{
					fprintf(f, "%c ", seats[i].number);
					fprintf(f, "%d ", seats[i].reserve);
					fprintf(f, "%s ", seats[i].fname);
					fprintf(f, "%s ", seats[i].sname);
				}
				fclose(f);
			}
			break;
			system("exit");
		}
	}
	
}