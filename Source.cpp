#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 10;
const int INF = 1e9;

int n, m;
int cost[MAXN][MAXN];
int minv[MAXN], minu[MAXN];
int u[MAXN], v[MAXN], p[MAXN], way[MAXN];
bool used[MAXN];

void hungarian_algorithm() {
    fill(p, p + MAXN, -1);
    fill(v, v + MAXN, 0);
    fill(u, u + MAXN, 0);
    for (int i = 0; i < n; ++i) {
        p[0] = i;
        int j0 = 0;
        fill(minv, minv + MAXN, INF);
        fill(used, used + MAXN, false);
        do {
            used[j0] = true;
            int i0 = p[j0], delta = INF, j1;
            for (int j = 0; j < n; ++j)
                if (!used[j]) {
                    int cur = cost[i0][j] - u[i0] - v[j];
                    if (cur < minv[j])
                        minv[j] = cur, minu[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j], j1 = j;
                }
            for (int j = 0; j < n; ++j)
                if (used[j])
                    u[p[j]] += delta, v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != -1);
        do {
            int j1 = minu[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    // Ввод данных
    cout << "Введите количество кандидатов (не более 10): ";
    cin >> n;
    cout << "Введите количество вакантных мест (не более 10): ";
    cin >> m;
    cout << "Введите матрицу приоритетов:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> cost[i][j];

    // Запуск алгоритма
    hungarian_algorithm();

    // Вывод результата
    cout << "Результаты назначений:\n";
    for (int i = 0; i < m; ++i)
        cout << "Вакансия " << i + 1 << ": Кандидат " << p[i] + 1 << "\n";

    return 0;
}