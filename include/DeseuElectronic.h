//
// Created by lenovo on 21.05.2026.
//

#ifndef OOP_DESEUELECTRONIC_H
#define OOP_DESEUELECTRONIC_H

#pragma once
#include "Deseu.h"

class DeseuElectronic : public Deseu {
private:
    bool contine_baterie;
    public:

    explicit DeseuElectronic(float cantitate_electric, bool are_bateria);

    [[nodiscard]] int timp_descompunere_ani() const override;
    [[nodiscard]] std::string get_tip() const override;
    [[nodiscard]] float calculeaza_amprenta_carbon() const override;

    [[nodiscard]] std::string genereaza_raport_ecologic() const override;

protected:
    void afiseaza_impl(std::ostream& os) const override;
};
#endif //OOP_DESEUELECTRONIC_H