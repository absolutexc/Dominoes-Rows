#ifndef DYNAMICSTRUCTURES_H
#define DYNAMICSTRUCTURES_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>

template <typename T>
class DynamicArray {
private:
    T* data;
    size_t capacity;
    size_t len;

    void resize() {
        size_t newCapacity = capacity == 0 ? 2 : capacity * 2;
        T* newData = static_cast<T*>(::operator new(newCapacity * sizeof(T)));

        for (size_t i = 0; i < len; ++i) {
            new(newData + i) T(data[i]);
        }

        for (size_t i = 0; i < len; ++i) {
            data[i].~T();
        }
        ::operator delete(data);

        data = newData;
        capacity = newCapacity;
    }

public:
    DynamicArray() : data(nullptr), capacity(0), len(0) {}

    ~DynamicArray() {
        clear();
    }

    DynamicArray(const DynamicArray& other) : data(nullptr), capacity(0), len(0) {
        for (size_t i = 0; i < other.size(); ++i) {
            push_back(other[i]);
        }
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            clear();
            for (size_t i = 0; i < other.size(); ++i) {
                push_back(other[i]);
            }
        }
        return *this;
    }

    void push_back(const T& value) {
        if (len >= capacity) {
            resize();
        }
        new(data + len) T(value);
        ++len;
    }

    size_t size() const {
        return len;
    }

    bool empty() const {
        return len == 0;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    void clear() {
        for (size_t i = 0; i < len; ++i) {
            data[i].~T();
        }
        ::operator delete(data);
        data = nullptr;
        capacity = 0;
        len = 0;
    }
};

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    size_t count;

public:
    Queue() : head(nullptr), tail(nullptr), count(0) {}

    ~Queue() {
        while (!empty()) {
            pop();
        }
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
        ++count;
    }

    void pop() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        --count;
    }

    T& front() {
        return head->data;
    }

    bool empty() const {
        return count == 0;
    }

    size_t size() const {
        return count;
    }
};

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& d, Node* p = nullptr, Node* n = nullptr)
            : data(d), prev(p), next(n) {}
    };
    Node* head;
    Node* tail;
    size_t count;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), count(0) {
        Node* current = other.head;
        while (current) {
            pushBack(current->data);
            current = current->next;
        }
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current) {
                pushBack(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    ~DoublyLinkedList() {
        clear();
    }

    void pushFront(const T& value) {
        Node* newNode = new Node(value, nullptr, head);
        if (head) head->prev = newNode;
        else tail = newNode;
        head = newNode;
        ++count;
    }

    void pushBack(const T& value) {
        Node* newNode = new Node(value, tail, nullptr);
        if (tail) tail->next = newNode;
        else head = newNode;
        tail = newNode;
        ++count;
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        count = 0;
    }

    bool empty() const {
        return count == 0;
    }

    size_t size() const {
        return count;
    }

    void print(std::ostream& os, const std::string& delimiter = ", ") const {
        Node* current = head;
        bool first = true;
        while (current) {
            if (!first) os << delimiter;
            os << current->data.toString();
            first = false;
            current = current->next;
        }
    }
};

#endif