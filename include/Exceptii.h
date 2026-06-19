//
// Created by lenovo on 20.05.2026.
//

#ifndef OOP_EXCEPTII_H
#define OOP_EXCEPTII_H

#pragma once
#include <string>
#include <stdexcept>


#include <iostream>

template <typename T>
class EroareSuprasolicitare;

template <typename T>
std::ostream& operator<<(std::ostream& os, const EroareSuprasolicitare<T>& eroare);

// 1. Clasa sablon
template <typename T>
class EroareSuprasolicitare : public std::runtime_error {
private:
    T info_suplimentar;

public:

    EroareSuprasolicitare(const std::string& msg, const T& info)
        : std::runtime_error(msg), info_suplimentar(info) {}

    const T& get_info_suplimentar() const {
        return info_suplimentar;
    }
};


template <typename T>
std::ostream& operator<<(std::ostream& os, const EroareSuprasolicitare<T>& eroare) {
    os << eroare.what() << " : " << eroare.get_info_suplimentar();
    return os;
}

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