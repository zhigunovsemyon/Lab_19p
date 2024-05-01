/*Записать в массив последовательно вводимые оценки
студентов по предмету «Программирование». Ввод прекратить при
вводе нуля. Определить средний балл в группе по предмету,
количество неудовлетворительных оценок и количество отличников.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

enum Bool{ false, true };
enum Errors { NOERRORS, MALLOC_FAIL };
#define LOWEST 2
#define HIGHEST 5

int GetFives(int* Grades, int count);
int GetBads(int* Grades, int count);
double GetAverage(int* Grades, int count);
int* FillGrades(int* count);
int GetGrade(int count);

int main(void)
{
	int count = 0;
	int* Grades = FillGrades(&count);
	if (NULL == Grades)
	{
		puts("Ошибка выделения памяти! Завершение работы!");
		return MALLOC_FAIL;
	}

	printf("\nОтличников в группе: %d\n", GetFives(Grades, count));
	printf("Неудовлетворительных оценок в группе: %d\n", GetBads(Grades, count));
	if (count)
		printf("Средняя оценка по группе: %.3lf\n", GetAverage(Grades, count));


	free(Grades);
	return NOERRORS;
}


/*Ввод правильной оценки по счёту count*/
int GetGrade(int count)
{
	int ret;
	do
	{
		printf("Оценка %d -го студента: ", count + 1);
		scanf("%d", &ret);
		if (ret >= LOWEST && ret <= HIGHEST)
			return ret;
		/*else*/ printf("Оценка должна быть в диапазоне от %d до %d\n", LOWEST, HIGHEST);
	} while (ret); //Если был введён 0,
	return ret;	//То ноль и возвращается
}

/*Создание указателя на массив с оценками количества count*/
int* FillGrades(int* count)
{
	int* Grades = NULL;
	do
	{
		int memAmount = (*count + 1) * sizeof(int);
		Grades = (int*)realloc(Grades, memAmount);
		if (!Grades)
		{
			return NULL;
		}

		Grades[*count] = GetGrade(*count);

		if (!Grades[*count])
			break;
		(*count)++;
	} while (true);

	return Grades;
}

/*Получение среднего арифметического оценок среди Grades из числа count*/
double GetAverage(int* Grades, int count)
{
	double ret = 0.0;
	for (int i = 0; i < count; i++)
		ret += Grades[i];

	return ret / count;
}

/*Получение числа неудовлетворительных оценок среди Grades из числа count*/
int GetBads(int* Grades, int count)
{
	int ret = 0;
	for (int i = 0; i < count; i++)
		if (Grades[i] == LOWEST)
			ret++;
	return ret;
}

/*Получение числа отличных оценок среди Grades из числа count*/
int GetFives(int* Grades, int count)
{
	int ret = 0;
	for (int i = 0; i < count; i++)
		if (Grades[i] == HIGHEST)
			ret++;
	return ret;
}
