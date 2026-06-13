#include "Lexer.h"
#include "../utils/RegexManager.h"

#include <iostream>
#include <string>
#include <iomanip>

    Token Lexer::getToken() {
        while (reader.hasNext()) {
            auto character = reader.readChar();

            if (isspace(character)) {
                continue;
            }

            if (isalpha(character)) {
                std::string token;
                token.push_back(character);

                while (reader.hasNext() && isalnum(reader.peek())) {
                    token.push_back(reader.readChar());
                }

                return evaluateToken(token);
            }

            if (isdigit(character)) {
                std::string token;
                token.push_back(character);

                while (reader.hasNext() && isalnum(reader.peek())) {
                    token.push_back(reader.readChar());
                }

                return evaluateToken(token);
            }

            const auto token = std::string(1, character);
            return this->evaluateToken(token);
        }
        return Token {
            "EOF",
            "EOF",
            0,
            "EOF",
        };
    }

void Lexer::printTable() {
    std::cout << "Tabla de simbolos"<<"\n";
    std::cout << std::left
              << std::setw(15) << "TOKEN"
              << std::setw(15) << "LEXEMA"
              << std::setw(15) << "ATRIBUTO"
              << std::setw(20) << "CLASIFICACION"
              << std::setw(20) << "REGEX"
              << std::endl;

    std::cout << std::string(85, '-') << std::endl;
    for (const auto& token : symbolsTable) {
        std::cout << std::left
                  << std::setw(15) << token.token
                  << std::setw(15) << token.lexeme
                  << std::setw(15) << token.attribute
                  << std::setw(20) << token.classification
                  << std::setw(20) << token.regex
                  << std::endl;
    }
    std::cout<<"\n";
    std::cout<<"\n";
}

Token Lexer::evaluateToken(const std::string& token) {
    Token tokenStruct = {
        token,
        token,
        this->attribute,
        "",
        ""
    };

    if (reservedWords.contains(token)) {
        std::cout<<token << ": Palabra reservada" << "\n";

        tokenStruct.classification = token;
        tokenStruct.regex = R"(\b(programa|binario|octal|hexa|leer|escribir|finprograma)\b)";
        symbolsTable.insert(tokenStruct);

        this->attribute++;
        printTable();
    }
    else if (RegexManager::verifyIdentifier(token)) {
        std::cout <<token << ": Indentificador" << "\n";

        tokenStruct.classification = "id";
        tokenStruct.regex = RegexManager::identifierRgx;

        this->symbolsTable.insert(tokenStruct);
        this->attribute++;
    }
    else if (RegexManager::verifyBinaryNumber(token)) {
        std::cout <<token << ": Numero binario" << "\n";

        tokenStruct.classification = "litbinaria";
        tokenStruct.regex = RegexManager::binaryNumberRgx;

        this->attribute++;
    }
    else if (RegexManager::verifyOctalNumber(token)) {
        std::cout << token << ": Numero octal" << "\n";

        tokenStruct.classification = "litoctal";
        tokenStruct.regex = RegexManager::octalNumberRgx;

        this->attribute++;
    }
    else if (RegexManager::verifyHexaNumber(token)) {
        std::cout << token << ": Numero hexadecimal" << "\n";

        tokenStruct.classification = "lithexa";
        tokenStruct.regex = RegexManager::hexaNumberRgx;

        this->attribute++;
    }
    else if (RegexManager::verifySymbol(token)) {
        std::cout << token << ": Caracter especial" << "\n";

        tokenStruct.classification = token;
        tokenStruct.regex = RegexManager::symbolsRgx;

        this->attribute++;
    }
    else {
        std::cout << token << ": Caracter no valido" << "\n";

        tokenStruct.classification = "Caracter no valido";
        tokenStruct.regex = RegexManager::identifierRgx;

        this->attribute++;
    }

    return tokenStruct;
}
