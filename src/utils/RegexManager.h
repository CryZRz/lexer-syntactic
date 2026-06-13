#ifndef ANALIZADORLEXICO_REGEXMANAGER_H
#define ANALIZADORLEXICO_REGEXMANAGER_H
#include <regex>


class RegexManager {
    public:
        static std::string identifierRgx;
        static std::string binaryNumberRgx;
        static std::string octalNumberRgx;
        static std::string hexaNumberRgx;
        static std::string symbolsRgx;

        static bool verifyIdentifier(std::string token);
        static bool verifyBinaryNumber(std::string token);
        static bool verifyOctalNumber(std::string token);
        static bool verifyHexaNumber(std::string token);
        static bool verifySymbol(std::string token);
};


#endif