#include "Syntactic.h"

#include <iostream>
#include <ranges>

Syntactic::Syntactic(
    const std::string &program,
    const std::string &grammar
    )
        :
    lexer(std::make_unique<Lexer>(program)),
    grammar(std::make_unique<Grammar>(grammar)),
    stack(std::make_unique<Stack<std::string>>())
{
    this->grammar.get()->generateStructures();
}


void Syntactic::analize() {
    std::string initialSymbol = grammar->getInitial();

    stack->push(initialSymbol);
    auto x = stack->peek();
    auto a = lexer->getToken();
    while (!stack->isEmpty()) {
        if (inNotTerminals(x)) {
            auto predict = matrix[getIndexNoTerminals(x)][getIndexTerminals(a.classification)];
            if (predict != 0) {
                auto productions = grammar->getProductions()[predict-1];
                stack->pop();
                for (const auto& elem : productions | std::ranges::views::reverse) {
                    stack->push(elem);
                }
                x = stack->peek();
                printTrace(a, predict);
            }else {
                throw std::runtime_error("syntax error");
            }
        }else {
            if (x == a.classification) {
                stack->pop();
                a = lexer->getToken();
                if (!stack->isEmpty()) {
                    x = stack->peek();
                }
            }else {
                throw std::runtime_error("syntax error");
            }
        }
    }
}

void Syntactic::printTrace(Token token, int derivation) {
    std::cout<<"Token actual: "<<"\n";
    std::cout<<"Token"<<token.token<<"\n";
    std::cout<<"Clasificacion"<<token.classification<<"\n";
    std::cout<<"Pila"<<"\n";
    stack->printStack();
    std::cout<<grammar->getRightSides()[derivation]<<"\n";
    std::cout<<"\n";
}

int Syntactic::getIndexNoTerminals(const std::string &value) {
    for (auto i = 0; i < grammar->getNotTerminalsSize(); ++i) {
        if (grammar->getNotTerminals()[i] == value) {
            return i;
        }
    }
    //se supone que aqui no deberiamos de llegar xd
    return -1;
}

int Syntactic::getIndexTerminals(const std::string &value) {
    for (auto i = 0; i < grammar->getTerminalsSize(); ++i) {
        if (grammar->getTerminals()[i] == value) {
            return i;
        }
    }
    //se supone que aqui no deberiamos de llegar xd
    return -1;
}

bool Syntactic::inNotTerminals(const std::string &value) {
    for (auto i = 0; i < grammar->getNotTerminalsSize(); ++i) {
        if (grammar->getNotTerminals()[i] == value) {
            return true;
        }
    }
    return false;
}
