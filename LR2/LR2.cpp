﻿//1.1 Реализовать алгоритм сортировки слиянием.
//1.2 Доработать алгоритм таким образом, чтоб можно было обойтись одним дополнительным массивом на всю программу
//1.3 Реализовать алгоритм сортировки слиянием без рекурсии.
//1.4 Реализовать алгоритм быстрой сортировки
//1.5.Предложить выбор разделяющего элемента


#include <iostream>
using namespace std;

// Прототипы функций
void merge(int*, int*, int, int); // слияние
void mergeSort(int*, int); // сортировка слияние
void mergeSort_Remastered(int*, int); // сортировка слияние ++
void quickSort(int*, int, int); // быстрая сортировка
void quickSort_Remastered(int*, int, int); // быстрая сортировка ++
int split(int*, int, int); // разделить (быстрая сортировка)
void countSort(int*, int, int); // сортировка подсчетом
void digitSort(int*, int); // цифровая сортировка
void bucketSort(float*, int); // карманная сортировка
int getMax(int*, int); // функция по поиску максимального элемента в массиве
void randArr(int*, int, int); // Заполнение массива случайными элементами
void randArr(float*, int, int); // Заполнение массива случайными элементами
void printArr(int*, int); // Печать массива
void printArr(float*, int); // Печать массива для float
void swap(int& a, int& b); // Обмена элементов массива

// Связанный список
struct List
{
	float key;
	List* next;
};

int main()
{
	const int n = 10;
	int a[n] = {0};
	int k = 100;

	// сортировка слияянием
	cout << "Original Data\n";
	randArr(a, n, k);
	printArr(a, n);
	mergeSort(a, n);
	cout << "Merge sort\n";
	printArr(a, n);
	
	// сортировка слиянием ++
	randArr(a, n, k);
	mergeSort_Remastered(a, n);
	cout << "Merge sort Remastered\n";
	printArr(a, n);

	// быстрая сортировка
	randArr(a, n, k);
	quickSort(a, 0, n - 1);
	cout << "Quick sort\n";
	printArr(a, n);

	// быстрая сортировка ++
	randArr(a, n, k);
	quickSort_Remastered(a, 0, n - 1);
	cout << "Quick sort Remastered\n";
	printArr(a, n);

	// сортировка подсчетом
	randArr(a, n, k);
	countSort(a, n, k);
	cout << "Count sort\n";
	printArr(a, n);

	// цифровая сортировка
	randArr(a, n, k);
	digitSort(a, n);
	cout << "Digit sort\n";
	printArr(a, n);

	float arr[10];
	cout << "Bucket sort\n";
	randArr(arr, n, k);
	//printArr(arr, n);
	bucketSort(arr, n);
	printArr(arr, n);
}

// Слияние отсортированных массивов
void merge(int* a, int* b, int n, int m)
{
	int i = 0, j = 0;
	int k = 0;

	int* temp = (int*)malloc((n + m) * sizeof(int));

	while (i < n or j < m)
	{
		if (j == m or (i < n and a[i] <= b[j]))
			temp[k++] = a[i++];
		else
			temp[k++] = b[j++];
	}

	for (int i = 0; i < n + m; i++)
		a[i] = temp[i];

	free(temp);
}

// Сратировка слиянием
void mergeSort(int* a, int n)
{
	if (n > 1)
	{
		int mid = n / 2;
		int* left = a;
		int* right = a + mid;

		mergeSort(left, mid);
		mergeSort(right, n - mid);

		merge(left, right, mid, n - mid);
	}
}

// Сортировка слиянием ++
void mergeSort_Remastered(int* a, int n)
{
	int* temp = (int*)malloc(n * sizeof(int)); // дополнительный массив

	for (int step = 1; step < n; step *= 2)
	{
		int k = 0;    // индекс результирующего массива

		int left = 0;      // левая граница участка
		int mid = left + step;  // середина участка
		int right = left + step * 2;  // правая граница участка
		do
		{
			// сортируемый участок не выходит за границы последовательности
			if (mid > n)
				mid = n;
			if (right > n)
				right = n;

			int i = left, j = mid; // индексы сравниваемых элементов

			while (i < mid || j < right)
			{
				if (j == right || (i < mid && a[i] <= a[j]))
					temp[k++] = a[i++];
				else
					temp[k++] = a[j++];
			}

			left += step * 2; // перемещаемся на следующий сортируемый участок
			mid += step * 2;
			right += step * 2;
		} while (left < n); // пока левая граница сортируемого участка - в пределах последоватльности

		for (int i = 0; i < n; i++) // переносим сформированный массив обратно в a
			a[i] = temp[i];
	}

	free(temp);
}


// Быстрая сортировка
void quickSort(int* a, int left, int right)
{
	if (right <= left)
		return;
	int m = split(a, left, right);

	quickSort(a, left, m - 1);
	quickSort(a, m + 1, right);
}

// Разделение массива по элементу
int split(int* a, int left, int right)
{
	int x = (a[left] + a[right]) / 2;
	int j = left - 1;
	
	for (int i = left; i < right; i++)
	{
		if (a[i] <= x)
			swap(a[i], a[++j]);
	}
	
	swap(a[++j], a[right]);
	return j;
}

// Быстрая сортировка ++
void quickSort_Remastered(int* a, int left, int right)
{
	int i = left; // индекс левая граница участка
	int j = right; // индкес правая граница участка
	int x = a[(left + right) / 2]; //элемент из середины учатска
	
	while (a[i] < x) i++; // увеличиваем индекс левого элемента пока его элемент не будет больше x
	while (a[j] > x) j--; // уменьшаем индекс правого элемента пока его элемент не будет меньше x

	// если левый элемент больше правого, то меняем местами
	if (a[i] > a[j])
		swap(a[i], a[j]);

	// если левая граница меньше парвого индекса, то сортируем от левой границы до правого индекса
	if (left < j)
		quickSort_Remastered(a, left, j-1);
	// если левый индекс меньше правой границы, то сортируем от левого индкса до правой границы
	if (i < right)
		quickSort_Remastered(a, i+1, right);
}

// Сортировка подсчетом
void countSort(int* a, int n, int k)
{
	int* temp = (int*)malloc(sizeof(int) * n); // временный массив для отсортированных элементов
	int* C = (int*)malloc(sizeof(int) * ++k); // массив для подсчета элементов

	// Заполняем массив для подсчета элементов нулями
	for (int i = 0; i < k; i++)
		C[i] = 0;
	
	// Подсчитываем кол-во каждого элемента в массиве
	for (int i = 0; i < n; i++)
		C[a[i]]++;

	// Находим место каждого элемента в остортированном массиве
	for (int i = 1; i < k; i++)
		C[i] += C[i-1];

	// Записываем элементы в отсортированный массив
	for (int i = n - 1; i >= 0; i--)
	{
		temp[C[a[i]] - 1] = a[i];
		C[a[i]]--;
	}

	// Копируем элементы из временного масссива в основной
	for (int i = 0; i < n; i++)
		a[i] = temp[i];

	// Освобождаем память (press f временнму массиву)
	free(temp);
	free(C);
}

// Цифровая сортировка
void digitSort(int* a, int n)
{
	int max = getMax(a, n); // максимальный элемент
	int* temp = (int*)malloc(sizeof(int) * n); // временный массив

	// для каждого разряда чисел
	for (int e = 1; max / e > 0; e *= 10)
	{
		int digits[10] = {0};  // массив для подсчета кол-во цифр

		// подсчитываем количество чисел по каждому разряду
		for (int i = 0; i < n; i++)
			digits[(a[i] / e) % 10]++;
        
		// вычисляем положение чисел в итоговом массиве
		for (int i = 1; i < 10; i++)
			digits[i] += digits[i-1];

		// распределяем числа в итоговый массив
		for (int i = n - 1; i >= 0; i--)
		{
			temp[digits[(a[i] / e) % 10] - 1] = a[i];
			digits[(a[i] / e) % 10]--;
		}

		// копируем отсортированный массив в исходный
		for (int i = 0; i < n; i++)
			a[i] = temp[i];
	}

	free(temp);
}

// Карманная сортировка
void bucketSort(float* a, int len)
{
	// Создание карманов
	List** buckets = new List*[len];
	for (int i = 0; i < len; i++)
		buckets[i] = nullptr;

	// Заполнение карманов
	for (int i = 0; i < len; i++)
	{
		int bucketIndex = len * a[i]; // индекс кармана
		List* newBucket = new List{a[i], nullptr}; // создание нового элемента для кармана

		// Если карман пустой - записываем в него элемент
		if (buckets[bucketIndex] == nullptr)
			buckets[bucketIndex] = newBucket;
		else
		{
			List* head = buckets[bucketIndex]; // текущщий элемент кармана
			List* prev = nullptr; // предыдущий элемент кармана

			// Сортируем элемент для кайфа (пока не дошли до последнего и текущий небольше сортируемого элемента)
			while (head != nullptr && head->key < a[i])
			{
				prev = head; // предыдущий равен текущему
				head = head->next; // текущий переходит на следующий
			}

			// Если новый элемент - наименьший, ставим его на первое место
			if (prev == nullptr)
			{
				newBucket->next = buckets[bucketIndex];
				buckets[bucketIndex] = newBucket;
			}
			else
			{
				prev->next = newBucket;
				newBucket->next = head;
			}
		}
	}

	// Объединение элементов карманов
	int j = 0;
	for (int i = 0; i < len; i++)
	{
		// Проходим по всем элементам кармана и только потом переходим на следующий
		List* head = buckets[i];
		while (head != nullptr)
		{
			a[j++] = head->key;
			head = head->next;
		}
	}

	delete[] buckets;
}

// Функция по поиску максимального элемента в массиве
int getMax(int* a, int n)
{
	int max = a[0];
	for (int i = 1; i < n; i++)
		if (a[i] > max)
			max = a[i];
	return max;
}

// Заполнение массива случайными элементами
void randArr(int* a, int n, int k)
{
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % k;
	}
}

// Заполнение массива случайными элементами
void randArr(float* a, int n, int k)
{
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		a[i] = ((float)(rand() % k)) / k;
	}
}


// Печать массива
void printArr(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << '\t';
	}
	cout << '\n';
}

// Печать массива для float
void printArr(float* a, int len)
{
	for (int i = 0; i < len; i++)
		cout << a[i] << '\t';
	cout << '\n';
}

// Обмена элементов массива
void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
