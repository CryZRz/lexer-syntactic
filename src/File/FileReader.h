#ifndef ANALIZADORLEXICOSINTACTICO_H
#define ANALIZADORLEXICOSINTACTICO_H

#include <fstream>

class FileReader {
private:
    std::ifstream file;
public:
    FileReader(const std::string& fileName): file(fileName){};
    FileReader();

    void initFile(const std::string& path);
    char readChar();
    std::string readLine();
    bool hasNext();
    void close();
    void ungetChar();
    char peek();
};


#endif