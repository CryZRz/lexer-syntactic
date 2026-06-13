#include "FileReader.h"

char FileReader::readChar() {
    char value;
    if (!file.get(value)) {
        throw std::runtime_error("Error accediste mas alla del final del archivo");
    }

    return value;
}

void FileReader::ungetChar() {
    file.unget();

    if (file.fail()) {
        file.clear();
    }
}

std::string FileReader::readLine() {
    std::string line;
    if (!std::getline(file, line)) {
        throw std::runtime_error("Error accediste mas alla del final del archivo");
    }

    return line;
}

bool FileReader::hasNext() {
    return file.peek() != EOF;
}

void FileReader::initFile(const std::string& path) {
    if (!file.is_open()) {
        file.open(path);
    }
}

void FileReader::close() {
    if (file.is_open()) {
        file.close();
    }
}

char FileReader::peek() {
    return file.peek();
}