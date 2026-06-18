#ifndef OOP_CONTAINERHARTIE_H
#define OOP_CONTAINERHARTIE_H

#pragma once
#include "ContainerDeseuri.h"

class ContainerHartie : public ContainerDeseuri {
public:
    ContainerHartie(int id, const std::string& locatie, float capacitate_maxima);
    ContainerHartie* clone() const override;
    void compacteaza_carton();
protected:
    void afiseaza_impl() const override;
};

#endif //OOP_CONTAINERHARTIE_H