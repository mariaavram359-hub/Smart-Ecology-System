#ifndef OOP_DESEUFACTORY_H
#define OOP_DESEUFACTORY_H

#include "Deseu.h"
#include "DeseuPlastic.h"
#include "DeseuBiologic.h"
#include "DeseuElectronic.h"
#include "DeseuSticla.h"
#include <string>
#include <stdexcept>

class DeseuFactory {
public:
    static Deseu* creeaza(const std::string& tip, float cantitate) {
        if (tip == "Plastic")
            return new DeseuPlastic(cantitate, TipPlastic::PET);
        if (tip == "Biologic")
            return new DeseuBiologic(cantitate, true);
        if (tip == "Electronice")
            return new DeseuElectronic(cantitate, false);
        if (tip == "Sticla")
            return new DeseuSticla(cantitate, CuloareSticla::TRANSPARENTA, false);

        throw std::invalid_argument("Tip de deseu necunoscut: " + tip);
    }
};

#endif //OOP_DESEUFACTORY_H