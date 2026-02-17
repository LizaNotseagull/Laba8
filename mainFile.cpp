#include <iostream>
#include <string>
#include <fstream>
#include <clocale>
#include <iomanip>
#include "Header.h"

void N_1() {
    std::setlocale(LC_ALL, "Russian");

    int itemsCount, minWeight;
    int* weight = nullptr, * tax = nullptr;

    readFromFile("input.txt", itemsCount, minWeight, weight, tax);

    // Вычисление суммарного веса всех предметов
    int totalWeight = 0;
    for (int i = 0; i < itemsCount; i++) totalWeight += weight[i];

    // Выделение памяти для массивов
    long long* minTax = new long long[totalWeight + 1];
    int* prevItem = new int[totalWeight + 1];

    // Заполнение таблицы
    FillTable(itemsCount, totalWeight, weight, tax, minTax, prevItem);

    // Поиск лучшего решения
    long long minTaxFound;
    int bestWeight;
    if (!findBest(minWeight, totalWeight, minTax, minTaxFound, bestWeight)) {
        std::cout << "Решение не найдено" << std::endl;

        delete[] weight;
        delete[] tax;
        delete[] minTax;
        delete[] prevItem;
        return;
    }

    // Восстановление выбранных предметов
    int* slctd = nullptr;
    int slctdCount = 0;
    reconstItems(bestWeight, itemsCount, prevItem, weight, slctd, slctdCount);

    // Вычисление суммарных значений
    int sumWeight;
    long long sumTax;
    int* num = nullptr;
    weightNtax(slctd, slctdCount, weight, tax, sumWeight, sumTax, num);

    // Вывод результатов
    printResults(num, slctdCount, sumWeight, sumTax);

    delete[] weight;
    delete[] tax;
    delete[] minTax;
    delete[] prevItem;
    delete[] slctd;
    delete[] num;
}

void N_2() {
    std::setlocale(LC_ALL, "Russian");

    int n;
    int** board = nullptr;
    int** Table = nullptr;
    char** path = nullptr;
    bool fileRead = false;

    // Чтение из файла
    fileRead = readFromFile("input2.txt", n, board);

    if (fileRead) {
        // Создание матриц
        Table = MatrixMinSum(n);   // Матрица минимальных сумм
        path = MatrixPath(n);  // Матрица путей

        // Заполнение таблицы
        fillTable(n, board, Table, path);

        // Восстановление пути
        std::string resultPath = KingWayRestore(n, path);

        // Запись в файл
        writeResultToFile("output2.txt", Table[n - 1][0], resultPath);

        // Вывод результата
        std::cout << "Минимальная сумма неприятностей: " << Table[n - 1][0] << std::endl;
        std::cout << "Путь короля: " << resultPath << std::endl;
    }
    else {
        
        std::cout << "Программа завершена из-за ошибки чтения файла." << std::endl;
    }

    freeMatrix(board, n);
    freeMatrix(Table, n);
    freeCharMatrix(path, n);
}

void N_3() {
    std::setlocale(LC_ALL, "Russian");

    int K, N;

    // Чтение из файла
    readInput("input3.txt", K, N);

    // Создание табл
    double** Table = createTable(N);

    // Заполнение табл
    fillTable(K, N, Table);

    // Вычисление результата
    double result = calculateResult(N, Table);

    // Запись в файл
    writeResultToFile("output.txt", result);

    // Вывод результата
    std::cout << "Количество K-ичных чисел из N разрядов (К и N смотри в файле): "
        << std::fixed << std::setprecision(0) << result << std::endl;

    freeTable(Table, N);
}

int main() {
    std::setlocale(LC_ALL, "RU");
    int V;
    do {
        std::cout << "Выберите: " << std::endl << std::endl;
        std::cout << "1 - Задача 1 РЮКЗАК" << std::endl;
        std::cout << "2 - Задача 2 ХРОМОЙ КОРОЛЬ " << std::endl;
        std::cout << "3 - Задача 3 ЕЩЁ ЧТО-ТО" << std::endl;
        std::cout << "0 - Завершить ?" << std::endl << std::endl;
        std::cout << "Выберите задачу: ";
        std::cin >> V;

        switch (V) {
        case 1:
            N_1();
            break;
        case 2:
            N_2();
            break;
        case 3:
            N_3();
            break;
        case 0:
            std::cout << "Завершаю" << std::endl;
            break;
        default:
            std::cout << "Выберите от 0 до 3" << std::endl;
        }
    } while (V != 0);
    return 0;
}