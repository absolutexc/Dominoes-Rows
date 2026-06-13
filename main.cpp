#include <iostream>
#include "DynamicStructures.h"
#include "dominoSolver.h"
#include "input.h"
#include "exceptions.h"

int main() {
    srand(time(0));

    int choice;
    do {
        std::cout << "\nПостроение ряда домино.\n";
        std::cout << "Главное меню.\n";
        std::cout << "1. Ввод набора костей\n";
        std::cout << "2. Вывод правил\n";
        std::cout << "3. Выход из программы\n";

        choice = getValidatedInt(1, 3, "Выберите пункт меню (1-3):\n ");

        switch (choice) {
            case 1: {
                std::cout << "Выберите способ ввода\n";
                std::cout << "1. Ввод вручную\n";
                std::cout << "2. Случайная генерация\n";
                std::cout << "3. Чтение из файла\n";

                int method = getValidatedInt(1, 3, "Выберите способ (1-3): ");

                DynamicArray<Domino> tiles;
                try {
                    if (method == 1) {
                        tiles = manualInput();
                    }
                    else if (method == 2) {
                        tiles = randomInput();
                        std::cout << "Сгенерированные кости: ";
                        printTiles(tiles);
                        std::cout << std::endl;
                    }
                    else if (method == 3) {
                        tiles = fileInput();
                    }
                    DoublyLinkedList<Domino> result = DominoSolver::solve(tiles);
                    std::cout << "Результат: можно: ";
                    result.print(std::cout);
                    std::cout << std::endl;
                }
                catch (const InvalidInputException& e) {
                    std::cout << "Результат: некорректные входные данные" << std::endl;
                }
                catch (const NoEulerianPathException& e) {
                    std::cout << "Результат: нельзя" << std::endl;
                }
                catch (const std::exception& e) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            case 2: {
                printRules();
                break;
            }
            case 3: {
                std::cout << "Спасибо за игру\n";
                break;
            }
        }
    } while (choice != 3);

    return 0;
}