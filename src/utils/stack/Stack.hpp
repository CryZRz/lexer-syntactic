#ifndef ANALIZADORLEXICOSINTACTICO_STACK_HPP
#define ANALIZADORLEXICOSINTACTICO_STACK_HPP

#include <memory>
#include "Node.hpp"
#include <iostream>

template <typename  T>
class Stack {

private:
    std::unique_ptr<Node<T>> top = nullptr;

public:
    void push(T value) {
        auto newNode = std::make_unique<Node<T>>(value);
        newNode->setNext(std::move(top));
        top = std::move(newNode);
    }

    T pop() {
        if (top == nullptr) {
            throw std::runtime_error("La pila esta vacia");
        }

        auto value = top->getValue();
        auto oldTop = std::move(top);
        top = std::move(oldTop->getNextUnique());

        return value;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("La pila esta vacia");
        }

        return top->getValue();
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void printStack() {
        if (isEmpty()) {
            std::cout << "[ Pila Vacía ]\n";
            return;
        }

        std::cout << "Tope -> ";
        Node<T>* current = top.get();

        while (current != nullptr) {
            std::cout << "[ " << current->getValue() << " ] ";
            current = current->getNext();
        }
        std::cout << "\n";
    }

};


#endif //ANALIZADORLEXICOSINTACTICO_STACK_HPP