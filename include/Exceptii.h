//
// Created by lenovo on 20.05.2026.
//

#ifndef OOP_EXCEPTII_H
#define OOP_EXCEPTII_H

#pragma once
#include <string>
#include <stdexcept>


class ExceptieSmartEcology : public std::runtime_error {
public:
    explicit ExceptieSmartEcology(const std::string& msg)
        : std::runtime_error(msg) {}
};


template <typename T>
class EroareSuprasolicitare;

template <typename T>
std::ostream& operator<<(std::ostream& os, const EroareSuprasolicitare<T>& eroare);

template <typename T>
class EroareSuprasolicitare : public ExceptieSmartEcology {
private:
    T info_suplimentar;

public:
    EroareSuprasolicitare(const std::string& msg, const T& info)
        : ExceptieSmartEcology(msg), info_suplimentar(info) {}

    const T& get_info_suplimentar() const {
        return info_suplimentar;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const EroareSuprasolicitare<T>& eroare) {
    os << eroare.what() << " : " << eroare.get_info_suplimentar();
    return os;
}

class EroareTipDeseu : public ExceptieSmartEcology {
public:
    explicit EroareTipDeseu(const std::string& msg)
        : ExceptieSmartEcology(msg) {}
};

class EroareCantitateInvalida : public ExceptieSmartEcology {
public:
    explicit EroareCantitateInvalida(const std::string& msg)
        : ExceptieSmartEcology(msg) {}
};

class EroareMentenanta : public ExceptieSmartEcology {
public:
    explicit EroareMentenanta(const std::string& msg)
        : ExceptieSmartEcology(msg) {}
};

#endif //OOP_EXCEPTII_H