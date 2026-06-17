//
// Created by lenovo on 17.06.2026.
//

#ifndef OOP_ISTORIC_H
#define OOP_ISTORIC_H

#pragma once
#include <vector>
#include <iostream>
#include <string>

template <typename T>
class Istoric {
private:
    std::vector<T> inregistrari;

public:
    Istoric() = default;

    void adauga(const T& element) {
        inregistrari.push_back(element);
    }

    void afiseaza(const std::string& titlu = "Istoric:") const {
        std::cout << "--- " << titlu << " ---\n";
        if (inregistrari.empty()) {
            std::cout << "  (Nicio inregistrare)\n";
            return;
        }
        for (size_t i = 0; i < inregistrari.size(); ++i) {
            std::cout << "  " << i + 1 << ". " << inregistrari[i] << "\n";
        }
    }

    size_t dimensiune() const {
        return inregistrari.size();
    }
};

#endif //OOP_ISTORIC_H