#ifndef ANALIZADORLEXICOSINTACTICO_SYNTACTIC_H
#define ANALIZADORLEXICOSINTACTICO_SYNTACTIC_H
#include "../Grammar/Grammar.h"
#include "../Lexer/Lexer.h"
#include <memory>

#include "../utils/stack/Stack.hpp"


class Syntactic {
private:
    std::unique_ptr<Lexer> lexer;
    std::unique_ptr<Grammar> grammar;
    std::unique_ptr<Stack<std::string>> stack;
    int matrix[11][20] = {
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 2, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0},
        { 0, 3, 4, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0},
        { 0, 6, 0, 0, 0, 7, 0, 0, 8, 0, 0, 0, 0, 5, 5, 5, 0, 0, 0, 0},
        { 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0,11, 0, 0, 0,11, 0,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0,12, 0, 0, 0, 0, 0, 0, 0, 0,12,12,12, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0,14, 0, 0, 0,14, 0, 0, 0, 0, 0, 0, 0, 0,13,13,13,13},
        { 0,15, 0, 0, 0, 0, 0, 0, 0, 0,16,17,18, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,19,20,21, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,22,23,25,24},
    };

    void printTrace(Token token, int derivation);
public:
    Syntactic(
        const std::string& program,
        const std::string& grammar);

    void analize();
    bool inNotTerminals(const std::string& value);
    int getIndexNoTerminals(const std::string& value);
    int getIndexTerminals(const std::string& value);
};


#endif //ANALIZADORLEXICOSINTACTICO_SYNTACTIC_H