#ifndef ANALIZADORLEXICO_LEXER_H
#define ANALIZADORLEXICO_LEXER_H
#include <set>
#include <string>
#include "../File/FileReader.h"

struct Token {
    std::string token;
    std::string lexeme;
    int attribute;
    std::string classification;
    std::string regex;

    bool operator<(const Token& otro) const {
        return std::tie(token, lexeme, classification, regex) <
               std::tie(otro.token, otro.lexeme,
                        otro.classification, otro.regex);
    }
};

class Lexer {
    private:
        std::set<std::string> reservedWords = {
            "programa",
            "binario",
            "octal",
            "hexad",
            "leer",
            "escribir",
            "finprograma"
        };
        std::string source;
        size_t position = 0;
        std::set<Token> symbolsTable;
        int attribute = 300;
        FileReader reader;

        Token evaluateToken(const std::string& token);
        void printTable();
    public:
        Lexer(const std::string& file): reader(file){};

        Token getToken();

        const std::set<Token>& symbols_table() const {
            return symbolsTable;
        }
};


#endif