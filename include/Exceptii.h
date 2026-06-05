//
// Created by lenovo on 20.05.2026.
//

#ifndef OOP_EXCEPTII_H
#define OOP_EXCEPTII_H

#pragma once
#include <string>
#include <stdexcept>


class EroareSuprasolicitare : public std::runtime_error {
public:
   explicit EroareSuprasolicitare(const std::string& msg)
       : std::runtime_error(msg) {
   }
};

class EroareTipDeseu : public std::runtime_error {
public:
    explicit EroareTipDeseu(const std::string& msg)
    : std::runtime_error(msg) {

    }
};

class EroareCantitateInvalida : public std::invalid_argument {
public:
    explicit EroareCantitateInvalida(const std::string& msg) : std::invalid_argument(msg) {}
};

class EroareMentenanta : public std::runtime_error {
public:
    explicit EroareMentenanta(const std::string& msg) : std::runtime_error(msg) {}
};


#endif //OOP_EXCEPTII_H