#ifndef INPUT_H
#define INPUT_H

#include <string>
#include "domino.h"
#include "DynamicStructures.h"

// Функция валидации ввода чисел
int getValidatedInt(int min, int max, const std::string& prompt);

// Функции ввода данных
DynamicArray<Domino> parseInput(const std::string& line);
DynamicArray<Domino> manualInput();
DynamicArray<Domino> randomInput();
DynamicArray<Domino> fileInput();
void printTiles(const DynamicArray<Domino>& tiles);
void printRules();

#endif