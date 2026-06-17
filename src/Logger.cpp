
#include "Logger.h"

void Logger::info(const std::string& message) {
    std::cout << "\033[36m[SISTEM INFO]\033[0m " << message << "\n";
}

void Logger::warning(const std::string& message) {
    std::cout << "\033[33m[AVERTISMENT]\033[0m " << message << "\n";
}

void Logger::error(const std::string& message) {
    std::cerr << "\033[31m[EROARE]\033[0m " << message << "\n";
}

void Logger::success(const std::string& message) {
    std::cout << "\033[32m[SUCCES]\033[0m " << message << "\n";
}