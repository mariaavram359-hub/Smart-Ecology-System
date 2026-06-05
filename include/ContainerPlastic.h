//
// Created by lenovo on 19.05.2026.
//

#ifndef OOP_CONTAINERPLASTIC_H
#define OOP_CONTAINERPLASTIC_H

#pragma once
#include "ContainerDeseuri.h"

class ContainerPlastic : public ContainerDeseuri {
private:
    float eficienta_compactor{};

public:
    ContainerPlastic(int id_plastic, std::string locatie_plastic, float capacitate_plastic, float eficienta_plastic);

    [[nodiscard]] ContainerDeseuri* clone() const override;

protected:
    float calculeaza_spatiu_ocupat(const Deseu& deseu) const override;
    void afiseaza_impl() const override;
};

#endif //OOP_CONTAINERPLASTIC_H