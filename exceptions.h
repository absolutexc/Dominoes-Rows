#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class InvalidInputException : public std::runtime_error {
public:
    explicit InvalidInputException(const std::string& msg) : std::runtime_error(msg) {}
};

class NoEulerianPathException : public std::runtime_error {
public:
    explicit NoEulerianPathException(const std::string& msg) : std::runtime_error(msg) {}
};

class FileOpenException : public std::runtime_error {
public:
    explicit FileOpenException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif