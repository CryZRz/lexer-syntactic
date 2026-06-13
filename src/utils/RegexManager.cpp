#include "RegexManager.h"

std::string RegexManager::identifierRgx = "^[a-z]+$";
std::string RegexManager::binaryNumberRgx = "^[01]*B$";
std::string RegexManager::octalNumberRgx = "^[0-7]+O$";
std::string RegexManager::hexaNumberRgx = "^[0-9A-F]+X$";
std::string RegexManager::symbolsRgx = "[;=+\\-/*,()]";

bool RegexManager::verifyIdentifier(std::string token) {
    const std::regex regex(identifierRgx);
    return std::regex_match(token, regex);
}

bool RegexManager::verifyBinaryNumber(std::string token) {
    const std::regex regex(binaryNumberRgx);
    return std::regex_match(token, regex);
}

bool RegexManager::verifyOctalNumber(std::string token) {
    const std::regex regex(octalNumberRgx);
    return std::regex_match(token, regex);
}

bool RegexManager::verifyHexaNumber(std::string token) {
    const std::regex regex(hexaNumberRgx);
    return std::regex_match(token, regex);
}

bool RegexManager::verifySymbol(std::string token) {
    const std::regex regex(symbolsRgx);
    return std::regex_match(token, regex);
}