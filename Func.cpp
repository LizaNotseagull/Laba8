#include <iostream>
#include <string>
#include <fstream>
#include <clocale>
#include <iomanip>
#include "Header.h"

// Чтения из файла
void readFromFile(const std::string& filename, int& itemsCount, int& minWeight,
    int*& weight, int*& tax) {
    std::ifstream input(filename);

    if (!input.is_open()) {
        std::cout << "Ошибка открытия файла" << std::endl;
        exit(0);
    }

    input >> itemsCount >> minWeight;

    // Память для массивов
    weight = new int[itemsCount];
    tax = new int[itemsCount];

    for (int i = 0; i < itemsCount; i++) input >> weight[i];
    for (int i = 0; i < itemsCount; i++) input >> tax[i];

    input.close();
}

// Функция для заполнения таблицы
void FillTable(int itemsCount, int totalWeight, int* weight, int* tax,
    long long*& minTax, int*& prevItem) {
    const long long infinity = 1000000000000000000;

    // Инициализация массивов
    for (int i = 0; i <= totalWeight; i++) {
        minTax[i] = infinity;
        prevItem[i] = -1;
    }
    minTax[0] = 0;

    // Основной алгоритм
    for (int item = 0; item < itemsCount; item++) {
        for (int w = totalWeight; w >= weight[item]; w--) {
            if (minTax[w - weight[item]] != infinity &&
                minTax[w - weight[item]] + tax[item] < minTax[w]) {
                minTax[w] = minTax[w - weight[item]] + tax[item];
                prevItem[w] = item;
            }
        }
    }
}

// Функция для поиска лучшего решения
bool findBest(int minWeight, int totalWeight, long long* minTax,
    long long& minTaxFound, int& bestWeight) {
    minTaxFound = 1000000000000000000;
    bestWeight = -1;

    for (int w = minWeight + 1; w <= totalWeight; w++) {
        if (minTax[w] < minTaxFound) {
            minTaxFound = minTax[w];
            bestWeight = w;
        }
    }

    return (bestWeight != -1);
}

// Функция для восстановления выбранных предметов
void reconstItems(int bestWeight, int itemsCount, int* prevItem,
    int* weight, int*& slctd, int& slctdCount) {
    // Временный массив для хранения выбранных индексов
    int* tempSlctd = new int[itemsCount];
    bool* used = new bool[itemsCount]();

    int currWeight = bestWeight;
    slctdCount = 0;

    // Восстанавливаем цепочку выбранных предметов
    while (currWeight > 0 && prevItem[currWeight] != -1) {
        int idx = prevItem[currWeight];

        if (used[idx]) {
            std::cout << "Ошибка восстановления пути" << std::endl;
            delete[] tempSlctd;
            delete[] used;
            exit(0);
        }

        tempSlctd[slctdCount++] = idx;
        used[idx] = true;
        currWeight -= weight[idx];
    }

    // Копируем результаты в выходной массив
    slctd = new int[slctdCount];
    for (int i = 0; i < slctdCount; i++) {
        slctd[i] = tempSlctd[i];
    }

    delete[] tempSlctd;
    delete[] used;
}

// Функция для вычисления суммарного веса и налога
void weightNtax(int* slctd, int slctdCount, int* weight, int* tax,
    int& sumWeight, long long& sumTax, int*& num) {
    sumWeight = 0;
    sumTax = 0;

    num = new int[slctdCount];

    for (int i = 0; i < slctdCount; i++) {
        int idx = slctd[i];
        sumWeight += weight[idx];
        sumTax += tax[idx];
        num[i] = idx + 1;  // Нумерация с 1 для вывода
    }
}

// Функция для вывода результатов
void printResults(int* num, int slctdCount, int sumWeight, long long sumTax) {
    std::cout << "Порядковые номера вещей, которые нужно взять: ";
    for (int i = 0; i < slctdCount; i++) {
        std::cout << num[i];
        if (i < slctdCount - 1) std::cout << " ";
    }
    std::cout << std::endl;

    std::cout << "Суммарный вес: " << sumWeight << std::endl;
    std::cout << "Минимальный налог: " << sumTax << std::endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Функция для чтения данных из файла
bool readFromFile(const std::string& filename, int& n, int**& board) {
    std::ifstream input(filename);

    if (!input.is_open()) {
        std::cout << "Ошибка открытия файла " << filename << std::endl;
        return false;
    }

    input >> n;

    // Выделяем память для доски n x n
    board = new int* [n];
    for (int i = 0; i < n; i++) {
        board[i] = new int[n];
    }

    // Неприятности короля
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            input >> board[i][j];
        }
    }

    input.close();
    return true;
}

// Функция для выделения памяти
int** MatrixMinSum(int n) {
    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n]();  // Инициализируем нулями
    }
    return matrix;
}

// Функция для выделения памяти и инициализации матрицы символов
char** MatrixPath(int n) {
    char** matrix = new char* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new char[n];
        for (int j = 0; j < n; j++) {
            matrix[i][j] = ' ';
        }
    }
    return matrix;
}

// Функция для заполнения таблицы
void fillTable(int n, int** board, int** Table, char** path) {
    // Инициализируем начальную точку (правый верхний угол)
    Table[0][n - 1] = board[0][n - 1];

    // Заполняем первую строку
    for (int j = n - 2; j >= 0; j--) {
        Table[0][j] = Table[0][j + 1] + board[0][j];
        path[0][j] = 'L'; // Пришли слева
    }

    // Заполняем последний столбец
    for (int i = 1; i < n; i++) {
        Table[i][n - 1] = Table[i - 1][n - 1] + board[i][n - 1];
        path[i][n - 1] = 'D'; // Пришли сверху
    }

    // Заполняем остальную часть матрицы
    for (int i = 1; i < n; i++) {
        for (int j = n - 2; j >= 0; j--) {
            // Выбираем минимальный путь сверху или слева
            int fromTop = Table[i - 1][j];
            int fromLeft = Table[i][j + 1];

            if (fromTop < fromLeft) {
                Table[i][j] = fromTop + board[i][j];
                path[i][j] = 'D'; // Пришли сверху
            }
            else {
                Table[i][j] = fromLeft + board[i][j];
                path[i][j] = 'L'; // Пришли слева
            }
        }
    }
}

// Функция для восстановления пути короля
std::string KingWayRestore(int n, char** path) {
    std::string resultPath = "";
    int i = n - 1, j = 0;

    // Идем от конечной точки к начальной
    while (i > 0 || j < n - 1) {
        if (path[i][j] == 'D') {
            resultPath += 'D';
            i--;
        }
        else {
            resultPath += 'L';
            j++;
        }
    }

    // Разворачиваем путь
    int len = resultPath.length();
    for (int k = 0; k < len / 2; k++) {
        char temp = resultPath[k];
        resultPath[k] = resultPath[len - 1 - k];
        resultPath[len - 1 - k] = temp;
    }

    return resultPath;
}

// Функция для записи результата в файл
void writeResultToFile(const std::string& filename, int minSum, const std::string& path) {
    std::ofstream output(filename);

    if (!output.is_open()) {
        std::cout << "Ошибка создания файла " << filename << std::endl;
        return;
    }

    // Записываем результат в файл
    output << minSum << std::endl;
    output << path << std::endl;

    output.close();
}

// Освобождения памяти
void freeMatrix(int** matrix, int n) {
    if (matrix != nullptr) {
        for (int i = 0; i < n; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

// Освобождения памяти
void freeCharMatrix(char** matrix, int n) {
    if (matrix != nullptr) {
        for (int i = 0; i < n; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Чтение из файла
void readInput(const std::string& filename, int& K, int& N) {
    std::ifstream input(filename);

    if (!input.is_open()) {
        std::cout << "Ошибка открытия файла" << std::endl;
        exit(1);
    }

    input >> K >> N;
    input.close();
}

// Функция для выделения памяти
double** createTable(int N) {
    // Создаем двумерный массив
    double** Table = new double* [N + 1];
    for (int i = 0; i <= N; i++) {
        Table[i] = new double[4]();  // Инициализируем нулями
    }
    return Table;
}

// Функция для заполнения таблицы 
void fillTable(int K, int N, double** Table) {
    // Инициализация для чисел длины 1
    Table[1][0] = K - 1;  // первая цифра не ноль (K-1 вариков)
    Table[1][1] = 0;
    Table[1][2] = 0;
    Table[1][3] = 0;

    // Заполнение таблицы для длин от 2 до N
    for (int i = 2; i <= N; i++) {
        // Сумма всех чисел длины i-1
        double totalPrev = Table[i - 1][0] + Table[i - 1][1] + Table[i - 1][2] + Table[i - 1][3];

        // Если ставим не ноль на текущую позицию
        Table[i][0] = (K - 1) * totalPrev;

        // Если ставим ноль на текущую позицию
        // Для получения j нулей в конце, нужно чтобы в предыдущем числе было j-1 нулей в конце
        Table[i][1] = Table[i - 1][0];
        Table[i][2] = Table[i - 1][1];
        Table[i][3] = Table[i - 1][2];
    }
}

double calculateResult(int N, double** Table) {
    return Table[N][0] + Table[N][1] + Table[N][2] + Table[N][3];
}

// Функция для записи результата в файл
void writeResultToFile(const std::string& filename, double result) {
    std::ofstream output(filename);

    if (!output.is_open()) {
        std::cout << "Ошибка создания файла output.txt" << std::endl;
        return;
    }

    output << std::fixed << std::setprecision(0) << result << std::endl;
    output.close();
}

void freeTable(double** Table, int N) {
    for (int i = 0; i <= N; i++) {
        delete[] Table[i];
    }
    delete[] Table;
}