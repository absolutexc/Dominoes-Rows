#include "dominoSolver.h"
#include <algorithm>

DoublyLinkedList<Domino> DominoSolver::solve(const DynamicArray<Domino>& tiles) {
    // 1. Проверка уникальности костей (с учётом переворота)
    bool used[7][7] = {false};
    for (size_t i = 0; i < tiles.size(); ++i) {
        auto norm = tiles[i].normalized();
        int minVal = norm.first;
        int maxVal = norm.second;
        if (used[minVal][maxVal]) {
            throw InvalidInputException("Обнаружен дубликат кости");
        }
        used[minVal][maxVal] = true;
    }

    // 2. Построение матрицы смежности
    int count[7][7] = {0};
    for (size_t i = 0; i < tiles.size(); ++i) {
        int u = tiles[i].first();
        int v = tiles[i].second();
        if (u == v) {
            count[u][u]++;
        } else {
            count[u][v]++;
            count[v][u]++;
        }
    }

    // 3. Вычисление степеней вершин
    int degree[7] = {0};
    int totalEdges = 0;
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            degree[i] += count[i][j];
            totalEdges += count[i][j];
        }
    }
    totalEdges /= 2;

    // 4. Проверка условия эйлерова пути (0 или 2 вершины с нечётной степенью)
    int oddDegrees = 0;
    for (int i = 0; i < 7; ++i) {
        if (degree[i] % 2 != 0) ++oddDegrees;
    }
    if (oddDegrees != 0 && oddDegrees != 2) {
        throw NoEulerianPathException("Условие эйлерова пути не выполнено (нечётных вершин: " + std::to_string(oddDegrees) + ")");
    }

    // 5. Проверка связности графа
    int startVertex = -1;
    for (int i = 0; i < 7; ++i) {
        if (degree[i] > 0) {
            startVertex = i;
            break;
        }
    }
    if (startVertex == -1) {
        throw InvalidInputException("Не введено ни одной кости");
    }

    bool visited[7] = {false};
    Queue<int> q;
    q.push(startVertex);
    visited[startVertex] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < 7; ++v) {
            if (count[u][v] > 0 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    for (int i = 0; i < 7; ++i) {
        if (degree[i] > 0 && !visited[i]) {
            throw NoEulerianPathException("Граф несвязный");
        }
    }

    // 6. Выбор стартовой вершины для эйлерова пути
    int start = -1;
    if (oddDegrees == 2) {
        for (int i = 0; i < 7; ++i) {
            if (degree[i] % 2 != 0) {
                start = i;
                break;
            }
        }
    } else {
        start = startVertex;
    }

    // 7. Построение эйлерова пути (алгоритм Хирхольцера)
    DoublyLinkedList<Domino> result;
    hierholzer(start, count, result);

    // 8. Проверка, что использованы все рёбра
    if (result.size() != static_cast<size_t>(totalEdges)) {
        throw NoEulerianPathException("Эйлеров путь построен не полностью");
    }
    return result;
}

void DominoSolver::hierholzer(int u, int count[7][7],
                              DoublyLinkedList<Domino>& list) {
    for (int v = 0; v < 7; ++v) {
        if (count[u][v] > 0) {
            count[u][v]--;
            if (u != v) {
                count[v][u]--;
            }
            hierholzer(v, count, list);
            list.pushFront(Domino(u, v));
        }
    }
}