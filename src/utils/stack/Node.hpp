#ifndef ANALIZADORLEXICOSINTACTICO_NODE_HPP
#define ANALIZADORLEXICOSINTACTICO_NODE_HPP
#include <algorithm>
#include <memory>

template <typename R> class Stack;

template <typename T>
class Node {
private:
    T value;
    std::unique_ptr<Node> next;

public:
    Node(T value): value(value){}

    T getValue() {
        return value;
    }

    void setNext(std::unique_ptr<Node> next) {
        this->next = std::move(next);
    }

    Node* getNext() {
        return next.get();
    }

    std::unique_ptr<Node<T>> getNextUnique() {
        return std::move(next);
    }
};


#endif //ANALIZADORLEXICOSINTACTICO_NODE_HPP