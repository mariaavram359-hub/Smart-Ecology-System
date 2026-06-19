#include "../include/Logger.h"
#include <iostream>

Logger::Logger() {
    fisier_log.open("istoric_sistem.txt", std::ios::app);
    if (fisier_log.is_open()) {
        fisier_log << "\n=== SESIUNE NOUA START ===\n";
    }
}

Logger::~Logger() {
    if (fisier_log.is_open()) {
        fisier_log << "=== SESIUNE INCHISA ===\n\n";
        fisier_log.close();
    }
}

Logger& Logger::get_instance() {
    static Logger instance;
    return instance;
}

void Logger::info(const std::string& mesaj) {
    std::cout << "[INFO] " << mesaj << "\n";

    if (fisier_log.is_open()) {
        fisier_log << "[INFO] " << mesaj << "\n";
    }
}

void Logger::error(const std::string& mesaj) {
    std::cout << "\033[1;31m[EROARE] " << mesaj << "\033[0m\n";

    if (fisier_log.is_open()) {
        fisier_log << "[EROARE] " << mesaj << "\n";
    }
}

void Logger::warning(const std::string& mesaj) {
    std::cout << "\033[1;33m[WARNING] " << mesaj << "\033[0m\n";

    if (fisier_log.is_open()) {
        fisier_log << "[WARNING] " << mesaj << "\n";
    }
}

void Logger::success(const std::string& mesaj) {
    (void)this;
    std::cout << "\033[1;32m[SUCCESS] " << mesaj << "\033[0m\n";

    if (fisier_log.is_open()) {
        fisier_log << "[SUCCESS] " << mesaj << "\n";
    }
}