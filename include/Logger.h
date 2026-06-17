//
// Created by lenovo on 17.06.2026.
//

#ifndef OOP_LOGGER_H
#define OOP_LOGGER_H

#pragma once
#include <iostream>
#include <string>

class Logger {
private:
    Logger() = default;

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& get_instance() {
        static Logger instance;
        return instance;
    }

    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    void success(const std::string& message);
};

#endif //OOP_LOGGER_H