#ifndef DOMINOSOLVER_H
#define DOMINOSOLVER_H

#include "domino.h"
#include "DynamicStructures.h"
#include "exceptions.h"

class DominoSolver {
public:
    static DoublyLinkedList<Domino> solve(const DynamicArray<Domino>& tiles);
private:
    static void hierholzer(int u, int count[7][7],
                           DoublyLinkedList<Domino>& list);
};

#endif