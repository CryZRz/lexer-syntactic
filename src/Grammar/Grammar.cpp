#include "Grammar.h"

#include <vector>
#include <regex>
#include <unordered_set>

void Grammar::generateStructures() {
    auto dynamicGrammar = std::vector<std::string>();
    while (fileReader.hasNext()) {
        auto linea = fileReader.readLine();
        dynamicGrammar.push_back(linea);
    }

    sizeGrammar = dynamicGrammar.size();
    grammar = std::make_unique<std::string[]>(sizeGrammar);
    for (size_t i = 0; i < dynamicGrammar.size(); i++) {
        grammar[i] = dynamicGrammar[i];
    }
    fileReader.close();
    generateRightSides();
    generateNotTerminals();
    generateTerminals();
    generateInitial();
    generateProductions();
}

void Grammar::generateRightSides() {
    const auto size = sizeGrammar;
    std::smatch match;
    auto rightSidesDynamic = std::vector<std::string>();

    for (size_t i = 0; i < size; i++) {
        if (std::regex_match(grammar[i], match, patternGrammar)) {
            rightSidesDynamic.push_back(match[2].str());
        }
    }

    sizeRightSides = rightSidesDynamic.size();
    rightSides = std::make_unique<std::string[]>(sizeRightSides);

    for (size_t i = 0; i < size; i++) {
        rightSides[i] = rightSidesDynamic[i];
    }
}

void Grammar::generateProductions() {
    std::vector<std::vector<std::string>> productionsTemp;

    auto rgx = R"((<[a-zA-Z]+>)|(programa|finprograma|id|leer|escribir|litbinaria|litoctal|lithexa|binario|octal|hexad)|([;=(),\+\-\/\*]))";
    std::regex rgxCombinada(rgx);

    for (int i = 0; i < sizeRightSides; i++) {
        std::vector<std::string> production;
        auto rightSide = rightSides[i];

        std::sregex_iterator start(rightSide.begin(), rightSide.end(), rgxCombinada);
        std::sregex_iterator end;

        while (start != end) {
            production.push_back(start->str());
            start++;
        }

        productionsTemp.push_back(production);
    }

    productions = productionsTemp;
}


void Grammar::generateNotTerminals() {
    const auto size = sizeGrammar;
    std::smatch match;
    auto notTerminalsDynamic = std::vector<std::string>();
    auto setVerify = std::unordered_set<std::string>();

    for (size_t i = 0; i < size; i++) {
        if (std::regex_match(grammar[i], match, patternGrammar)) {
            auto textClean = std::regex_replace(match[1].str(), rgxCleanText, "");

            if (setVerify.insert(textClean).second) {
                notTerminalsDynamic.push_back(textClean);
            }

        }
    }

    sizeNotTerminals = notTerminalsDynamic.size();
    notTerminals = std::make_unique<std::string[]>(sizeNotTerminals);

    auto index = 0;
    for (const auto& notTerminal : notTerminalsDynamic) {
        notTerminals[index] = notTerminal;
        index++;
    }

}

void Grammar::generateTerminals() {
    std::vector<std::string> terminalDynamic;
    std::unordered_set<std::string> setVerify;

    for (size_t i = 0; i < sizeGrammar; i++) {
        auto target = rightSides[i];

        auto wordsBegin = std::sregex_iterator(target.begin(), target.end(), noTerminalRgx);
        auto wordsEnd = std::sregex_iterator();

        for (auto it = wordsBegin; it != wordsEnd; ++it) {
            std::smatch match = *it;
            std::string terminal = match.str();

            if (setVerify.insert(terminal).second) {
                terminalDynamic.push_back(terminal);
            }
        }
    }

    sizeTerminals = terminalDynamic.size();
    terminals = std::make_unique<std::string[]>(sizeTerminals);

    size_t index = 0;
    for (const auto& term : terminalDynamic) {
        terminals[index] = term;
        index++;
    }

}

void Grammar::generateInitial() {
    std::vector<std::string> noTerminalsVec;

    for (size_t z = 0; z < sizeRightSides; z++) {
        std::string text = rightSides[z];
        std::smatch match;

        while (std::regex_search(text, match, rgxTerminals)) {
            noTerminalsVec.push_back(match[0].str());
            text = match.suffix().str();
        }
    }

    std::vector<std::string> diferencia;
    for (int i = 0; i < sizeNotTerminals; i++) {
        if (std::find(noTerminalsVec.begin(), noTerminalsVec.end(), notTerminals[i]) == noTerminalsVec.end()) {
            diferencia.push_back(notTerminals[i]);

        }
    }

    initialSymbol = diferencia[0];
}

const std::string* Grammar::getTerminals() const {
    return terminals.get();
}

const std::string* Grammar::getNotTerminals() const {
    return notTerminals.get();
}

const std::string* Grammar::getRightSides() const {
    return rightSides.get();
}

const std::string *Grammar::getGrammar() const {
    return grammar.get();
}

size_t Grammar::getGrammarSize() const {
    return sizeGrammar;
}

size_t Grammar::getRightSidesSize() const {
    return sizeGrammar;
}

size_t Grammar::getNotTerminalsSize() const {
    return sizeNotTerminals;
}

size_t Grammar::getTerminalsSize() const {
    return sizeTerminals;
}

const std::string& Grammar::getInitial() const {
    return initialSymbol;
}

const std::vector<std::vector<std::string> > &Grammar::getProductions() const {
    return productions;
}