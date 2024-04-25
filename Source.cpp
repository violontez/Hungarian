#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9; // Бесконечность

// Функция для поиска минимального элемента в матрице
int findMin(const vector<vector<int>>& matrix, vector<bool>& rowUsed, vector<bool>& colUsed, int rows, int cols) {
    int minVal = INF;
    for (int i = 0; i < rows; ++i) {
        if (!rowUsed[i]) {
            for (int j = 0; j < cols; ++j) {
                if (!colUsed[j]) {
                    minVal = min(minVal, matrix[i][j]);
                }
            }
        }
    }
    return minVal;
}

// Функция для нахождения оптимального назначения с помощью венгерского алгоритма
void hungarianAlgorithm(const vector<vector<int>>& matrix) {
    int rows = matrix.size();    // Количество строк
    int cols = matrix[0].size(); // Количество столбцов

    // Создаем вспомогательные структуры данных
    vector<int> rowAssign(rows, -1);
    vector<int> colAssign(cols, -1);
    vector<bool> rowUsed(rows, false);
    vector<bool> colUsed(cols, false);

    // Проходим по всем строкам матрицы
    for (int i = 0; i < rows; ++i) {
        int minVal = findMin(matrix, rowUsed, colUsed, rows, cols);
        // Проходим по всем столбцам матрицы
        for (int j = 0; j < cols; ++j) {
            // Если текущий элемент равен минимальному значению и строка и столбец не используются
            if (matrix[i][j] == minVal && !rowUsed[i] && !colUsed[j]) {
                rowAssign[i] = j;
                colAssign[j] = i;
                rowUsed[i] = true;
                colUsed[j] = true;
                break;
            }
        }
    }

    // Выводим результат на экран
    cout << "Оптимальное назначение:\n";
    for (int i = 0; i < rows; ++i) {
        cout << "Работник " << i + 1 << " -> Вакансия " << rowAssign[i] + 1 << "\n";
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    // Пример матрицы приоритетов (6 работников на 4 вакансии)
    vector<vector<int>> matrix = {
        {5, 7, 6, 1},
        {3, 6, 7, 5},
        {1, 4, 2, 6},
        {6, 3, 9, 4},
        {2, 5, 4, 7},
        {1, 8, 3, 9}
    };

    // Вызываем функцию решения задачи
    hungarianAlgorithm(matrix);

    return 0;
}
