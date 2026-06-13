#ifndef GRAMATICA_GRAMMARGENERATOR_H
#define GRAMATICA_GRAMMARGENERATOR_H

#include "../File/FileReader.h"
#include <memory>
#include <regex>

class Grammar {
private:
    FileReader fileReader;
    std::unique_ptr<std::string[]> grammar;
    std::unique_ptr<std::string[]> rightSides;
    std::vector<std::vector<std::string>> productions;
    std::unique_ptr<std::string[]> notTerminals;
    std::unique_ptr<std::string[]> terminals;
    size_t sizeGrammar;
    size_t sizeRightSides;
    size_t sizeNotTerminals;
    size_t sizeTerminals;
    std::regex patternGrammar = std::regex(R"(^(.+?)\s*->\s*(.+)$)");
    std::regex rgxCleanText = std::regex(R"([^a-zA-Z<>])");
    std::regex rgxTerminals = std::regex(R"(<[a-zA-Z]+>)");
    std::string initialSymbol;
    //Si la grammaire change nous devons changer ceta
    std::regex noTerminalRgx = std::regex("(programa|finprograma|id|leer|escribir|litbinaria|litoctal|lithexa|binario|octal|hexad)|([;=(),\\+\\-\\/*])");

    void generateRightSides();
    void generateNotTerminals();
    void generateTerminals();
    void generateInitial();
    void generateProductions();
public:
    Grammar(const std::string& fileName): fileReader(fileName){};

    void generateStructures();
    const std::string* getGrammar() const;
    const std::string* getRightSides() const;
    const std::string* getNotTerminals() const;
    const std::string* getTerminals() const;
    const std::vector<std::vector<std::string>>& getProductions() const;

    size_t getGrammarSize() const;
    size_t getRightSidesSize() const;
    size_t getNotTerminalsSize() const;
    size_t getTerminalsSize() const;
    const std::string& getInitial() const;
};


#endif