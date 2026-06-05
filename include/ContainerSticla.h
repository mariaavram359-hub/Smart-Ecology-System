#ifndef OOP_CONTAINERSTICLA_H
#define OOP_CONTAINERSTICLA_H

#pragma once
#include "ContainerDeseuri.h"

class ContainerSticla : public ContainerDeseuri {
private:
    bool necesita_manipulare_atenta;

protected:
    void afiseaza_impl() const override;
    float calculeaza_spatiu_ocupat(const Deseu& deseu) const override;
public:
    ContainerSticla(int id_container, const std::string& locatie_container, float capacitate_maxima_container, bool manipulare_atenta = true);

    [[nodiscard]] ContainerSticla* clone() const override;
};

#endif //OOP_CONTAINERSTICLA_H