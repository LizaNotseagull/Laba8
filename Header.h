#pragma once
#ifndef FUNC // Чтобы дважды не включалось
#define FUNC

#include <fstream>
#include <string>

void N_1();
void N_2();
void N_3();

// Функция для чтения данных из файла
void readFromFile(const std::string& filename, int& itemsCount, int& minWeight, int*& weight, int*& tax);
// Функция для заполнения таблицы
void FillTable(int itemsCount, int totalWeight, int* weight, int* tax, long long*& minTax, int*& prevItem);
// Функция для поиска лучшего решения
bool findBest(int minWeight, int totalWeight, long long* minTax, long long& minTaxFound, int& bestWeight);
// Функция для восстановления выбранных предметов
void reconstItems(int bestWeight, int itemsCount, int* prevItem, int* weight, int*& selected, int& selectedCount);
// Функция для вычисления суммарного веса и налога
void weightNtax(int* selected, int selectedCount, int* weight, int* tax, int& sumWeight, long long& sumTax, int*& numbers);
// Функция для вывода результатов
void printResults(int* numbers, int selectedCount, int sumWeight, long long sumTax);

// Функция для чтения данных из файла
bool readFromFile(const std::string& filename, int& n, int**& board);
// Функция для выделения памяти и инициализации матрицы
int** MatrixMinSum(int n);
// Функция для выделения памяти и инициализации матрицы символов
char** MatrixPath(int n);
// Функция для заполнения таблицы динамического программирования
void fillTable(int n, int** board, int** Table, char** path);
// Функция для восстановления пути короля
std::string KingWayRestore(int n, char** path);
// Функция для записи результата в файл
void writeResultToFile(const std::string& filename, int minSum, const std::string& path);
// Функция для освобождения памяти
void freeMatrix(int** matrix, int n);
// Функция для освобождения памяти символьной матрицы
void freeCharMatrix(char** matrix, int n);

// Функция для чтения данных из файла
void readInput(const std::string& filename, int& K, int& N);
// Функция для выделения памяти для таблицы
double** createTable(int N);
// Функция для заполнения таблицы 
void fillTable(int K, int N, double** Table);
// Функция для вычисления результата (суммы всех чисел длины N)
double calculateResult(int N, double** Table);
// Функция для записи результата в файл
void writeResultToFile(const std::string& filename, double result);
// Функция для освобождения памяти
void freeTable(double** Table, int N);

#endif