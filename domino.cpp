#include "domino.h"
#include <algorithm>

Domino::Domino(int x, int y) : a(x), b(y) {}

int Domino::first() const { return a; }
int Domino::second() const { return b; }

std::string Domino::toString() const {
    return std::to_string(a) + std::to_string(b);
}

std::pair<int, int> Domino::normalized() const {
    return {std::min(a, b), std::max(a, b)};
}

bool Domino::operator==(const Domino& other) const {
    return normalized() == other.normalized();
}