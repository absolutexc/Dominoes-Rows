#ifndef DOMINO_H
#define DOMINO_H

#include <string>
#include <utility>

class Domino {
private:
    int a, b;
public:
    Domino(int x, int y);
    Domino(const Domino& other) = default;
    int first() const;
    int second() const;
    std::string toString() const;
    std::pair<int, int> normalized() const;
    bool operator==(const Domino& other) const;
};

#endif