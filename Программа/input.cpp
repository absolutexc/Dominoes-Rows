#include "input.h"
#include "exceptions.h"
#include "DynamicStructures.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <limits>

int getValidatedInt(int min, int max, const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите число! Попробуйте снова.\n";
        } else if (value < min || value > max) {
            std::cout << "Ошибка: число должно быть от " << min << " до " << max << ". Попробуйте снова.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

DynamicArray<Domino> parseInput(const std::string& line) {
    DynamicArray<Domino> result;
    std::string cleaned = line;
    std::replace(cleaned.begin(), cleaned.end(), ',', ' ');
    std::istringstream iss(cleaned);
    std::string token;

    while (iss >> token) {
        if (token.length() != 2) {
            throw InvalidInputException("Неверный формат кости: " + token);
        }
        if (!std::isdigit(token[0]) || !std::isdigit(token[1])) {
            throw InvalidInputException("Недопустимый символ в кости: " + token);
        }
        int a = token[0] - '0';
        int b = token[1] - '0';
        if (a < 0 || a > 6 || b < 0 || b > 6) {
            throw InvalidInputException("Число вне диапазона 0-6 в кости: " + token);
        }
        result.push_back(Domino(a, b));
    }

    if (result.empty()) {
        throw InvalidInputException("Не введено ни одной кости");
    }
    return result;
}

DynamicArray<Domino> manualInput() {
    while (true) {
        try {
            std::cout << "Введите кости (через пробелы или запятые):\n";
            std::string line;
            std::getline(std::cin, line);

            if (line.empty()) {
                std::cout << "Ошибка: строка пуста. Попробуйте снова.\n";
                continue;
            }

            bool onlySpaces = true;
            for (char c : line) {
                if (!std::isspace(c)) {
                    onlySpaces = false;
                    break;
                }
            }
            if (onlySpaces) {
                std::cout << "Ошибка: введены только пробелы. Попробуйте снова.\n";
                continue;
            }

            return parseInput(line);
        } catch (const InvalidInputException& e) {
            std::cout << "Ошибка: " << e.what() << ". Попробуйте снова.\n";
        }
    }
}

DynamicArray<Domino> randomInput() {
    int num = rand() % 12 + 1;
    bool used[7][7] = {false};
    DynamicArray<Domino> tiles;

    for (int i = 0; i < num; ++i) {
        int a, b;
        do {
            a = rand() % 7;
            b = rand() % 7;
        } while (used[std::min(a, b)][std::max(a, b)]);
        used[std::min(a, b)][std::max(a, b)] = true;
        tiles.push_back(Domino(a, b));
    }
    return tiles;
}

DynamicArray<Domino> fileInput() {
    while (true) {
        try {
            std::cout << "Введите имя файла:\n";
            std::string filename;
            std::getline(std::cin, filename);

            if (filename.empty()) {
                std::cout << "Ошибка: имя файла не может быть пустым. Попробуйте снова.\n";
                continue;
            }

            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cout << "Ошибка: не удалось открыть файл '" << filename << "'. Попробуйте снова.\n";
                continue;
            }

            std::string line;
            std::getline(file, line);
            file.close();

            if (line.empty()) {
                std::cout << "Ошибка: файл пуст. Попробуйте другой файл.\n";
                continue;
            }

            return parseInput(line);
        } catch (const InvalidInputException& e) {
            std::cout << "Ошибка в содержимом файла: " << e.what() << ". Попробуйте другой файл.\n";
        }
    }
}

void printTiles(const DynamicArray<Domino>& tiles) {
    for (size_t i = 0; i < tiles.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << tiles[i].toString();
    }
}

void printRules() {
    std::cout << "Правила\n\n";
    std::cout << "Кость домино состоит из двух чисел от 0 до 6.\n";
    std::cout << "Ряд считается корректным, если соседние кости\n";
    std::cout << "соприкасаются одинаковыми числами.\n";
    std::cout << "\nЗадача: определить, можно ли выложить заданный\n";
    std::cout << "набор костей в один ряд (каждая кость используется\n";
    std::cout << "ровно один раз).\n";
    std::cout << "\nЕсли можно — вывести один из возможных вариантов\n";
    std::cout << "расположения.\n";
    std::cout << "Кости в наборе уникальны (нет дубликатов даже в перевёрнутом виде).\n";
}