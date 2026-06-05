
#ifndef OOP_CONTAINERDESEURI_H
#define OOP_CONTAINERDESEURI_H

#pragma once
#include <iostream>
#include "Deseu.h"

class ContainerDeseuri {
protected:
    int id{};
    std::string locatie;
    float capacitate_maxima{};
    int grad_umplere{};
    float prag_colectare = 80.0f;

    int numar_colectari = 0;
    int prag_mentenanta = 3;
    bool in_mentenanta = false;

public:
    ContainerDeseuri(int id_container, std::string locatie_container, float capacitate_maxima_container);

    virtual ~ContainerDeseuri() = default;
    [[nodiscard]] virtual ContainerDeseuri* clone() const = 0;
    void afiseaza() const;

    void adauga_deseuri(const Deseu& deseu_aruncat);
    ContainerDeseuri& operator+=(const Deseu& deseu_aruncat);

    friend std::ostream& operator<<(std::ostream& os, const ContainerDeseuri& container);

    float goleste();

    [[nodiscard]] float get_grad_umplere() const;
    [[nodiscard]] float get_capacitate_maxima() const;
    void set_prag_colectare(float prag);
    [[nodiscard]] bool necesita_colectare() const;

    [[nodiscard]] bool este_in_mentenanta() const;
    void scoate_din_mentenanta();

    [[nodiscard]] int get_id() const;

protected:
    std::string tip_acceptat;
    virtual void afiseaza_impl() const = 0;
    virtual float calculeaza_spatiu_ocupat(const Deseu& deseu) const;
};

#endif //OOP_CONTAINERDESEURI_H