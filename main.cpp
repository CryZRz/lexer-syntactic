#include <iostream>

#include "src/Lexer/Lexer.h"
#include "src/Syntactic/Syntactic.h"

int main() {

    try {
        auto syntatic = Syntactic("/home/chris/Documents/Code/cplusplus/analizadorLexicoSintactico/program2.txt", "/home/chris/Documents/Code/cplusplus/analizadorLexicoSintactico/gramatica.txt");
        syntatic.analize();
        std::cout<<"Porgrama valido";
    }catch (std::exception& e) {
        std::cout<<e.what();
    }

    return 0;
}
