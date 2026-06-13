cmake_minimum_required(VERSION 4.0)
project(analizadorLexicoSintactico)

set(CMAKE_CXX_STANDARD 20)

add_executable(analizadorLexicoSintactico main.cpp
        src/File/FileReader.cpp
        src/Grammar/Grammar.cpp
        src/Lexer/Lexer.cpp
        src/utils/RegexManager.cpp
        src/utils/stack/Stack.hpp
        src/utils/stack/Node.hpp
        src/Syntactic/Syntactic.cpp
        src/Syntactic/Syntactic.h)
