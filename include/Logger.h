#ifndef OOP_LOGGER_H
#define OOP_LOGGER_H

#pragma once
#include <string>
#include <fstream>

class Logger {
private:
    std::ofstream fisier_log;


    Logger();
    ~Logger();

public:

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    static Logger& get_instance();

    void info(const std::string& mesaj);
    void error(const std::string& mesaj);
    void warning(const std::string& mesaj);
    void success(const std::string& mesaj);
};

#endif //OOP_LOGGER_H